#pragma once

#include <WiFiS3.h>
#include <WiFiClient.h>
#include <GSMSimHTTP.h>
#include <SoftwareSerial.h>

#include "EnergyStatus/EnergyStatus.h"
#include "NetworkProvider.h"

class NetworkUpdatePublisher {
private:
  WiFiClient wifi_client;
  SoftwareSerial gsm_serial = SoftwareSerial(GSM_RX_PIN, GSM_TX_PIN);
  GSMSimHTTP gsm_client = GSMSimHTTP(gsm_serial);

  bool sending = false;
  bool last_gsm_connected = false;
private:
  String createBody(EnergyStatus& energyStatus);
public:
  void begin();
  bool publish(EnergyStatus& energyStatus);
  void updateGsmStatus();
  void receive();

  wl_status_t getWiFiStatus();

  NetworkProvider getProvider();

  void debugPrint(Stream& stream);
};