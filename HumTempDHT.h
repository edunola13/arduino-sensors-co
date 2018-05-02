#ifndef HumTempDHT_h
#define HumTempDHT_h
//#include "WConstants.h"
#include <Arduino.h>
#include "vendor/igniteit/arduino-basic-oo/ElementAbstract.h"
#include <Adafruit_Sensor.h>
#include <DHT.h>

class HumTempDHT: public SensorInterface{
  protected:
    uint8_t pin;	
    float temp, hum;    

  public: 
    /*DHT11 11, DHT22 22, DHT21 21, AM2301 21*/
	uint8_t type;
  
    HumTempDHT();
    HumTempDHT(uint8_t pin, uint8_t type);
    void begin();
    void begin(uint8_t pin, uint8_t type);
    void stop();
    
	uint8_t getCode();
	
    uint8_t getPin();
    void setPin(uint8_t pin);
    float getHumedad();
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
