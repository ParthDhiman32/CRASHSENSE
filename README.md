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

#3D DESIGN 
<img width="946" height="333" alt="image" src="https://github.com/user-attachments/assets/8866bc36-f520-416b-a4cc-cb2ec569453d" />
<img width="788" height="380" alt="image" src="https://github.com/user-attachments/assets/8cdc51d0-d37f-4c0c-97bb-f432bc82bf2c" />
<img width="1242" height="708" alt="image" src="https://github.com/user-attachments/assets/0ea3c674-cffd-4e50-bf4a-9a28bb437a6a" />
<img width="1920" height="1080" alt="Crashsense Mark-1 3D assmebly v1" src="https://github.com/user-attachments/assets/e19d6577-a7b9-4ff8-b91b-da0c186a965d" />
<img width="1920" height="632" alt="Crashsense Mark-1 3D assmebly V2" src="https://github.com/user-attachments/assets/c6ebc2e5-4c15-4357-9167-225f5ed03ad3" />

the smaller box that you can see has a sliding lid which will fit onto the case and then screwed tightly to prevent it from slipping during impact 

The bigger box that you can see has a hexagonal infill pattern which will compress and crush under impact to absorb the shock and prevent the inner hard shell from breaking 

# THE PCB AND 3D DESIGN FOR THIS PROJECT ARE COMPLETE BUT THE CODE REMAINS I HAVE SHIPPED THIS PROJECT SO THAT I CAN GET MY CURRENT HOURS APPROVED AND BUY THE TICKET BEFORE THE DEADLINE AND WORK ON THE REMANING HOURS TILL 14TH AUGUST FOR HORIZONS-EQUINOX


