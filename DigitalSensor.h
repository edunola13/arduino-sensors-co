#ifndef DigitalSensor_h
#define DigitalSensor_h
//#include "WConstants.h"
#include <Arduino.h>
//#include "vendor/igniteit/arduino-basic-oo/ElementAbstract.h"
//#include "../arduino-basic-oo/ElementAbstract.h"
#include <ElementAbstract.h>

//PhotoResistance
//FlameSensor
//WaterLevelSensor
class DigitalSensor: public SensorInterface{
  protected:
    uint8_t pin;
    int in;

  public:
	  uint8_t type;
	
	  DigitalSensor();
    DigitalSensor(uint8_t pin);
	  void begin();
	  void begin(uint8_t pin);
	  void stop();
	
	  uint8_t getCode();
    	
	  bool getStarted();
	  uint8_t getPin();
	  void setPin(uint8_t pin);
    int getIn();
	
	  //SensorInterface
	  void updateSensor();
	  int getLevel(uint8_t type=0);
	  //JsonInterface
	  virtual void jsonProperties(String &value);
    virtual void parseJson(String* json);
	  //EEPROM
	  uint8_t positions();
	  void readFromEeprom(int pos);
	  void saveInEeprom(int pos);
};

#endif
