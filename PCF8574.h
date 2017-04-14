/*
  PCF8574.h - PCF8574 I2C expander library.
  https://github.com/StoneAgeSkillz/PCF8574
  Created by StoneAgeSkillz
  Released into the public domain.
*/

#ifndef PCF8574_h
#define PCF8574_h

#include "Arduino.h"

class PCF8574
{
  public:
    PCF8574(int expander_address);
  	void i2cWrite(byte data);
  	void setP(int pin, int set_to);
  	void toggleP( int pin);

  	byte i2cRead();
  	int readP(int pin);

  private:
  	int _address;
    int _expander_state; // temporary storrage of expander states

};

class ENCODER : public PCF8574
{
  private:
    bool pin_A_prev_state; // saved state of pin A
    bool pin_B_prev_state; // saved state of pin B
    int _pinA;
    int _pinB;
    int _button;
    //PCF8574(address);

  public:
    ENCODER(int expander_address, int pinA, int pinB, int button);
    void init(int state);
  	int getMovement();
    bool getButton();
    int _address;
    //using PCF8574::setP;

};

#endif
