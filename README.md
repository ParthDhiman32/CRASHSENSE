# CRASHSENSE
Crashsense is a high level embedded sytems project which senses crashes in vehicles like cars trucks and also drones and records crital data of that crash and gives enough data for the crash to be reoncstructed 

# Why did i create this #
i created Crashesense as this is a successor to my older project Dropsense what was dropsense it was simply a embedded system device a PCB inside a hard shell cover which you could drop from any height and it would tell you exactly what height was it droppsed from and also the G-Force with which it impacted the ground

Now this idea grew from a silly project of dropping and analyzing to something bigger i decided to add the best of the best sensors and analyze the data given by then 

Basically Crashsense by it's name you can figure out it is related to something which crashes what crashes?
A lot of things Cars, motorbikes, trucks, drones, ships, and many more vehicles 
Now imagine you could take out something useful from something as negative as a crash from am engineering presepective if Crashsense is intalled in a vehicle from the start if it ever crashes it would give us a lot of DATA....DATA is the most useful thing in engineering which not only tells us how our system behaved but also can be analyzed to fugure out how to make the system behave better and be operate with more accuracy and precision 

Crashsense extracts critical data from a crash like retardation, impact velocity, angle of impact (forward, rear, side, heads on collision) which may be used by engineers to find out how the car crashed and the data may also be analyzed b forensic investigators to collect better evidence. not only all this but if you are making your own custom drone you can install crashsense on it and find out at what exact angle it falls down and how does it fall down and it'll help to pinpoint the point of faliure of the entire system

# Components 

## sensors
The main sensors used in this project are 
1. BMI270 - 6 Axis Inertial Measurement Unit for standard acceleration
2. ADXL377 - 3 Axis Accelerometer extremely precise with massive reading range +-200G
3. u-blox NEO-M8N - Additional GPS tracting for pinpointing the location of crash 
4. DS3231M - precise timekeeping and timestamping the logged data 

## Micro processor
The micro processer i used for this project on which my custom PCB is based is ESP32 S3 WROOM-1 
because of it's high preocessing speeds of upto 240MHz

## Storage system
A push insert micro SD card for high speed data logging and keeping the micro SD card secure 

## Power and Battery Management 
1. USB-C connector much better than old micro-usb connectors 
2. TP4056 for recharing li-ion battries connected in araller for maximum runtime without being connected to external power source
3. ME6211 3.3V to step down the 5V input power to stable and low noise 3V3 volts 
4. Li-ion battries with JST connector for secure connection 

## Control and Diagnostics
1. Boot and reset buttons 
2. UART debuggin header (incase USB-C fails to work) 


