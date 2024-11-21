#include <Arduino.h>

#include "EnergyStatus/EnergyStatus.h"

EnergyStatus energyStatus;

uint32_t last_print_milis = 0;

void setup() {
  Serial.begin(9600);

  analogReadResolution(14);
}

void loop() {
  energyStatus.collect();

  if (millis() - last_print_milis > 1000) {
    last_print_milis = millis();

    energyStatus.debugPrint(Serial);
  }
}