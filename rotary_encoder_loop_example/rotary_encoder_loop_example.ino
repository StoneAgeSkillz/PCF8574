/*
  rotary_encoder_loop_example.ino - simple loop rotary encoder input example for use with PCF8574 I2C expander library.
  Bonus: https://github.com/StoneAgeSkillz/PCF8574/blob/master/rotary_encoder_interrupt_example/rotary_encoder_interrupt_example.png
  No need to wire INT for this example.
  https://github.com/StoneAgeSkillz/PCF8574
  Created by StoneAgeSkillz
  Released into the public domain.
*/

// I2C BUS
#include <Wire.h>
#include <PCF8574.h>

#define EXP_ADDRESS 0x20
#define PINA 6
#define PINB 7
#define BUTTON 5

ENCODER encoder(EXP_ADDRESS, PINA, PINB, BUTTON); // PCF8574 @ address 0b0100/A2/A1/A0, to GND = 0, to LOGIC (3,3V;5V) = 1

int i = 0; // position of rotary encoder

void setup() {
  Serial.begin(115200);// for debug in serial monitor
  Serial.println("serial start");

  Wire.begin(); // i2c
  Serial.println("i2c start");

  encoder.init(LOW); //sets pins A, B and BUTTON pin to LOW/HIGH
}

void loop() {
   i = i + encoder.getMovement();
   Serial.println(String(i)+"/button: "+String(encoder.getButton()));
}
