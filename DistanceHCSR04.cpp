//#include "WProgram.h"
#include <Arduino.h>
#include "vendor/igniteit/arduino-basic-oo/ElementAbstract.h"
#include "DistanceHCSR04.h"

DistanceHCSR04::DistanceHCSR04() {
}
DistanceHCSR04::DistanceHCSR04(uint8_t pinEcho, uint8_t pinTrig) {
  this->begin(pinEcho, pinTrig);
}
void DistanceHCSR04::begin(uint8_t pinEcho, uint8_t pinTrig) {  
  this->pinEcho= pinEcho;
  this->pinTrig= pinTrig;
  this->begin();
}
void DistanceHCSR04::begin() {
  pinMode(this->pinTrig, OUTPUT);
  pinMode(this->pinEcho, INPUT);
  this->started= true;
}
void DistanceHCSR04::stop() {
  this->started= false;
}

uint8_t DistanceHCSR04::getCode(){
	return 4;
}

uint8_t DistanceHCSR04::getPinEcho(){
  return pinEcho;
}
void DistanceHCSR04::setPinEcho(uint8_t pinEcho){
  this->pinEcho= pinEcho;
  this->begin();
}
uint8_t DistanceHCSR04::getPinTrig(){
  return pinTrig;
}
void DistanceHCSR04::setPinTrig(uint8_t pinTrig){
  this->pinTrig= pinTrig;
  this->begin();
}

//Sensor Interface
void DistanceHCSR04::updateSensor(){
  digitalWrite(this->pinTrig, LOW);     // Nos aseguramos de que el trigger está desactivado
  delayMicroseconds(2);     // Para estar seguros de que el trigger ya está LOW
  digitalWrite(this->pinTrig, HIGH);    // Activamos el pulso de salida
  delayMicroseconds(10);    // Esperamos 10µs. El pulso sigue active este tiempo
  digitalWrite(this->pinTrig, LOW);     // Cortamos el pulso y a esperar el echo
  long duration;
  duration = pulseIn(this->pinEcho, HIGH);
  this->distance = duration / 2 / 29.1  ;
}
int DistanceHCSR04::getLevel(uint8_t type){
  return this->distance;
}

//JSON
void DistanceHCSR04::jsonProperties(String &value){
  value+= this->propertyToJson("st", String(this->started), false, false);
  value+= this->propertyToJson("pinE", String(this->pinEcho), false, false);
  value+= this->propertyToJson("pinT", String(this->pinTrig), false, false);
  value+= this->propertyToJson("di", String(this->distance), false, true);
}

void DistanceHCSR04::parseJson(String* json){
  String value= this->parseProperty(json, "pinE");
  if(isNotNull(value)){
    this->setPinEcho(value.toInt());
  } 
  value= this->parseProperty(json, "pinT");
  if(isNotNull(value)){
    this->setPinTrig(value.toInt());
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
uint8_t DistanceHCSR04::positions(){
	return 10;
}
void DistanceHCSR04::readFromEeprom(int pos){
	uint8_t val= EEPROM.read(pos++);
	if(val == 1){
		this->pinEcho= EEPROM.read(pos++);
		this->pinTrig= EEPROM.read(pos++);
		this->begin();
	}
}
void DistanceHCSR04::saveInEeprom(int pos){
	EEPROM.update(pos++, this->started);
	if(this->started){
		EEPROM.update(pos++, this->pinEcho);
		EEPROM.update(pos++, this->pinTrig);
	}
}
