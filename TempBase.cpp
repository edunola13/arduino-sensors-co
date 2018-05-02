//#include "WProgram.h"
#include <Arduino.h>
#include "vendor/igniteit/arduino-basic-oo/ElementAbstract.h"
#include "TempBase.h"

TempBase::TempBase(){}
TempBase::TempBase(uint8_t pinA, uint8_t type) {
  this->begin(pinA, type);
}
void TempBase::begin(uint8_t pinA, uint8_t type) {  
  this->pinA= pinA;
  this->type= type;
  this->begin();
}
void TempBase::begin() {
  this->started= true;
}
void TempBase::stop() {
  this->started= false;
}

uint8_t TempBase::getCode(){
	return 3;
}

uint8_t TempBase::getPinA(){
  return pinA;
}
void TempBase::setPinA(uint8_t pinA){
  this->pinA= pinA;
}
float TempBase::getTemperatura(){
  return temp;
}

//Sensor Interface
void TempBase::updateSensor(){
    int lectura = analogRead(this->pinA);
    float voltaje = 5.0 /1024 * lectura ;
    if(this->type == 1){
      //LM35DZ
      temp= voltaje * 100 ;
    }else{
      //TMP36
      temp= voltaje * 100 - 50;
    }
}
int TempBase::getLevel(uint8_t type){
  return this->temp;
}

//JSON
void TempBase::jsonProperties(String &value){
  value+= this->propertyToJson("st", String(this->started), false, false);
  value+= this->propertyToJson("pinA", String(this->pinA), false, false);
  value+= this->propertyToJson("ty", String(this->type), false, false);
  value+= this->propertyToJson("te", String(this->temp), false, true);
}

void TempBase::parseJson(String* json){
  String value= this->parseProperty(json, "pinA");
  if(isNotNull(value)){
    this->setPinA(value.toInt());
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
uint8_t TempBase::positions(){
	return 10;
}
void TempBase::readFromEeprom(int pos){
	uint8_t val= EEPROM.read(pos++);
	if(val == 1){
		this->pinA= EEPROM.read(pos++);
		this->type= EEPROM.read(pos++);
		this->begin();
	}
}
void TempBase::saveInEeprom(int pos){
	EEPROM.update(pos++, this->started);
	if(this->started){
		EEPROM.update(pos++, this->pinA);
		EEPROM.update(pos++, this->type);
	}
}
