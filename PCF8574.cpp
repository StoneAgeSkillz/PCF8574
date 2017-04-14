/*
  PCF8574.cpp - PCF8574 I2C expander library.
	https://github.com/StoneAgeSkillz/PCF8574
  Created by StoneAgeSkillz
  Released into the public domain.
*/


#include "Arduino.h"
#include <Wire.h>
#include "PCF8574.h"

////////////////////////////////////////////////////////////////////////////////
// PFC8574
////////////////////////////////////////////////////////////////////////////////

PCF8574::PCF8574(int address){
	_address = address;
}

// WRITE PART //////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////
// ENCODER 
////////////////////////////////////////////////////////////////////////////////

bool pin_A_prev_state = true; // saved state of pin A
bool pin_B_prev_state = true; // saved state of pin B

ENCODER::ENCODER(int address, int pinA, int pinB, int button) : PCF8574(address) {
	_address = address;
  _pinA = pinA;
  _pinB = pinB;
  _button = button;
}

void ENCODER::init(int state){
	setP( _pinA, state);
	setP( _pinB, state);
	setP( _button, state);
}

int ENCODER::getMovement(){ // if it counts in wrong direction, just switch pin A and B
  //get states
  bool pin_A_state = readP(_pinA);
  bool pin_B_state = readP(_pinB);
  int encoder_pos = 0;

  if((pin_A_prev_state == true && pin_B_prev_state == true) && (pin_A_state == false or pin_B_state == false )){ //if they were both HIGH in previous loop
      if (pin_A_state == true && pin_B_state == false ){ // if pin B is now down
        encoder_pos--;
      }
      if (pin_A_state == false && pin_B_state == true) { // if A is now down
        encoder_pos++;
      }

      if(encoder_pos > 0){ encoder_pos = 1;}
      else if(encoder_pos < 0){ encoder_pos = -1;}
      else { encoder_pos = 0;}
  }

  //store states
  pin_A_prev_state = pin_A_state;
  pin_B_prev_state = pin_B_state;

  return encoder_pos;
  encoder_pos = 0;

  //if(expander.readPin(BUTTON) == true){ Serial.println("BUTTON!");} // if setPin = HIGH, rewrite true to false
}

bool ENCODER::getButton(){
	bool pin_BUTTON_state = readP(_button);
	return pin_BUTTON_state;
}
