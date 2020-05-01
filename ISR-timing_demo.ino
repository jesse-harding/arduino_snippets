//https://www.instructables.com/id/Arduino-Timer-Interrupts/

#define outPin 10
#define inPin A0

float sensorVal;
float sensorCalibrate;

float outputRange = -20000;
float outputMin = 65535;

int timerCounter;

void setup(){
  Serial.begin(9600);
  pinMode(outPin, OUTPUT);
  pinMode(inPin, INPUT);
  sensorCalibrate = analogRead(inPin);

  noInterrupts();          //initialize timer1 // disable all interrupts
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = timerCounter;   // preload timer
  //TCCR1B |= (1 << CS12);    // prescaler
  TCCR1B |= (1 << CS11);    // prescaler 
  //TCCR1B |= (1 << CS10);    // prescaler
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
  interrupts(); 
}

ISR(TIMER1_OVF_vect)        // interrupt service routine 
{
  TCNT1 = timerCounter;   // preload timer
  digitalWrite(outPin, !digitalRead(outPin));
}

void loop(){
  sensorVal = analogRead(inPin);
  sensorVal = (sensorVal / sensorCalibrate) * outputRange + outputMin;
  Serial.println(sensorVal);
  timerCounter = sensorVal;
}
