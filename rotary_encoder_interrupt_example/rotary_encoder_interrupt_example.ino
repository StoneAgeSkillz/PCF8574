/*
  rotary_encoder_interrupt_example.ino - rotary encoder input example  for use with PCF8574 I2C expander library.
  Utilizing interrupt to maximise performance. *If you can't impress them with you knowledge, baffle them with your bullshit.*
  Anyway, this is one way to do it.
  Bonus: https://github.com/StoneAgeSkillz/PCF8574/blob/master/rotary_encoder_interrupt_example/rotary_encoder_interrupt_example.png
  https://github.com/StoneAgeSkillz/PCF8574
  Created by StoneAgeSkillz
  Released into the public domain.
*/

// I2C BUS
#include <Wire.h>
#include <PCF8574.h>

#define EXP_ADDRESS 0x20
#define PINA 7
#define PINB 6
#define BUTTON 5
ENCODER encoder(EXP_ADDRESS, PINA, PINB, BUTTON); // PCF8574 @ address 0b0100/A2/A1/A0, to GND = 0, to LOGIC (3,3V;5V) = 1

int i = 0; // position of rotary encoder

// INTERRUPT
#define INT 0 //PCF8574 interrupt pin vired to INT pin on Arduino UNO (INT0 = pin 2), for more see Arduino pinout
volatile byte readExp = 0; // switch variable, "Do i have read the pins on PCF8574?"

void setup() {
  Serial.begin(115200);// for debug in serial monitor
  Serial.println("serial start");

  Wire.begin(); // i2c
  Serial.println("i2c start");

  encoder.init(LOW); //sets pins A, B and BUTTON pin to LOW/HIGH

  attachInterrupt(INT, expInterrupt, LOW); //attach interrupt to INT pin, what function to execute, trigger state
}

void loop() {

  if (readExp == 1) // if readExp is set, read expander
  {
    i = i + encoder.getMovement();
    Serial.println(String(i) + "/button: " + String(encoder.getButton()));
    readExp = 0;
    attachInterrupt(INT, expInterrupt, LOW); // attach again
  }

  // your code geos here
  // Serial.println("regular loop");
}

void expInterrupt()
{
  detachInterrupt(INT); // deactivate interrupt, so we don't interrupt our interruption
  readExp = 1;  // if pressed, interrupt sets readExp to 1, to read expander
  //Serial.println("INT");
}
