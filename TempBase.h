#ifndef TempBase_h
#define TempBase_h
//#include "WConstants.h"
#include <Arduino.h>
//#include "vendor/igniteit/arduino-basic-oo/ElementAbstract.h"
//#include "../arduino-basic-oo/ElementAbstract.h"
#include <ElementAbstract.h>

class TempBase: public SensorInterface {
  protected:
    uint8_t pinA;	
    float temp;

  public: 
    /*1 = LM35DZ, 2= TMP36*/
    uint8_t type;
  
    TempBase();
    TempBase(uint8_t pinA, uint8_t type);
    void begin();
    void begin(uint8_t pinA, uint8_t type);
    void stop();
  
	uint8_t getCode();
  
    uint8_t getPinA();
    void setPinA(uint8_t pinA);   
    float getTemperatura();    
    //SensorInterface
	void updateSensor();
	int getLevel(uint8_t type=0);
    //JsonInterface
    void jsonProperties(String &value);
    void parseJson(String* json);
	//EEPROM
	uint8_t positions();
	void readFromEeprom(int pos);
	void saveInEeprom(int pos);
};

#endif

