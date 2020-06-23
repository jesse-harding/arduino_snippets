//an example of an interrupt service routine using timer1 on an arduino uno, for reference: https://www.instructables.com/id/Arduino-Timer-Interrupts/

//in this example, we will use timer1 to create a periodic event
//timer1 can count up to 65535, while timer0 and timer2 can only count up to 255
//we can either change the number at which we start counting (TCNT1)
//or we can change the number at which we stop counting and reset (OCR1A)

#define outPin 10 //define where our output LED is connected
#define inPin A0 //define where our input potentiometer is connected

float sensorVal; 
float outputRange = 20000;
float preloadMax = 65300;
float timerPreload = preloadMax; //initialize with a fast value
float timerReset = 1;
boolean mode = 0; // 0 for compare match mode, 1 for overflow mode
float dutyCycle = .5; //set duty cycle (only used in compare match mode)

void setup(){
  Serial.begin(9600);       //begin serial communication
  pinMode(outPin, OUTPUT);  //declare pin modes
  pinMode(inPin, INPUT);
  noInterrupts();           //initialize timer1 and temporarily disable all interrupts
  TCCR1A = 0;               //set all registers to zero
  TCCR1B = 0;

  //Prescalers will essentially divide our clock speed by a set amount (to slow down our periodic events to different ranges)
  //to change the range, we need to set these three bits to either 1 or 0 (they are all automatically set to zero at this point)
  //refer to the truth table below for prescaling amounts
  
//  TCCR1B |= (1 << CS12);
  TCCR1B |= (1 << CS11);
  TCCR1B |= (1 << CS10);

  //CS12  CS11  CS10
  //  0     0     0     no clock signal (timer stopped)
  //  0     0     1     no prescaling
  //  0     1     0     1/8 prescaling
  //  0     1     1     1/64 prescaling
  //  1     0     0     1/256 prescaling
  //  1     0     1     1/1024 prescaling


if (mode == 0){
  TCCR1B |= (1 << WGM12); // turn on CTC mode
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
  TCNT1 = 0;  //preload timer to zero
  OCR1A = 500;  //initializing to a fast value (must be < 65536)
}

if (mode == 1){
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
  TCNT1 = timerPreload;   // preload timer to maximum functional amount
}
  
  interrupts(); //reenable interrupts
}

// interrupt service routine for overflow mode
ISR(TIMER1_OVF_vect){
  TCNT1 = timerPreload;   // preload the timer based on user input
  digitalWrite(outPin, !digitalRead(outPin));
}

// interrupt service routine for compare match mode
ISR(TIMER1_COMPA_vect){

  //here we change the compare match value for when the signal is high versus low
  if (digitalRead(outPin)){
    OCR1A = timerReset * (1 - dutyCycle);
  }
  else{
    OCR1A = timerReset * dutyCycle;
  }
  digitalWrite(outPin, !digitalRead(outPin));
}


void loop(){
  sensorVal = analogRead(inPin); //read data from potentiometer
  timerReset = map(sensorVal, 0, 1023, 65000, 500); //used for compare match mode
  timerPreload = map(sensorVal, 0, 1023, 25000, 65000); //used for overflow mode
//  printInfo();
}

void printInfo(){
  if (mode == 0){
  Serial.println(timerReset);
  }
  if (mode == 1){
  Serial.println(timerPreload);
  }
}
