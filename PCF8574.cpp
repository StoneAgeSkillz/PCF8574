/*
  PCF8574.cpp - PCF8574 I2C expander library.
	https://github.com/StoneAgeSkillz/PCF8574
  Created by StoneAgeSkillz
  Released into the public domain.
*/


#include "Arduino.h"
#include <Wire.h>
#include "PCF8574.h"

PCF8574::PCF8574(int address){
	_address = address;
}

// WRITE PART ////////////////////////////////////////////////////////////////////////

void PCF8574::i2cWrite(byte _data)
{
  Wire.beginTransmission(_address);
  Wire.write(_data);
  Wire.endTransmission();
}

void PCF8574::setP( int pin, int data){

  if(pin == 8){
    if(data == HIGH){ data = 255;}
    else{ data = 0;}
    i2cWrite(data);
  }
  else{
    if(data == LOW ){
      data = 1 << pin;

	  _expander_state = _expander_state & ~data ;
      i2cWrite(_expander_state);
    }
    else{
      data = 1 << pin;
      _expander_state = _expander_state | data ;
      i2cWrite(_expander_state);
    }
  }
}

void PCF8574::toggleP( int pin){
	if(pin < 8){
		_expander_state ^= (1 << pin);
		i2cWrite(_expander_state);
	}
}

// READ PART ////////////////////////////////////////////////////////////////////////

byte PCF8574::i2cRead()
{
  byte _data;
  Wire.requestFrom(_address, 1);
  if(Wire.available())
  {
    _data = Wire.read();
  }
  return _data;
}

int PCF8574::readP(int pin){
  int expReadData = 0;
	int filtr = 1;
  expReadData = i2cRead();

	if(pin < 8){
	  for(int i = 0; i < pin; i++){
			filtr *=2;
		}

		if((expReadData &= filtr) == 0){ expReadData = 0;}
		else{ expReadData = 1;}

	}

  return expReadData;
}

// Preinstantiate Objects //////////////////////////////////////////////////////

//PCF8574 expander = PCF8574(_address);
