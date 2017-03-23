// I2C BUS
#include <Wire.h>
#include <PCF8574.h>

#define EXP_ADDRESS 0x20
PCF8574 expander(EXP_ADDRESS); // PCF8574 @ address 0b0100/A2/A1/A0, to GND = 0, to LOGIC (3,3V;5V) = 1

#define DELAY 50

void setup() {

  Wire.begin(); // i2c

  expander.setPin( 8, HIGH); // setPin(PCF8574 address, pin number or 8 = ALL pins, set pin state to HIGH/LOW); 
  delay(3000);
}

void loop() {
  for(int i = 8; i >= 0; i--){
    expander.setPin( i, HIGH);
    delay(DELAY);
  }

  expander.setPin( 8, HIGH);
  
  for(int i = 7; i >= 0; i--){
    expander.setPin( i, LOW);
    delay(DELAY);
  }
  
  for(int i = 0; i < 8; i++){
    expander.setPin( i, HIGH);
    delay(DELAY);
  }

  for(int i = 0; i < 8; i++){
    expander.setPin( i, LOW);
    delay(DELAY);
  }

  for(int x = 0; x < 8; x++){
    for(int i = 0; i < 10; i++){
    
    expander.setPin( x, LOW);
    delay(DELAY);
    expander.setPin( x, HIGH);
    delay(DELAY);
    }
    expander.setPin( x, LOW);
  }

  for(int i = 0; i < 8; i++){
    for(int x = 0; x < 8; x++){
      expander.togglePin( x);
      delay(DELAY);
    }
  }
}




