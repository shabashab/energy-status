#include "EnvironmentMeter.h"

EnvironmentMeter::EnvironmentMeter() {}

void EnvironmentMeter::begin() {
  if (this->sht3x.begin()) {
    this->status = ENVIRONMENT_METER_ACTIVE;
  } else {
    this->status = ENVIRONMENT_METER_NOT_FOUND;
  }
}

void EnvironmentMeter::collect() {
  if(this->status == ENVIRONMENT_METER_NOT_FOUND) {
    return;
  }
  
  bool measured = this->sht3x.measure();

  if(measured) {
    this->last_humidity = this->sht3x.humidity();
    this->last_temp = this->sht3x.temperature();
    this->status = ENVIRONMENT_METER_ACTIVE;
  }
}

float EnvironmentMeter::getTemperature() {
  return this->last_temp;
}

float EnvironmentMeter::getHumidity() {
  return this->last_humidity;
}

EnvironmentMeterStatus EnvironmentMeter::getStatus() {
  return this->status;
}

void EnvironmentMeter::debugPrint(Stream& stream) {
  stream.print("Status: ");
  stream.print(this->status);

  if(this->status == ENVIRONMENT_METER_ACTIVE) {
    stream.print(" / Temperature: ");
    Serial.print(this->getTemperature());
    stream.print(" / Humidity: ");
    Serial.print(this->getHumidity());
  }
}