---
Title: "Crashsense"
Author: "Parth Dhiman"
Description: "Crashsense is a smart crash analysis system which recods data of a crash and has SOS features"
Created_at: "2026-7-22"
---

# July 22nd: Setting up and researching!

So today is the day i started my work for horizons-equinox in this session all what i did was to simply set up hackatime for VS code and also learn how to journal and use github it was a bit hard to set up because horizons equinox is mainly for software projects but to also log hardware projects i also needed to learn how to sync hackatime and lapse so i can track both my coding time and the time i will be speding on my CAD and PCBs 
So what project am i making is something you might be wondering i am start to work on crashsense actually this is a continuation of my last project Dropsense dropsense was a great learning project basically you could drop it from a certain height and it would log all the data of the drop but now i want to upgrade my project i am going to another level with this project i am willing to make a device which could be mounted in a car ans which could record all sorts of inertial measurements of the car now you would ask me does that not already exist which i would give am answer to as yes! it already does exist but what the point is for making this project is that i am making this project as a learning project and i will also try to include as any features in it as i can so i may also be able to patient it in the future! and yes i will now start to research for this project deciding which are the best sensors to use in this and ones with the maximum data collection rate!

OKay so this is after i researched for the project and i have a lot to say first of all let me list all the parts i will be using in this project 
1. ESP32-S3-WROOM-1
2. ADXL377
3. QMC5883L
4. BMI270
5. micro sd
6. DS3231 
7. u-blox NEO-M8N
8. USB C
9. TP4056
10. ME6211 3v3
so let me talk about each and evey part one by one 

no-1 we have esp32 s3 wroom-1 module which is the microcontroller i will be using for this project this is the brain of the entire system i am planning to use this because of it's very high operational frequency of upto 240Mhz which is enough for my project which needed data sampaling at a very fast rate and also because of it's abundant GPIO pins which will allow me to connect all of the above listed compoennts 
next up 

no-2 ADX377 this is the best accelerometer i could find because it records acceleration upto +- 200g in all 3 axes with maximum accuracy and i don't think a better accelerometer than this for my budget exists i will be using as car crashes have an massive magnitudes of retardation 100-200g and as the range of this sensor falls withing the range of a typicall car crash it will most probably be able to record most of the critical data 


no-3 QMC5883L is a 3 axis digital compass which measure's the earth's magnetic fields accurately and gives accurate compass directions this will help me to figure out what direction the vehicle is heading to The best part i can combine this with the accelerometer and tell if a collision happens which direction did the collision hapenned from read end or frontend or side impact very accurately 

no-4 BMI270 now this is a very powerful gyroscope it also does feature a accelerometer but we do not require that as we are already using ADX377 which is much much better than the accelerometer featured by this 
Now if i combine the acclerometer the compass and this gyroscope sensor together i now have the ability to capture a new variety of crash which is if the car rolls over or falls down a hill now i can detect rotation yaw and pitch by sensor fusion 

no-5 i will be using a simple sd card module to log the data now you may be asking why use a sd card they are not that fast to log tens of thousands of bits of data at a very low frequency now we can fix this issue by simply logging a chunk of data in the 512KB of Sram the esp32 s3 wroom-1 offers and then load that into the sd card at once ad repeate this process and it makes logging the data much more relaible 

mo-6 DS3231 is a RTC module which i will use to add timestamps to each of my readings in formats of dd/mm/yy for header reading and then readings for the actual logged data will be logged in intervals f miliseconds as per the esp32 s3 wroom-1' clock

no-7 u-blox NEO-M8N this is a pretty good enough GPS for crashsense as i also want to record the velocity of the crash and also for future upgrades i want to give the exact co-ordinates where the crash most probably took place 

no-8,9,10 TP4056 now here comes the power system which i would like to cover all together so first up comes the usb-c which i will using to power program and test the entire pcb firstly the 5V power enters through the USB and then i use the TP4056 module to charge the onboard li-ion battery which will power the entire system for now i will add a more complex power system in the pcb which enable the pcb to run directly off of the 11.8 to ~14 V from the lead acid car battery and yes i will also add supercapacitors later incase the battery wires snap during a crash 

<img width="1532" height="744" alt="image" src="https://github.com/user-attachments/assets/63774e1b-62cb-4026-a261-0b771fb3503b" />


**Total time spent: ~2h** for the lapse + journal if talking only about the journal i spent a exact time of 1 hour and 7 mins on it because i mostly did research and wrote my views here today 

# July 23rd: Deeper research and Pcb schematic development!

So guys today's decided goal is to complete adding all the parts i need for my project in the schematic and then 
hopefully start the routing 

So i decided to make a change in the magnotemeter i'll be using instead of using a QMC5883L 3 axis magnometer 
i will instead use BMM150 which is also a 3 axis magnetometer but this one is made by bosch and hence 
is much more relaible

so first of all what i did was to place all the parts in the KiCAD schematics editor 
I got most of the parts in the default library but i needed to add a few special sensors like ADXL377 and the 
BMI270 3 axis accelerometer and gyroscope from bosch 

now first of all i started to wire up the power system consistong of a USB C connector TP4056 for charging the battery and also a ME6211 to step down the voltage from 5V from the USB C to 3V3 volts on which the entire system will operate on if any sensor requires exact 5V signal i will either use a I2C signal logic level converter because f i directly feed the sensor 5V it will be output 3V3 signals to my ESP32 S3 and cook it 

