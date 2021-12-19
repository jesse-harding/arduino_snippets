//from https://www.hackster.io/cesparzauk/inclusive-and-accessible-stem-afcbb5
//https://editor.p5js.org/jesse_harding/sketches/RwGr88C-0

//requires skywriter library: https://github.com/pimoroni/skywriter-hat/tree/master/arduino

#include <Wire.h>
#include <skywriter.h>

boolean data = false;

void setup() {
  Serial.begin(9600); //Initialise serial communication at 9600 bds
  while(!Serial){}; //We wait for the data serial port to start
  Serial.println("Hello world!"); //The port is ready!

  Skywriter.begin(10,11); //Initialise the Flick with the pins TS=D10 and RESET=D11
  
  Skywriter.onXYZ(handle_xyz); //This method records the position on the Flick and the function handle_xyz manipulates the data.
  
//We can initialise the LED pins as follows
  pinMode (9, OUTPUT); //Red LED
  pinMode (8, OUTPUT); //Green LED

}

void loop() {
  data = false;
  Skywriter.poll(); //Check if the status of the Flick has changed
  if (data){
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
  }
  else{
    digitalWrite(9, HIGH);
    digitalWrite(8, LOW);
  }
}

void handle_xyz(unsigned int x, unsigned int y, unsigned int z){
  data = true;
  char buf[17]; //An array of 17 characters 5 for each coordinate and two delimiters
  sprintf(buf, "%05u:%05u:%05u",x,y,z); //Record the position on the Flick
  Serial.println(buf); //Print the position to the serial port followed by a new line character
}
