//#include "WProgram.h"
#include <Arduino.h>
#include "vendor/igniteit/arduino-basic-oo/ElementAbstract.h"
#include "AnalogSensor.h"
//
//ANALOG SENSOR
AnalogSensor::AnalogSensor() {
}
AnalogSensor::AnalogSensor(uint8_t pinA) {
  this->begin(pinA);
}
AnalogSensor::AnalogSensor(uint8_t pinA, uint8_t pinD) {
  this->begin(pinA, pinD);
}
void AnalogSensor::begin(uint8_t pinA) {  
  this->pinA= pinA;
  this->begin();
}
void AnalogSensor::begin(uint8_t pinA, uint8_t pinD) {  
  this->pinD= pinD;
  this->begin(pinA);
}
void AnalogSensor::begin() {
  pinMode(this->pinD, INPUT);
  this->started= true;
}
void AnalogSensor::stop() {
  this->started= false;
}

uint8_t AnalogSensor::getCode(){
	return 1;
}

bool AnalogSensor::getStarted(){
  return started;
}
uint8_t AnalogSensor::getPinA(){
  return pinA;
}
void AnalogSensor::setPinA(uint8_t pinA){
  this->pinA= pinA;
}
uint8_t AnalogSensor::getPinD(){
  return pinD;
}
void AnalogSensor::setPinD(uint8_t pinD){
  this->pinD= pinD;
  this->begin();
}
int AnalogSensor::getIn(){
  return in;
}

//Sensor Interface
void AnalogSensor::updateSensor(){
  in= analogRead(pinA);
}
int AnalogSensor::getLevel(uint8_t type){
  return this->in;
}

//JSON
void AnalogSensor::jsonProperties(String &value){
  value+= this->propertyToJson("st", String(this->started), false, false);
  value+= this->propertyToJson("pinA", String(this->pinA), false, false);
  value+= this->propertyToJson("pinD", String(this->pinD), false, false);
  value+= this->propertyToJson("ty", String(this->type), false, false);
  value+= this->propertyToJson("in", String(this->in), false, true);
}

void AnalogSensor::parseJson(String* json){
  String value= this->parseProperty(json, "pinA");
  if(isNotNull(value)){
    this->setPinA(value.toInt());
  }  
  value= this->parseProperty(json, "pinD");
  if(isNotNull(value)){
    this->setPinD(value.toInt());
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
uint8_t AnalogSensor::positions(){
	return 10;
}
void AnalogSensor::readFromEeprom(int pos){
	uint8_t val= EEPROM.read(pos++);
	if(val == 1){
		this->pinA= EEPROM.read(pos++);
		val= EEPROM.read(pos++);
		if(val <= 53){
			this->pinD= val;
		}
		this->type= EEPROM.read(pos++);
		this->begin();
	}
}
void AnalogSensor::saveInEeprom(int pos){
	EEPROM.update(pos++, this->started);
	if(this->started){
		EEPROM.update(pos++, this->pinA);
		EEPROM.update(pos++, this->pinD);
		EEPROM.update(pos++, this->type);
	}
}
