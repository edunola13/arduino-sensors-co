#include <Arduino.h>
//#include "vendor/igniteit/arduino-basic-oo/ElementAbstract.h"
#include "../arduino-basic-oo/ElementAbstract.h"
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include "HumTempDHT.h"

HumTempDHT::HumTempDHT(){}
HumTempDHT::HumTempDHT(uint8_t pin, uint8_t type){
  this->begin(pin, type);
}
void HumTempDHT::begin(){
  pinMode(pin, INPUT_PULLUP);
  this->started= true;
}
void HumTempDHT::begin(uint8_t pin, uint8_t type){
  this->type= type;
  this->pin= pin;
  this->begin();
}
void HumTempDHT::stop(){
  this->started= false;
}

uint8_t HumTempDHT::getCode(){
	return 2;
}

uint8_t HumTempDHT::getPin(){
  return this->pin;
}
void HumTempDHT::setPin(uint8_t pin){
  this->pin= pin;
  this->begin();
}
float HumTempDHT::getHumedad(){
  return this->hum;
}
float HumTempDHT::getTemperatura(){
  return this->temp;
}

//Sensor Interface
void HumTempDHT::updateSensor(){
  DHT dht(pin, type);
  dht.begin();
  float h= dht.readHumidity();
  //Read temperature as Celsius (the default)
  float t= dht.readTemperature();
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Error Leyendo");
  }else{
    this->hum= h;
    this->temp= t;
  }
}
int HumTempDHT::getLevel(uint8_t type){
  if(type == 0){
	return this->hum;
  }else{
	return this->temp;
  }  
}

//JSON
void HumTempDHT::jsonProperties(String &value){
  value+= this->propertyToJson("st", String(this->started), false, false);
  value+= this->propertyToJson("pin", String(this->pin), false, false);
  value+= this->propertyToJson("ty", String(this->type), false, false);
  value+= this->propertyToJson("hum", String(this->hum), false, false);
  value+= this->propertyToJson("temp", String(this->temp), false, true);
}
void HumTempDHT::parseJson(String* json){
  String value= this->parseProperty(json, "pin");
  if(isNotNull(value)){
    this->setPin(value.toInt());
  }
  value= this->parseProperty(json, "ty");
  if(isNotNull(value)){
    this->type= value.toInt();
  } 
  value= this->parseProperty(json, "st");
  if(isNotNull(value)){
      if(value == "1"){
      this->begin();
    }else{
      this->stop();
    }
  }
}
//EEPROM
uint8_t HumTempDHT::positions(){
	return 5;
}
void HumTempDHT::readFromEeprom(int pos){
	uint8_t val= EEPROM.read(pos++);
	if(val == 1){
		this->pin= EEPROM.read(pos++);
		this->type= EEPROM.read(pos++);
		this->begin();
	}
}
void HumTempDHT::saveInEeprom(int pos){
	EEPROM.update(pos++, this->started);
	if(this->started){
		EEPROM.update(pos++, this->pin);
		EEPROM.update(pos++, this->type);
	}
}
