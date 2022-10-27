int buttonDuration = 0; //variable to store how long the button press lasted
int debouncedButton;
int buttonTime = 0; //the time that the button press begins
int prevButton = 1; //the previous state of the button 
void setup() {
  // put your setup code here, to run once:
 pinMode(2,INPUT_PULLUP); //set internal pull-up resistor so we don't need the 10k pull-down resistor
 Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  int buttonState = digitalRead(2); //read current button state (0 means pressed, 1 means not pressed)
  
if (buttonState == 0 && prevButton == 1){ //if the button has become pressed
  buttonTime = millis(); //store time of button press start
}
if (buttonState == 1 && prevButton == 0){ //if the button is released
  buttonDuration = millis() - buttonTime; //compare current time to the the time when the button was pressed
  if (buttonDuration > 20){ //if that duration of press is longer than a threshold (like debouncing)
    debouncedButton = buttonDuration; //assign debounced button data to another variable
    if (debouncedButton < 100){
      Serial.println("dot");
    }
    else{
      Serial.println("dash");
   }
  }
}
prevButton = buttonState; //update prevButton to the current state of the button

}
