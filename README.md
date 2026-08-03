# CRASHSENSE
Crashsense is a high level embedded sytems project which senses crashes in vehicles like cars trucks and also drones and records crital data of that crash and gives enough data for the crash to be reoncstructed 

# Why did i create this 
i created Crashesense as this is a successor to my older project Dropsense what was dropsense it was simply a embedded system device a PCB inside a hard shell cover which you could drop from any height and it would tell you exactly what height was it droppsed from and also the G-Force with which it impacted the ground

Now this idea grew from a silly project of dropping and analyzing to something bigger i decided to add the best of the best sensors and analyze the data given by then 

Basically Crashsense by it's name you can figure out it is related to something which crashes what crashes?
A lot of things Cars, motorbikes, trucks, drones, ships, and many more vehicles 
Now imagine you could take out something useful from something as negative as a crash from am engineering presepective if Crashsense is intalled in a vehicle from the start if it ever crashes it would give us a lot of DATA....DATA is the most useful thing in engineering which not only tells us how our system behaved but also can be analyzed to fugure out how to make the system behave better and be operate with more accuracy and precision 

Crashsense extracts critical data from a crash like retardation, impact velocity, angle of impact (forward, rear, side, heads on collision) which may be used by engineers to find out how the car crashed and the data may also be analyzed b forensic investigators to collect better evidence. not only all this but if you are making your own custom drone you can install crashsense on it and find out at what exact angle it falls down and how does it fall down and it'll help to pinpoint the point of faliure of the entire system

# HARDWARE & PCB SPECS 

## MICROPROCESSOR
This PCB runs on **ESP32-S3-WROOM-1** operating at speeds of 240Mhz for high frequency data sampling and sensor fusion 

## SENSORS
The main sensors used in this project are 
1. **BMI270** - 6 Axis Inertial Measurement Unit for reading  standard acceleration
2. **ADXL377** - 3 Axis Accelerometer extremely precise readings with massive reading range +-200G
3. **u-blox NEO-M8N** - Additional GPS tracting for pinpointing the location of crash 
4. **DS3231M - precise** timekeeping and timestamping the logged data

## Storage system 
**Push-Push Micro SD-Card Slot** this locks the card firmly inside it's frams and ensures no hinderance with high speed SPI communication 

## Power and Battery Management 
1. **USB-C connector** much better than old micro-usb connectors 
2. **TP4056** for recharing li-ion battries connected in araller for maximum runtime without being connected to external power source
3. **ME6211 3.3V** to step down the 5V input power to stable and low noise 3V3 volts 
4. **Li-ion battries** with JST connector for secure connection 

## Control and Diagnostics #
1. Boot and reset buttons 
2. UART debuggin header (incase USB-C fails to work)

# Schematics
<img width="917" height="653" alt="image" src="https://github.com/user-attachments/assets/a588354a-ed32-4c77-b208-898fecac20c1" />
<img width="755" height="582" alt="image" src="https://github.com/user-attachments/assets/35923196-79d2-42c8-b43f-2fefbe704b32" />
<img width="737" height="565" alt="image" src="https://github.com/user-attachments/assets/27ef61de-0b24-4023-bc82-6612154fdf8c" />

# PCB
<img width="1580" height="882" alt="Crashsense PCB Render-1" src="https://github.com/user-attachments/assets/28ff6a70-5415-43b5-935a-e20b0fe32de9" />
<img width="1580" height="882" alt="Crashsense PCB Render-2" src="https://github.com/user-attachments/assets/bf2b3f8c-44f6-457f-9f1e-0234a42bb2e4" />
<img width="1580" height="882" alt="Crashsense PCB Render-3" src="https://github.com/user-attachments/assets/c52cccf8-4679-45f7-b950-db0f46cd8cf6" />

# BOM
| Component | Designator(s) | Qty | LCSC Part # | Manufacturer Part # | Package | Supplier |
|-----------|---------------|-----|-------------|---------------------|---------|----------|
|Esp32 S3|U1|1|C701341|ESP32-WROOM-32E-N4|Module |LCSC| 
|LowG IMU/GYRO|U2|1|C2828751|BMI270|LGA-14|LCSC|
|High G accelerometer|U3|1|C138128|ADXL377BCCZ|LFCSP-16|LCSC|
|Precise RTC|U4|1|C83023|DS3231MZ+|SOIC-8|LCSC|
|3v3 LDO Regulartor|U5|1|C6186|AMS1117-3.3|SOT-223 |LCSC|
|MicroSD Card slot |J1|1|C114227|MICRO SPI Push-Push|SMD|LCSC|
|GPS Module Header|J2|1|C124375|Header 1x05 Pin|2.54mm Pitch|LCSC|
|Power connector|J3|1|C136657|XT30PW-M|Right_Angle_SMD|LCSC |
|TVS Diode |D1|1|C83307|SMAJ5.0A|SMA(DO-214AC)|LCSC|
|Schhotkey diode|D2|1|C8598|SS14|SMA(DO-214AC)|LCSC| 
|I2C Pull up resistors|R1,R2|2|C8598|4.7kΩ 1%|0805|LCSC|
|ADXL377 Filter Resistors|R3,R4,R5|3|C25804|4.7kΩ 1%|0805|LCSC|
|ESP32 Boot/EN Pull-ups|R6,R7|2|C17414|10kΩ 1%|0805|LCSC|
|ADXL377 Filter Capacitors|C1,C2,C3|3|C15849|10nF 50V|0805|LCSC|
|Bulk Input capacitors|C4,C5|2|C15850|10uF 25V|0805|LCSC|
|Decoupling Capacitors|C6,C7,C8,C9|4|C14663|100nF 50V|0805|LCSC|
|RTC Backup Battery Holder|BT1|1|C70377|CR1220 Holder|SMD|LCSC|






