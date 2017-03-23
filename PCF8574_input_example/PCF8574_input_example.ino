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

  expander.setPin( 8, HIGH); // setPin(PCF8574 address, pin number or 8 = ALL pins, set pin state to HIGH/LOW);
  // set pins to LOW, if triggered to GND logical 0 goes to 1
  // if pins set to HIGH, if triggered to + logical 1 goes to 0
}

void loop() {

  Serial.print(String(expander.readPin(5))); // read input 5, returns 0 or 1
  Serial.print("/");
  Serial.println(String(expander.readPin(8), BIN)); // read all inputs, returns 0-255

}
