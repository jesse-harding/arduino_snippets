//behavior of each LED at each timer state
int led2[] = {1,0,0,0,0,0};
int led3[] = {0,1,0,0,0,1};
int led4[] = {0,0,1,0,1,0};
int led5[] = {0,0,0,1,0,0};

//current position in cycle
int cyclePos = 0;

//length of cycle
int cycleLength = 6;

//millis timer vars
unsigned long currentMillis = 0;
unsigned long prevMillis = 0;
int duration = 100;

void setup() {
  //not used in this example, but if you want to use serial, you'll need this
  Serial.begin(9600);

  //set pin modes (LEDs connected to pins 2 through 5 with current limiting resistors)
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
}

void loop() {
  currentMillis = millis();

  if (currentMillis > prevMillis + duration){
    cyclePos++;
    prevMillis = currentMillis;
  }

  //reset back to the first state in the cycle
  if (cyclePos >= cycleLength){
    cyclePos = 0;
  }
  
  //write values from the array to the LEDs
  digitalWrite(2, led2[cyclePos]);
  digitalWrite(3, led3[cyclePos]);
  digitalWrite(4, led4[cyclePos]);
  digitalWrite(5, led5[cyclePos]);
}
