#pragma once

#include <WiFiS3.h>
#include <WiFiClient.h>

#include "EnergyStatus/EnergyStatus.h"
#include "NetworkProvider.h"

class NetworkUpdatePublisher {
private:
  WiFiClient wifi_client;
  bool sending = false;
private:
  String createBody(EnergyStatus& energyStatus);
public:
  void begin();
  bool publish(EnergyStatus& energyStatus);
  void receive();

  wl_status_t getWiFiStatus();

  NetworkProvider getProvider();

  void debugPrint(Stream& stream);
};