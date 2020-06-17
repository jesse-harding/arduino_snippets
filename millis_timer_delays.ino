const int buttonPin = 2;
const int potPin = A0;
const int ledPin = 13;
int timerVal;
bool ledOn = false;

int buttonState = 0;
int potState = 0;

void setup() {
    // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
    // initialize the pushbutton/potentiometer pins as inputs:
  pinMode(potPin, INPUT);
  pinMode(buttonPin, INPUT);
    //start serial connection at 9600 baud (make sure this matches in processing)
  Serial.begin(9600);
  timerVal = millis();
}

void loop() {
    // read the state of the pushbutton value:
  potState = analogRead(potPin);
    // check if the pushbutton is pressed.
  buttonState = digitalRead(buttonPin); //momentary button

    //version using delay:
  digitalWrite(ledPin, HIGH);
  delay(potState);
  digitalWrite(ledPin, LOW);
  delay(potState);

    //verision using millis() timer:
//  if (millis() > timerVal + potState){
//    timerVal = millis();
//    ledOn = !ledOn;
//  }
//
//  if (ledOn){
//    digitalWrite(ledPin, HIGH);
//  }
//  else{
//    digitalWrite(ledPin, LOW);
//  }

   //send sensor values over serial connection
  Serial.print(potState);
  Serial.print("&");
  Serial.println(buttonState);
}
