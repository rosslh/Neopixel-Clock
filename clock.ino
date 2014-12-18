#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <RTClib.h>
short alarmPin = A0, //defines all the pins and global variables to be used in this project
switchPin = 8,
buttonPin = 7,
buzzerPin = 5,
ringPin = 6,

alarmHour = 0,
alarm5Minute = 0,

brightness = 40; //Maximum brightness of 255


RTC_Millis rtc; //defines the DS1307 as "rtc"
Adafruit_NeoPixel ring = Adafruit_NeoPixel(12, ringPin, NEO_GRB + NEO_KHZ800); //sets all the parameters of the ring

void setup() {
  Serial.begin(57600); //sets the rate of output of the serial monitor 
  pinMode(switchPin,INPUT); //Sets switch and button pins to input, and buzzer pin to output
  pinMode(buttonPin,INPUT);
  pinMode(buzzerPin,OUTPUT);
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //sets the date and time of the RTC
  ring.begin(); //Starts the Neopixel ring
  ring.show(); //Initialize all pixels to 'off'
  ring.setBrightness(brightness); //sets brightness using variable set earlier
}

void loop(){
  DateTime now = rtc.now(); //Sets the date and time using the rtc
  while(digitalRead(switchPin)) setAlarm(); //While the switchPin is recieving HIGH input, setAlarm() is looped
  displayTime(now.second(), now.minute(), now.hour()); //Displays the current time on the neopixel
  buzz(now.minute(), now.hour()); //Runs the buzzer function
  delay(50); //Delays 50 milliseconds
}

void displayTime(short seconds, short minutes, short hours){ //displayTime() is passed the current second, minute, and hour
  reset(); //first clears the neopixel
  showSeconds(seconds); //Shows the current second on the neopixel
  showMinutes(minutes); //Shows the current minute on the neopixel
  showHours(hours);     //Shows the current hour on the neopixel
}

void reset(){ //Clears the neopixel
  for(int i=0;i<12;i++)  ring.setPixelColor(i, ring.Color(0,0,0)); //Sets all 12 pixels to rgb 0,0,0
  ring.show();  //displays new neopixel output
}

void showHours(short hours){
  short pixel = hours;
  if(pixel > 12) pixel -= 12; //if the hour is greater than 12, subtract 12 (ie 13:00 to 1:00)
  setPixels(pixel, 255, 0, 0); //sets the pixel to red
}

void showMinutes(float minutes){
  short pixel = floor(minutes/5);  //divides the minute by 5 and floor to give the appropriate pixel
  setPixels(pixel, 0, 0, 255); //sets the pixel to blue
}

void showSeconds(float seconds){
  short pixel = floor((seconds)/5);  //divides the second by 5 and floor to give the apprpriate pixel
  setPixels(pixel, 0, 255, 0); //sets the pixel to green
}

void setPixels(short pixel, short r, short g, short b){ //displays pixels based on pixel # and rgb values passed to it
  ring.setPixelColor(pixel, ring.Color(r,g,b)); //sets pixels
  ring.show(); //displays new neopixel output
}

void setAlarm(){ //Sets the time for the alarm to go off
  while(digitalRead(buttonPin) && digitalRead(switchPin)) //while button is unpressed, and switch is on
      setAlarmHour(); //Sets the hour for the alarm to go off on

  while(!digitalRead(buttonPin)); //Doesn't move to next while loop until button is unpressed

  while(digitalRead(buttonPin) && digitalRead(switchPin)) //while button is unpressed, and switch is on
      setAlarmMinute(); //Sets the minute for the alarm to go off on

  while(!digitalRead(buttonPin)); //Doesn't move to next while loop until button is unpressed
}

void setAlarmHour(){
  reset(); //Clears the neopixel ring
  short potVal = readPotValue();
  setPixels(potVal,255,0,0); //Sets the Neopixel hour pixel to the potentiometer value
  if(!digitalRead(buttonPin)) alarmHour = potVal; //if the button is clicked, alarmHour is set
}

void setAlarmMinute(){
  reset(); //Clears the neopixel ring
  short potVal = readPotValue(); 
  setPixels(potVal,0,0,255); //Sets the Neopixel minute pixel to the potentiometer value
  if(!digitalRead(buttonPin)) alarm5Minute = potVal;  //if the button is clicked, alarmMinute is set
}

short readPotValue(){
  short value = analogRead(alarmPin); //Sets the value to the analog reading of the alarmPin
  value = map(value, 0, 1024, 0, 12); //maps the potentiometer reading to 12 values
  return value; //returns the value
}

void buzz(short minutes, short hours){
  if(hours > 12) hours -= 12; //subtracts 12 from the hours if the hours is above 12 (ie 13:00 to 1:00)
  minutes = floor(minutes/5); //divides the current minute by 5 and floors the value. (ie 38mins = 7 pixels)

  if(alarmHour == hours && alarm5Minute == minutes){
    boolean buzzing = true;

    while(buzzing){ //while buzzing is set to true
      digitalWrite(buzzerPin, HIGH); //buzz with a delay of 1 millisecond
      delay(1);
      digitalWrite(buzzerPin, LOW);
      delay(1);

      if(!digitalRead(buttonPin)){ //Stops buzzing if button is clicked
        buzzing = false;
        alarmHour = alarm5Minute = 0; //Sets the alarm hour and minute back to 0
      }
    }
  }
}




