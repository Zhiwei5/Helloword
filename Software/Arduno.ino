 #define FLASH_RATE_HZ 2
 #define PWM_MAX 255
 #define interval 500      

 // global variables representing "state" across all functions
 // operating mode: 0 - off, 1 - bright, 2 - mid-bright, 3 - dim, 4 - flash
 int operating_mode = 1;
 volatile bool button_pushed_Result = HIGH;
 //int previous_button_state = 0;
 int PWM_OUT = 0;
 int PWM_OUT_State =0;
 int LedPin = 6;
 bool ledState = LOW;
 //int BUTTON_IN = 3;
 const int BatteryPin = 8;
 const int BatteryHighPIN = 11;
 const int BatteryLowPIN = 12;
 bool batteryState = LOW;
 unsigned long currentMillis;
 unsigned long previousMillis;
 
 
 // executed one-time at device startup
 void setup() {

    Serial.begin(9600); 
    pinMode(LedPin, OUTPUT);
    pinMode(BatteryPin, INPUT); 
    pinMode(BatteryHighPIN, OUTPUT);
    pinMode(BatteryLowPIN, OUTPUT);
    attachInterrupt(digitalPinToInterrupt(3), button_pushed, RISING);
    
    check_button_press();
    
    set_pwm_based_on_operating_mode();

    // define output (PWM) pin connected to LED

 }

 // continually-running loop
 // calls functions that are named as "actions"
 void loop(){

    currentMillis = millis();
     
     
     check_button_press();
     
     set_pwm_based_on_operating_mode();

     batteryState = digitalRead(batteryState);

     if (digitalRead(BatteryPin) == LOW)
        {  
        digitalWrite(BatteryLowPIN, HIGH); // indicate via LED
        digitalWrite(BatteryHighPIN, LOW);
      }
      if (digitalRead(BatteryPin) == HIGH){
        digitalWrite(BatteryHighPIN, HIGH); 
        digitalWrite(BatteryLowPIN, LOW);
      }
    Serial.println("operating mode is");
    Serial.println(operating_mode);
    //Serial.println(button_pushed_Result);
    //analogWrite(LedPin, 1);
 }



 void button_pushed() {
      button_pushed_Result =HIGH;
      //Serial.println("button is triggered");
     // BUTTON_PUSHED = TRUE;
 }
 
  void check_button_press() {
    if(button_pushed_Result == HIGH){
        if ( operating_mode <4){
            operating_mode++;
        }else{
            operating_mode=0;
        }
    }
    button_pushed_Result = LOW;
 }
 
 void set_pwm_based_on_operating_mode() {

     switch (operating_mode) {
         case 0:
             PWM_OUT = 0;
             analogWrite(LedPin, PWM_OUT);
             Serial.println("case 0");
             break;
         case 1:
             //PWM_OUT = PWM_MAX;
             analogWrite(LedPin, PWM_MAX);
             Serial.println("case 1");
             break;
         case 2:
             PWM_OUT = PWM_MAX/2;
             analogWrite(LedPin, PWM_OUT);
             Serial.println("case 2");
             break;
         case 3:
             PWM_OUT = PWM_MAX/4;
             analogWrite(LedPin, PWM_OUT);
             Serial.println("case 3");
             break;
         case 4:
             flash_the_light();
             Serial.println("case 4");
             break;
     }

 }

 void flash_the_light() {
    //Serial.println(currentMillis - previousMillis);
    if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
        previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (PWM_OUT < PWM_MAX) {
      PWM_OUT = PWM_MAX;
    } else {
      PWM_OUT = 0;
    }

    // set the LED with the ledState of the variable:
    analogWrite(LedPin, PWM_OUT);
  }
 }

