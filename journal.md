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


**Total time spent: h**