so i worked on the power system i wired up a USB C connector to my TP4056 battery power managemnent IC and use it to charge my 
li-ion battries and also give the 3V3 volt regulator aka the ME6211 which is being fed the 5V from the TP4056 
for it to be convertyed into stable 3V3 volts also i added 10uF capacitors at the input and output of each of the 
regualtors to store power and to stabelize voltage fluctuations which may take place 
<img width="1457" height="680" alt="image" src="https://github.com/user-attachments/assets/48396691-1ae5-43ce-8994-07801063d5c7" />


after this i wired up the sd card module and added net labels for easily connecting them to my ESP32 S3 WROOM-1 module 
also i added one 10uF capacitor at the inputs of the SD card module to stabelize the voltage and a 100nF capacitor to 
filter out the any noise in the power signals which may interfere with the SD card module 
<img width="728" height="619" alt="image" src="https://github.com/user-attachments/assets/8b5d74a5-efa2-4e22-a638-5dd4a806f916" />

## overall PCb schematic as of today 
<img width="852" height="592" alt="image" src="https://github.com/user-attachments/assets/826f070b-b4e3-4b6b-b89e-10f2f8140894" />


**Total time spent: ~2.5h** (including lapse and journalling)

# July 24th: PCb schematics continued!

sooo guys my goal for tonight is to route 3 more sensors properly like not properly perfectly flawlessly so that 
i would not worry about my connections being wrong 

I started by wiring up the very easy u-blox-NEO-M8N GPS which uses only vcc gnd and I2C pins which make 
the connections very easy 

then i connected the ADX377 to my esp32 s3 i added a 100nF decoupling capacitor and also added 10nF capacotors at X Y and Z 
output pins to set the data sampaling speed to 200Hz

after that i made a master I2C rail over which i connected all the I2C devices mainly the DS3231M RTC 

and lastly i connected the BMI270 IMU which i'll be using for reading the gyroscopic values for all 3 axes 

<img width="525" height="564" alt="image" src="https://github.com/user-attachments/assets/e1f13cfb-6ac1-45e2-bbb9-47dc76a2ed2e" />
<img width="579" height="485" alt="image" src="https://github.com/user-attachments/assets/b276cf28-9bc5-42c3-9863-5d978e258987" />\
<img width="823" height="505" alt="image" src="https://github.com/user-attachments/assets/b5bfd0fb-18cb-412e-9d07-d56258076d89" />
<img width="922" height="633" alt="image" src="https://github.com/user-attachments/assets/e0848537-99c8-44bc-9484-9603b1313bcf" />

**Total time spent: ~1.3h** (including lapse and journalling)

# July 24th: PCB schematics finished!
So guys my goal for today is to finish the pcb and then organize the schematics and optimize it for redability 
to make it look proffesional afterall

so firstly i wired up the last piece the BMM150 the 3 axis compass which will be used for telling which direction the vehicle 
is headed to and from where did the crash occur 

what i learnt that i always have to connect a 100nF resistor with every IC because it stabelizes the power input 
and also helps to reduce impact of high frequency signals on the IC 

as for the ESP32 S3 wroom-1 module which i mostly use in my projects i need to connect 2 resistors to it 
firstly the bulk charge holder 10uF capacitor and then the noise reducing capacitor aka the 100nF capacitor 
the combination of the two helps with fluctuating power and signal noise 

alright now after adding these changes i also added the RC delay circuit for the EN pin with a 10kR resistor 
and a 1uF resistor and a reset circuit for the IO0 pin to decide wether to put the ESP32 in running or uploading module

then i also added 2 pins the RX and TX as pin headers on the PCB so that i can still upload the code to my esp32 
is my USB fails to program or detect the ESP32 which has hapenned to me in the past so i mostly use a FTDI 
module connected to the ESP32's RX and TX pins to flash it 

now i have another bigger obstacle in my way i need to organize everything all the components in the schematic

alright now i organised everything inside the schematic
The power delivery system is at the top right 
The esp32 s3 wroom-1 with all it's connection flags is placed in the center the accelerometer and the gyroscope sensor to it's right
The RTC and the RC delay and Reset circuits are on the leftthe sd card module on the top left 

Now i ran the most critical part the ERC 
first it showed 5 errors and 3 warnings 
the 5 errors pominted to 2 unconnected pins which i forgot to place a no connection mark on and 
the other 3 were pointing at the +5V_BAT the 3V3 and the GND i just needed to add 3 PWR_FLAGS to them to fix it
Then i ignored the warnings because they were pointing at some silly stuff and i saw ZERO!!!!! DRC errors

now i added footprint for each and every component used from a single resistor to the BMI270 all have the footprints assigned
now i converted everything to a pcb and i already know it is going to be a hell of a routing session 

Here are the screenshots of today's work 
<img width="893" height="644" alt="image" src="https://github.com/user-attachments/assets/9dd541ad-0688-4536-b2f8-0e1da0931cad" />
<img width="857" height="540" alt="image" src="https://github.com/user-attachments/assets/c0777a9e-5936-4fa9-975c-1ada1043d9b4" />
<img width="940" height="668" alt="image" src="https://github.com/user-attachments/assets/c9d73274-d097-4a66-918a-7dc5fbd90d2d" />
<img width="1410" height="795" alt="image" src="https://github.com/user-attachments/assets/188c15b2-6905-4677-8984-6c3c9ff7e809" />
<img width="1536" height="816" alt="image" src="https://github.com/user-attachments/assets/0996262a-bbfd-4bc1-86a3-f1253607cc1b" />


Which i decide to save for tomorrow 

**Total time spent: ~1.6h** (including lapse and journalling)
