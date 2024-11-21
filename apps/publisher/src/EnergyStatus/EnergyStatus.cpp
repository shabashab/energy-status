#include "EnergyStatus.h"

EnergyStatus::EnergyStatus() {}

void EnergyStatus::begin() {
  this->environmentMeter.begin();
}

void EnergyStatus::collect() {
  this->powerMeter1.collect();
  this->powerMeter2.collect();
  this->environmentMeter.collect();
}

void EnergyStatus::debugPrint(Stream& stream) {
  stream.print("Power meter 1: ");
  this->powerMeter1.debugPrint(stream);

  stream.println();

  stream.print("Power meter 2: ");
  this->powerMeter2.debugPrint(stream);

  stream.println();

  stream.print("Environment: ");
  this->environmentMeter.debugPrint(stream);

  stream.println();
}

bool EnergyStatus::getPower1() {
  return this->powerMeter1.getPowerStatus();
}

bool EnergyStatus::getPower2() {
  return this->powerMeter2.getPowerStatus();
}

float EnergyStatus::getTemperature() {
  return this->environmentMeter.getTemperature();
}

float EnergyStatus::getHumidity() {
  return this->environmentMeter.getHumidity();
}