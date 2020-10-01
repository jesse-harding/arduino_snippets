
/*
 Stepper Motor Control - one revolution

 This program drives a unipolar or bipolar stepper motor.
 The motor is attached to digital pins 8 - 11 of the Arduino.

 The motor should revolve one revolution in one direction, then
 one revolution in the other direction.


 Created 11 Mar. 2007
 Modified 30 Nov. 2009
 by Tom Igoe

 modified for 28byj48 by Jesse Harding
 */

#include <Stepper.h>

const int stepsPerRevolution = 2048;  // CHANGE TO 2048

// initialize the stepper library on pins 8 through 11:
// these pins will control the polarity of the electromagnets inside of the stepper motor
// if they are in an incorrect order, the changes in magnetic field will not let the motor spin properly
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11); 
void setup() {
  // set the speed at 10 rpm (15 seems to be about the max for this motor):
  myStepper.setSpeed(10);
  // initialize the serial port:
  Serial.begin(9600);
}

void loop() {
  // step one revolution  in one direction:
  Serial.println("clockwise");
  myStepper.step(stepsPerRevolution);
  delay(500);

  // step one revolution in the other direction:
  Serial.println("counterclockwise");
  myStepper.step(-stepsPerRevolution);
  delay(500);
}
