#include "PowerMeter.h"

#define POWER_EXISTS_ACTIVATION_THRESHOLD 1000

PowerMeter::PowerMeter(pin_size_t read_pin) {
  this->pin = read_pin;
  this->avg.begin();
}

void PowerMeter::collect() {
  int value = analogRead(this->pin);
  avg.reading(value);
}

int PowerMeter::getAnalogValue() {
  return this->avg.getAvg();
}

bool PowerMeter::getPowerStatus() {
  return avg.getAvg() < POWER_EXISTS_ACTIVATION_THRESHOLD;
}