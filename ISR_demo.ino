//an example of an interrupt service routine using timer1 on an arduino uno, for reference: https://www.instructables.com/id/Arduino-Timer-Interrupts/

//in this example, we will use timer1 to create a periodic event
//timer1 can count up to 65535, while timer0 and timer2 can only count up to 255
//we can either change the number at which we start counting (TCNT1)
//or we can change the number at which we stop counting and reset (OCR1A)

#define outPin 10 //define where our output LED is connected
#define inPin A0 //define where our input potentiometer is connected

float sensorVal; //variable to hold input data from the potentiometer
float timerPreload = 65000; //initialize with a fast value (this is the number that the count will start from in overflow mode)
float timerReset = 500; //initialize with a fast value (this is the number at which the count will end in compare match mode)
boolean mode = 0; // 0 for compare match mode (superior for most uses), 1 for overflow mode (inferior for most uses)
float dutyCycle = .5; //set duty cycle (only used in compare match mode) (low duty cycle makes for clearer interferometry)

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
  //  0     0     1     no prescaling (prescaler = 1)
  //  0     1     0     1/8 = prescaler
  //  0     1     1     1/64 = prescaler
  //  1     0     0     1/256 = prescaler
  //  1     0     1     1/1024 = prescaler


if (mode == 0){ //compare match mode
  TCCR1B |= (1 << WGM12); // turn on CTC mode
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare interrupt
  TCNT1 = 0;  //initialize timer at zero
  OCR1A = timerReset;  //initializing to a fast value (must be < 65536)
}

if (mode == 1){ //overflow mode
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
  if (digitalRead(outPin)){ //if the pin is currently receiving power, change timing for the next cycle to inverse of duty cycle (off time)
    OCR1A = timerReset * (1 - dutyCycle);
  }
  else{ //if the pin is not currently receiving power, change timing for the next cycle to duty cycle (on time)
    OCR1A = timerReset * dutyCycle;
  }
  digitalWrite(outPin, !digitalRead(outPin)); //toggle between supplying and not supplying power to output pin
}


void loop(){
  sensorVal = analogRead(inPin); //read data from potentiometer
  timerReset = map(sensorVal, 0, 1023, 65000, 500); //used for compare match mode
  timerPreload = map(sensorVal, 0, 1023, 25000, 65000); //used for overflow mode
  printInfo();
}

void printInfo(){
  if (mode == 0){
  Serial.println(timerReset)  ; //print number that timer counts to in compare match mode
  //in compare match mode, you can get real frequency: (prescaler * clock speed) / timerReset
  float realFrequency = (16000000.0 / 64.0 / timerReset); //won't be completely accurate without testing cpu clock speed
//  Serial.println(realFrequency);
  }
  if (mode == 1){
  Serial.println(timerPreload); //print number that timer counts from in overflow mode
  }
}
