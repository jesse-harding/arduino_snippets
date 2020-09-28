int potVal; //declare integer variable named potVal (short for potentiometer value) (0-1023)
int ledVal; //declare integer variable for PWM output (0-255)

void setup() {
  pinMode(A0, INPUT); //set out analog pin to input
  pinMode(3, OUTPUT); //set pin 3 to output for PWM control of LED
  Serial.begin(9600); //turn on serial connection at 9600 bits/sec
}

void loop() {
  potVal = analogRead(A0); //read voltage being applied to pin A0

  ledVal = constrain(map(potVal, 100, 500, 0, 255),0,255); //constrain mapped value so it doesn't leave 0-255 range

  analogWrite(3, ledVal); //change duty cycle of PWM applied to LED
  
  Serial.println(potVal); //print value of potVal over USB to computer, ending in new line character
}
