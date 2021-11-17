/*
 Built off of:
 Copyright (c) 2015 NicoHood
 See the readme for credit to other people.

 AnalogTouch example
 Lights an Led if pin is touched and prints values to the Serial
*/

// AnalogTouch
#include <AnalogTouch.h>

// Choose your analog and led pin
#define pinAnalog A0
#define pinLed LED_BUILTIN

int thresh;
void setup(){
  pinMode(pinLed, OUTPUT);// Led setup
  Serial.begin(115200); // Start Serial for debugging
  thresh = analogTouchRead(pinAnalog);
}
void loop(){
  uint16_t value = analogTouchRead(pinAnalog);
  Serial.println(value);
  if (value > thresh - 5){
    digitalWrite(pinLed, HIGH);
  }
  else{
    digitalWrite(pinLed, LOW);
  }

  delay(100);
}
