/*
  PCF8574.h - PCF8574 I2C expander library.
  Created by StoneAgeSkillz, 2017-09-03
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
	void setPin(int pin, int set_to);
	void togglePin( int pin);

	byte i2cRead();
	int readPin(int pin);

  private:
  	int _address;
    int _expander_state; // temporary storrage of expander states

};

#endif
=======
/*
  PCF8574.h - PCF8574 I2C expander library.
  Created by StoneAgeSkillz, 2017-09-03
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
	void setPin(int pin, int set_to);
	void togglePin( int pin);

	byte i2cRead();
	int readPin(int pin);

  private:
  	int _address;
    int _expander_state; // temporary storrage of expander states

};

#endif
