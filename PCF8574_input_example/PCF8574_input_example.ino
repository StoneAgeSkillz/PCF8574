/*
  PCF8574_input_example.ino - input example for use with PCF8574 I2C expander library.
  https://github.com/StoneAgeSkillz/PCF8574
  Created by StoneAgeSkillz
  Released into the public domain.
*/
// I2C BUS
#include <Wire.h>
#include <PCF8574.h>

#define EXP_ADDRESS 0x20
PCF8574 expander(EXP_ADDRESS); // PCF8574 @ address 0b0100/A2/A1/A0, to GND = 0, to LOGIC (3,3V;5V) = 1

#define DELAY 50

void setup() {
  Serial.begin(115200);// for debug in serial monitor
  Serial.println("serial start");

  Wire.begin(); // i2c
  Serial.println("i2c start");

  expander.setP( 8, LOW); // setPin(PCF8574 address, pin number or 8 = ALL pins, set pin state to HIGH/LOW);
  // set pins to LOW, if triggered to GND logical 0 goes to 1
  // if pins set to HIGH, if triggered to + logical 1 goes to 0
}

void loop() {

  for(int i = 0; i < 8; i++){
    Serial.print("P"+String(i)+": ");
    Serial.print(String(expander.readP(i))); // read input i, returns 0 or 1
    Serial.print("/");
  }

  Serial.println(String(expander.readP(8), BIN)); // read all inputs, returns 0-255

}
