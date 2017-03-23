/*
  rotary_encoder_loop_example.ino - simple loop rotary encoder input example for use with PCF8574 I2C expander library.
  https://github.com/StoneAgeSkillz/PCF8574
  Created by StoneAgeSkillz
  Released into the public domain.  
*/

// I2C BUS
#include <Wire.h>
#include <PCF8574.h>

#define EXP_ADDRESS 0x20
PCF8574 expander(EXP_ADDRESS); // PCF8574 @ address 0b0100/A2/A1/A0, to GND = 0, to LOGIC (3,3V;5V) = 1


// ENCODER vars
#define PINA 7
#define PINB 6
#define BUTTON 5

boolean pin_A_prev_state; // saved state of pin A
boolean pin_B_prev_state; // saved state of pin B

volatile unsigned int encoder_pos = 0;


void setup() {
  Serial.begin(115200);// for debug in serial monitor
  Serial.println("serial start");

  Wire.begin(); // i2c
  Serial.println("i2c start");

  expander.setPin( 8, LOW); // setPin(PCF8574 address, pin number or 8 = ALL pins, set pin state to HIGH/LOW);
  // set pins to LOW, if triggered to GND logical 0 goes to 1
  // if pins set to HIGH, if triggered to + logical 1 goes to 0

}

void loop() {

  //get states
  int pin_A_state = expander.readPin(PINA);
  int pin_B_state = expander.readPin(PINB);

  if(pin_A_prev_state == 1 && pin_B_prev_state == 1){ //if they wereboth up in previous loop 
    if (pin_A_state == true && pin_B_state == false) { // if pin B is now down
        encoder_pos++;
      }
      if (pin_A_state == false && pin_B_state == true) { // if A is now down
        encoder_pos--;
      } 
      
      Serial.println(String(encoder_pos)); // if it counts in wrong direction, just switch pin A and B   
  }

  if(expander.readPin(BUTTON) == true){ Serial.println("BUTTON!");} // if setPin = HIGH, rewrite true to false

  //store states
  pin_A_prev_state = pin_A_state; 
  pin_B_prev_state = pin_B_state;
   
}
