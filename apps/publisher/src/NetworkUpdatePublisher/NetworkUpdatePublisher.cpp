#include "NetworkUpdatePublisher.h"

void NetworkUpdatePublisher::begin() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
}

String NetworkUpdatePublisher::createBody(EnergyStatus& energyStatus) {
  String body = "";
  body += "temperature:";
  body += energyStatus.getTemperature();
  body += ";humidity:";
  body += energyStatus.getHumidity();

  return body;
}

wl_status_t NetworkUpdatePublisher::getWiFiStatus() {
  return (wl_status_t) WiFi.status();
}

void NetworkUpdatePublisher::receive() {
  if (wifi_client.available()) {
    char c = wifi_client.read();
    Serial.print(c);
  }

  if(!wifi_client.connected()) {
    this->sending = false;
  }
}

bool NetworkUpdatePublisher::publish(EnergyStatus& energyStatus) {
  if(this->sending) {
    Serial.println("Already sending");
    return false;
  }

  this->sending = true;

  if (getProvider() == NETWORK_PROVIDER_WIFI) {
    if(!wifi_client.connect("webhook.site", 80)) {
      this->sending = false;
      Serial.println("Couldn't connect to host");
      return false;
    }

    String body = createBody(energyStatus);

    wifi_client.println("POST /93610184-f1c9-4ffe-ae44-37ca499ce6c9 HTTP/1.1");
    wifi_client.println("Connection: close");
    wifi_client.println("Host: webhoook.site");
    wifi_client.print("Content-Length: ");
    wifi_client.print(body.length());
    wifi_client.println();
    wifi_client.println();
    wifi_client.println(body);

    Serial.println("Request sent");
  } else {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  } 

  return false;
}

NetworkProvider NetworkUpdatePublisher::getProvider() {
  if (getWiFiStatus() == WL_CONNECTED) {
    return NETWORK_PROVIDER_WIFI;
  }

  return NETWORK_PROVIDER_NONE;
}

void NetworkUpdatePublisher::debugPrint(Stream& stream) {
  stream.print("Network provider: ");
  stream.println(getProvider());

  stream.print("WiFi status: ");
  stream.println(getWiFiStatus());
}