#include <Arduino.h>

#include "EnergyStatus/EnergyStatus.h"
#include "StatusDisplay/StatusDisplay.h"

#define PUBLISHING_DELAY 1000

EnergyStatus energyStatus;
StatusDisplay statusDisplay; 

uint32_t last_print_milis = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  energyStatus.begin();
  statusDisplay.begin();

  analogReadResolution(14);
}

void loop() {
  energyStatus.collect();

  if (millis() - last_print_milis > PUBLISHING_DELAY) {
    last_print_milis = millis();

    energyStatus.debugPrint(Serial);
    statusDisplay.print(energyStatus);
  }
}