Neopixel-Clock
==============

Reference:<br>
See: http://darcy.rsgc.on.ca/ACES/TEI3M/1415/Tasks.html#SurpriseMe1<br>
Adafruit Neopixel: https://www.adafruit.com/datasheets/WS2812.pdf<br>
RTC DS1307: http://datasheets.maximintegrated.com/en/ds/DS1307.pdf<br>

Purpose:<br>
The purpose of this project is to make a digital clock using an Adafruit Neopixel 12-pixel Ring, an Adafruit RTC DS1307, an analog potentiometer, a piezo speaker, a switch, and a button. These parts will work together to make a digital clock in the shape of a ring, whose alarm can be set using the potentiometer, switch, and button. The Real Time Clock (RTC) will be synced with the users computer upon upload of the program to the Arduino. The Neopixel ring will then display the time given by the RTC on its pixels, with “hands” (simply pixels that are on) for seconds, minutes, and hours. The alarm will be set based on the position of the potentiometer when the button is pressed.<br>

Procedure:<br>
1.	Connect the Neopixel ring to ground (GND), power (PWR), and pin 6.<br>
2.	Connect the RTC to GND and PWR, SDA and SCL to pins A4 and A5 respectively.<br>
3.	Connect the piezo speaker to pin 5 and GND<br>
4.	Connect the rotary potentiometer side pins to GND and PWR, and the middle pin to A0.<br>
5.	Connect the digital switch’s side pins to GND and PWR, and the middle pin to pin 8.<br>
6.	Connect the button’s top right pin to GND, and left pin to both pin 7 and to PWR via a 2.2kΩ resistor.<br>
7.	Download Adafruit Neopixel and RTClib libraries, and run the Arduino code.<br>

Parts List:<br>
1	Arduino Uno Microcontroller<br>
1	Adafruit Neopixel - 12 Pixel Ring<br>
1	RTC DS1307, mounted on an Adafruit breakout board<br>
1	Rotary Potentiometer<br>
1	Push Button Normally On (PBNO)<br>
1	Digital Switch<br>
1	Piezo Speaker<br>
3	2.2kΩ resistors<br>
