#include <Arduino.h>

#include "PowerMeter/PowerMeter.h"

PowerMeter powerMeter1(0);
PowerMeter powerMeter2(1);

uint32_t last_print_milis = 0;

void setup() {
  Serial.begin(9600);

  analogReadResolution(14);
}

void loop() {
  powerMeter1.collect();
  powerMeter2.collect();

  if (millis() - last_print_milis > 1000) {
    last_print_milis = millis();
    Serial.print("PowerMeter1: ");
    Serial.print(powerMeter1.getPowerStatus());
    Serial.print("/");
    Serial.print(powerMeter1.getAnalogValue());
    Serial.println();
    Serial.print(" PowerMeter2: ");
    Serial.print(powerMeter2.getPowerStatus());
    Serial.print("/");
    Serial.print(powerMeter2.getAnalogValue());
    Serial.println();
  }
  // put your main code here, to run repeatedly:
}