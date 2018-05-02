//#include "WProgram.h"
#include <Arduino.h>
//#include "vendor/igniteit/arduino-basic-oo/ElementAbstract.h"
#include "../arduino-basic-oo/ElementAbstract.h"
#include "DigitalSensor.h"
//
//ANALOG SENSOR
DigitalSensor::DigitalSensor() {
}
DigitalSensor::DigitalSensor(uint8_t pin) {
  this->begin(pin);
}
void DigitalSensor::begin(uint8_t pin) {  
  this->pin= pin;
  this->begin();
}
void DigitalSensor::begin() {
  pinMode(this->pin, INPUT);
  this->started= true;
}
void DigitalSensor::stop() {
  this->started= false;
}

uint8_t DigitalSensor::getCode(){
	return 5;
}

bool DigitalSensor::getStarted(){
  return started;
}
uint8_t DigitalSensor::getPin(){
  return pin;
}
void DigitalSensor::setPin(uint8_t pin){
  this->pin= pin;
}
int DigitalSensor::getIn(){
  return in;
}

//Sensor Interface
void DigitalSensor::updateSensor(){
  in= digitalRead(pin);
}
int DigitalSensor::getLevel(uint8_t type){
  return this->in == HIGH ? 1 : -1;
}

//JSON
void DigitalSensor::jsonProperties(String &value){
  value+= this->propertyToJson("st", String(this->started), false, false);
  value+= this->propertyToJson("pin", String(this->pin), false, false);
  value+= this->propertyToJson("ty", String(this->type), false, false);
  value+= this->propertyToJson("in", String(this->in), false, true);
}

void DigitalSensor::parseJson(String* json){
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
uint8_t DigitalSensor::positions(){
	return 10;
}
void DigitalSensor::readFromEeprom(int pos){
	uint8_t val= EEPROM.read(pos++);
	if(val == 1){
		this->pin= EEPROM.read(pos++);
		this->type= EEPROM.read(pos++);
		this->begin();
	}
}
void DigitalSensor::saveInEeprom(int pos){
	EEPROM.update(pos++, this->started);
	if(this->started){
		EEPROM.update(pos++, this->pin);
		EEPROM.update(pos++, this->type);
	}
}
