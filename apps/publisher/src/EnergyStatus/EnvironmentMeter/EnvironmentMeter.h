#pragma once

#include <ArtronShop_SHT3x.h>

#include "EnvironmentMeterStatus.h"

class EnvironmentMeter {
private:
  ArtronShop_SHT3x sht3x = ArtronShop_SHT3x(SHT3X_ADDR0, &Wire);
  EnvironmentMeterStatus status = ENVIRONMENT_METER_AWAITING_BEGIN;

  float last_temp = 0;
  float last_humidity = 0;
public:
  EnvironmentMeter();
public:
  void begin();
  void collect();

  float getTemperature();
  float getHumidity();
  EnvironmentMeterStatus getStatus();

  void debugPrint(Stream& stream);
};