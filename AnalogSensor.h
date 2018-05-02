#ifndef AnalogSensor_h
#define AnalogSensor_h
//#include "WConstants.h"
#include <Arduino.h>
//#include "vendor/igniteit/arduino-basic-oo/ElementAbstract.h"
#include "../arduino-basic-oo/ElementAbstract.h"

//PhotoResistance
//FlameSensor
//WaterLevelSensor
class AnalogSensor: public SensorInterface{
  protected:
    uint8_t pinA;
	uint8_t	pinD= -1;
    int in;

  public:
	uint8_t type;
	
	  AnalogSensor();
      AnalogSensor(uint8_t pinA);
	  AnalogSensor(uint8_t pinA, uint8_t pinD);
	  void begin();
	  void begin(uint8_t pinA);
	  void begin(uint8_t pinA, uint8_t pinD);
	  void stop();
	
	  uint8_t getCode();
    	
	  bool getStarted();
	  uint8_t getPinA();
	  void setPinA(uint8_t pinA);
	  uint8_t getPinD();
	  void setPinD(uint8_t pinD);
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
