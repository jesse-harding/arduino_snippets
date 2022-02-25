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
#define pinAnalog0 A0
#define pinAnalog1 A1
//#define pinLed LED_BUILTIN  //used for calibration


//int thresh; //used for calibration

void setup(){
//  pinMode(pinLed, OUTPUT);// Led setup //used for calibration
//  thresh = analogTouchRead(pinAnalog); //used for calibration
  Serial.begin(115200); // Start Serial for debugging

} 
void loop(){
  uint16_t value0 = analogTouchRead(pinAnalog0);
  uint16_t value1 = analogTouchRead(pinAnalog1);
  Serial.print("A0: ");
  Serial.println(value0);
  Serial.print("A1: ");
  Serial.println(value1);


  // //used for calibration
//  if (value > thresh - 5){
//    digitalWrite(pinLed, HIGH);
//  }
//  else{
//    digitalWrite(pinLed, LOW);
//  }

  delay(100);
}
