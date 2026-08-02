/** CRASHSENSE MARK-1 FIRMWARE **/
#include <Wire.h>
#include <SparkFun_BMI270_Arduino_Library.h>
#include <RTClib.h>
#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include <SPI.h>
#include <SD.h>

// --- PIN DEFINITIONS & CONSTANTS ---
#define RXD2 16
#define TXD2 17 
#define GPS_BAUD 9600 

const int PIN_X = 32; 
const int PIN_Y = 33;
const int PIN_Z = 34;
const int SD_CS_PIN = 5; // Standard ESP32 VSPI CS pin

const float V_REF = 3.3;            
const float ADC_MAX = 4095.0;       
const float ZERO_G_VOLTS = 1.65;    
const float SENSITIVITY  = 0.0065;  

// --- GLOBAL OBJECTS ---
RTC_DS3231 rtc;
TinyGPSPlus gps;
HardwareSerial gpsSerial(2); 
BMI270 imu;

// --- DATA STRUCTURES & RTOS GLOBALS ---
struct SensorFrame {
  uint32_t timestamp_us;
  float ax, ay, az;
  float gx, gy, gz;
  float lat, lng;
  uint8_t hour, minute, second;
};

const int BUFFER_SIZE = 400;
SensorFrame ringBuffer[BUFFER_SIZE];
volatile int headIndex = 0;

QueueHandle_t crashQueue;
TaskHandle_t SensorTaskHandle;
TaskHandle_t SDTaskHandle;

// --- CORE 0: HIGH SPEED SENSOR TASK ---
void core0_SensorTask(void *pvParameters) {
  TickType_t xLastWakeTime = xTaskGetTickCount();
  const TickType_t xFrequency = pdMS_TO_TICKS(5); // 200 Hz

  int impactCounter = 0;
  bool crashStatusLocked = false;

  for(;;) {
    // 1. Read Analog Accelerometer
    float gX = (((analogRead(PIN_X) / ADC_MAX) * V_REF) - ZERO_G_VOLTS) / SENSITIVITY;
    float gY = (((analogRead(PIN_Y) / ADC_MAX) * V_REF) - ZERO_G_VOLTS) / SENSITIVITY;
    float gZ = (((analogRead(PIN_Z) / ADC_MAX) * V_REF) - ZERO_G_VOLTS) / SENSITIVITY;

    // 2. Read Digital IMU
    imu.getSensorData();

    // 3. Update GPS data in background (non-blocking)
    while (gpsSerial.available() > 0) {
      gps.encode(gpsSerial.read());
    }

    // 4. Get Time
    DateTime now = rtc.now();

    // 5. Write to Ring Buffer
    ringBuffer[headIndex].timestamp_us = micros();
    ringBuffer[headIndex].ax = gX;
    ringBuffer[headIndex].ay = gY;
    ringBuffer[headIndex].az = gZ;
    ringBuffer[headIndex].gx = imu.data.gyroX;
    ringBuffer[headIndex].gy = imu.data.gyroY;
    ringBuffer[headIndex].gz = imu.data.gyroZ;
    
    if (gps.location.isValid()) {
      ringBuffer[headIndex].lat = gps.location.lat();
      ringBuffer[headIndex].lng = gps.location.lng();
    }
    
    ringBuffer[headIndex].hour = now.hour();
    ringBuffer[headIndex].minute = now.minute();
    ringBuffer[headIndex].second = now.second();

    // 6. Crash Detection Logic
    float aTotal = sqrt((gX*gX) + (gY*gY) + (gZ*gZ));
    
    if(aTotal > 5.0 && !crashStatusLocked) {
      impactCounter++;
      if(impactCounter >= 4) {
        crashStatusLocked = true;
        int freezeIndex = headIndex;
        xQueueSend(crashQueue, &freezeIndex, portMAX_DELAY);
      }
    } else {
      impactCounter = 0;
    }
     
    // 7. Advance Buffer and Delay
    headIndex = (headIndex + 1) % BUFFER_SIZE;
    vTaskDelayUntil(&xLastWakeTime, xFrequency);
  }
}

// --- CORE 1: ASYNCHRONOUS SD CARD TASK ---
void core1_SDTask(void *pvParameters) {
  int freezeIndex = 0;

  for(;;) {
    if (xQueueReceive(crashQueue, &freezeIndex, portMAX_DELAY) == pdPASS) {
      File dataFile = SD.open("/crash_log.csv", FILE_APPEND);
      if (!dataFile) {
        vTaskDelete(NULL); // SD failure, kill task
      }

      // Dump pre-crash history
      int readIndex = (freezeIndex + 1) % BUFFER_SIZE;
      for(int i = 0; i < BUFFER_SIZE; i++) {
        dataFile.print(ringBuffer[readIndex].timestamp_us); dataFile.print(",");
        dataFile.print(ringBuffer[readIndex].ax, 2); dataFile.print(",");
        dataFile.print(ringBuffer[readIndex].ay, 2); dataFile.print(",");
        dataFile.println(ringBuffer[readIndex].az, 2);
        // (Add gyro, lat, lng, time prints here to match your CSV headers)
        readIndex = (readIndex + 1) % BUFFER_SIZE;
      }
      
      dataFile.flush();

      // Capture post-crash data
      int postCrashFrames = 1000;
      int lastWrittenIndex = freezeIndex;

      while (postCrashFrames > 0) {
        if (headIndex != lastWrittenIndex) {
          lastWrittenIndex = (lastWrittenIndex + 1) % BUFFER_SIZE;
          dataFile.print(ringBuffer[lastWrittenIndex].timestamp_us); dataFile.print(",");
          dataFile.print(ringBuffer[lastWrittenIndex].ax, 2); dataFile.print(",");
          dataFile.print(ringBuffer[lastWrittenIndex].ay, 2); dataFile.print(",");
          dataFile.println(ringBuffer[lastWrittenIndex].az, 2);
          postCrashFrames--;
        } else {
          vTaskDelay(pdMS_TO_TICKS(1));
        }
      }
      
      dataFile.flush();
      dataFile.close();
      vTaskSuspend(NULL);
    }
  }
}

// --- SYSTEM INITIALIZATION ---
void setup() {
  Serial.begin(115200);
  gpsSerial.begin(GPS_BAUD, SERIAL_8N1, RXD2, TXD2);
  Wire.begin();
  Wire.setClock(400000); 
  analogReadResolution(12);

  // Initialize Sensors
  if (imu.beginI2C(0x68) != BMI2_OK) {
    Serial.println("BMI270 NOT DETECTED");
    while (1);
  }
  if (!rtc.begin()){
    Serial.println("Cannot find RTC");
    while (1);
  }
  if(rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  
  // Initialize SD Card
  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("SD Card Mount Failed");
    while (1);
  }

  // Create IPC Queue
  crashQueue = xQueueCreate(1, sizeof(int));
  if(crashQueue == NULL){
    Serial.println("ERROR: Queue allocation failed.");
    while(1);
  }

  // Pin Tasks to Cores
  xTaskCreatePinnedToCore(core0_SensorTask, "SensorTask", 4096, NULL, 2, &SensorTaskHandle, 0);
  xTaskCreatePinnedToCore(core1_SDTask, "SDTask", 8192, NULL, 1, &SDTaskHandle, 1);
}

void loop() {
  vTaskDelete(NULL); // Kill default loop to free Core 1
}