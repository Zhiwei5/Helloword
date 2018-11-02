 #define FLASH_RATE_HZ 2
 #define BUTTON_IN 2
 #define PWM_MAX 255
 #define interval 500      

 // global variables representing "state" across all functions
 // operating mode: 0 - off, 1 - bright, 2 - mid-bright, 3 - dim, 4 - flash
 int operating_mode = 0;
 // int button_pushed = 0;
 volatile bool button_pushed = TRUE;
 int previous_button_state = 0;
 int PWM_OUT = 0;
 int LedPin = 6;
 bool ledState = FALSE

 // executed one-time at device startup
 void setup() {

    Serial.begin(9600); 
    pinMode(LedPin, OUTPUT);
    attachInterrupt(BUTTON_IN, button_pushed, RISING);
    // define output (PWM) pin connected to LED

 }

 // continually-running loop
 // calls functions that are named as "actions"
 void loop(){

     unsigned long currentMillis = millis();
     check_for_button_press();
     
     set_pwm_based_on_operating_mode();

     shine_led();
     button_pushed = FALSE;
 }

 void set_pwn_based_on_operating_mode() {

     switch (operating_mode) {
         case 0:
             PWM_OUT = 0;
             analogWrite(LedPin, PWM_OUT);
         case 1:
             PWM_OUT = PWM_MAX;
             analogWrite(LedPin, PWM_OUT);
         case 2:
             PWN_OUT = int(PWM_MAX/2);
             analogWrite(LedPin, PWM_OUT);
         case 3:
             PWN_OUT = int(PWM_MAX/4);
             analogWrite(LedPin, PWM_OUT);
         case 4:
             flash_the_light();
     }

 }

 void button_pushed() {
      button_pushed = TRUE;
     // BUTTON_PUSHED = TRUE;
 }

 void flash_the_light() {

    if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
        previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == FALSE) {
      ledState = TRUE;
    } else {
      ledState = FALSE;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
  }
 }


 void check_button_press() {
    if(button_pushed == TRUE){
        if ( operating_mode <4){
            operating_mode++;
        }
        else{
            operating_mode=0;
        }
    }
 }