#include <Arduino.h>

#include "EnergyStatus/EnergyStatus.h"
#include "StatusDisplay/StatusDisplay.h"
#include "NetworkUpdatePublisher/NetworkUpdatePublisher.h"

#define PUBLISHING_DELAY 1000

EnergyStatus energyStatus;
StatusDisplay statusDisplay; 
NetworkUpdatePublisher networkUpdatePublisher;

uint32_t last_print_milis = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  energyStatus.begin();
  statusDisplay.begin();
  networkUpdatePublisher.begin();

  analogReadResolution(14);
}

void loop() {
  energyStatus.collect();
  networkUpdatePublisher.receive();

  if (millis() - last_print_milis > PUBLISHING_DELAY) {
    last_print_milis = millis();

    energyStatus.debugPrint(Serial);
    networkUpdatePublisher.debugPrint(Serial);

    statusDisplay.print(energyStatus, networkUpdatePublisher);
    bool result = networkUpdatePublisher.publish(energyStatus);
  }
}