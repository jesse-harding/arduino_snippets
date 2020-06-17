//global variable declaration
int ledPin = 13; //set which pin we want to use to blink our LED
int interval = 100; //set the interval (how often in milliseconds our code will run)

//variables for using a millis() timer
//this variable stores the time after each interval passes, so that we can begin a new count
//reference: https://www.arduino.cc/en/Reference.Int & https://www.arduino.cc/reference/en/language/variables/data-types/unsignedlong/
int prevMillis = 0; //the "int" datatype has a range of -32,768 to 32,767 (unused data, will work for about 33s)
//unsigned long prevMillis = 0; //the "unsigned long" datatype has a range of 0 to 4,294,967,295 (will work for about 50 days)



// create a boolean variable to toggle the led state from on to off and so on
boolean ledState = true;

void setup() {
  pinMode(ledPin, OUTPUT); //set LED pin to output
  Serial.begin(9600); 
}

void loop(){
  


//LETS START WITH A BLINK SKETCH USING DELAY()
  digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(interval);                       // wait for a tenth of a second
  digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
  delay(interval);                       // wait for a tenth of a second



////NOW LETS USE A MILLIS() TIMER INSTEAD OF A DELAY
//  if (millis() - prevMillis > interval){ //compare current time against stored time; if the difference is greater than our interval variable, the code within will run
//    digitalWrite(ledPin, ledState); //write the ledState to our ledPin
//    ledState = !ledState; //toggle the led state between true & false
//    prevMillis = millis(); //set stored time to the current time to reset the timer (now the difference between prevMillis and the current time will be less than the interval)
//  }
//  Serial.println(millis()); //print the number of milliseconds since the program began to the serial connection



}
