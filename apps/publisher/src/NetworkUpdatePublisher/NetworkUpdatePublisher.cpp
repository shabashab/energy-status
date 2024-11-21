#include "NetworkUpdatePublisher.h"

void NetworkUpdatePublisher::begin() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  gsm_serial.begin(9600);
  gsm_client.init();
  // gsm_client.setPhoneFunc(1);


  Serial.print("Set Phone Function... ");
  Serial.println(gsm_client.setPhoneFunc(1));
  //delay(1000);

  Serial.print("is Module Registered to Network?... ");
  Serial.println(gsm_client.isRegistered());
  //delay(1000);

  Serial.print("Signal Quality... ");
  Serial.println(gsm_client.signalQuality());
  //delay(1000);

  Serial.print("Operator Name... ");
  Serial.println(gsm_client.operatorNameFromSim());
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

  NetworkProvider provider = getProvider();

  if (provider == NETWORK_PROVIDER_WIFI) {
    if(!wifi_client.connect(WIFI_HOST, 80)) {
      this->sending = false;
      Serial.println("Couldn't connect to host");
      return false;
    }

    String body = createBody(energyStatus);

    wifi_client.print("POST ");
    wifi_client.print(WIFI_PATH);
    wifi_client.println(" HTTP/1.1");
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

  if (provider == NETWORK_PROVIDER_GSM) {
    String body = createBody(energyStatus);

    gsm_client.connect();
    gsm_client.post(GSM_URL, body, "text/plain");
    gsm_client.closeConn();
  }

  return false;
}

NetworkProvider NetworkUpdatePublisher::getProvider() {
  if (getWiFiStatus() == WL_CONNECTED) {
    return NETWORK_PROVIDER_WIFI;
  }

  if (gsm_client.isRegistered()) {
    return NETWORK_PROVIDER_GSM;
  }

  return NETWORK_PROVIDER_NONE;
}

void NetworkUpdatePublisher::debugPrint(Stream& stream) {
  stream.print("Network provider: ");
  stream.println(getProvider());

  stream.print("WiFi status: ");
  stream.println(getWiFiStatus());
}