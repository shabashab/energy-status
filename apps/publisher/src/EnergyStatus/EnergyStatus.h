#pragma once

#include "config.h"

#include "PowerMeter/PowerMeter.h"
#include "EnvironmentMeter/EnvironmentMeter.h"

class EnergyStatus {
private:
  PowerMeter powerMeter1 = PowerMeter(POWER_METER_1_PIN);
  PowerMeter powerMeter2 = PowerMeter(POWER_METER_2_PIN);
  EnvironmentMeter environmentMeter = EnvironmentMeter();
public:
  EnergyStatus();
public:
  void collect();
  void begin();

  bool getPower1();
  bool getPower2();
  float getTemperature();
  float getHumidity();

  void debugPrint(Stream &stream);
};