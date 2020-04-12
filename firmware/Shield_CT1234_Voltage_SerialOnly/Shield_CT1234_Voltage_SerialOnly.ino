
/* GNU GPL V3 Original Author: Trystan Lea */
#include "src/EmonLib/EmonLib.h"
#include "src/ArduinoUniqueID/ArduinoUniqueID.h"

EnergyMonitor ct1,ct2,ct3, ct4;

void printId() {
  for (size_t i = 0; i < UniqueIDsize; i++) {
    if (UniqueID[i] < 0x10) Serial.print("0");
    Serial.print(UniqueID[i], HEX);
  }
}

void setup() {
  Serial.begin(9600);
  while (!Serial) {}
  
  // Calibration factor = CT ratio / burden resistance = (100A / 0.05A) / 33 Ohms = 60.606
  ct1.current(1, 60.606);
  ct2.current(2, 60.606);                                     
  ct3.current(3, 60.606);
  ct4.current(4, 60.606); 
  
  // (ADC input, calibration, phase_shift)
  ct1.voltage(0, 300.6, 1.7);                                
  ct2.voltage(0, 300.6, 1.7);                                
  ct3.voltage(0, 300.6, 1.7);
  ct4.voltage(0, 300.6, 1.7);
  
  const int LEDpin = 9;
  pinMode(LEDpin, OUTPUT);                                              
  digitalWrite(LEDpin, HIGH);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.println();
  Serial.println();
  Serial.println();
}

void loop() {
  //digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  digitalWrite(LED_BUILTIN, HIGH);
  ct1.calcVI(20,1000);
  digitalWrite(LED_BUILTIN, LOW);
  printId();
  Serial.print(" ct1 ");
  Serial.println(ct1.realPower);

  digitalWrite(LED_BUILTIN, HIGH);
  ct2.calcVI(20,1000);
  digitalWrite(LED_BUILTIN, LOW);
  printId();
  Serial.print(" ct2 ");
  Serial.println(ct2.realPower);

  digitalWrite(LED_BUILTIN, HIGH);
  ct3.calcVI(20,1000);
  digitalWrite(LED_BUILTIN, LOW);
  printId();
  Serial.print(" ct3 ");
  Serial.println(ct3.realPower);

  digitalWrite(LED_BUILTIN, HIGH);
  ct4.calcVI(20,1000);
  digitalWrite(LED_BUILTIN, LOW);
  printId();
  Serial.print(" ct4 ");
  Serial.println(ct4.realPower);

  delay(1000);
}
