#include <Arduino.h>

#include "EnergyStatus/EnergyStatus.h"
#include "StatusDisplay/StatusDisplay.h"
#include "NetworkUpdatePublisher/NetworkUpdatePublisher.h"

#define PRINTING_TIMEOUT 1000
#define SENDING_TIMEOUT 10000

EnergyStatus energyStatus;
StatusDisplay statusDisplay; 
NetworkUpdatePublisher networkUpdatePublisher;

uint32_t last_print_milis = 0;
uint32_t last_send_milis = 0;

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

  if (millis() - last_print_milis > PRINTING_TIMEOUT) {
    energyStatus.debugPrint(Serial);
    networkUpdatePublisher.debugPrint(Serial);

    statusDisplay.print(energyStatus, networkUpdatePublisher);

    last_print_milis = millis();
  }

  if(millis() - last_send_milis > SENDING_TIMEOUT) {
    bool result = networkUpdatePublisher.publish(energyStatus);
    
    last_send_milis = millis();
  }
}