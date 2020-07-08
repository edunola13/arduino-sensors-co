#include "AnalogSensor.h"
#include "DigitalSensor.h"
#include "DistanceHCSR04.h"
#include "HumTempDHT.h"
#include "TempBase.h"

AnalogSensor sen1(0);
DigitalSensor dig(2);
DistanceHCSR04 dis(3, 4);
HumTempDHT sen(5, 11);
TempBase tmp(2, 1);

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
