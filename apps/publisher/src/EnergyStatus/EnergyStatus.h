#include "PowerMeter/PowerMeter.h"

#define POWER_METER_1_PIN 0
#define POWER_METER_2_PIN 1

class EnergyStatus {
private:
  PowerMeter powerMeter1 = PowerMeter(POWER_METER_1_PIN);
  PowerMeter powerMeter2 = PowerMeter(POWER_METER_2_PIN);
public:
  EnergyStatus();
public:
  void collect();

  bool getPower1();
  bool getPower2();

  void debugPrint(Stream &stream);
};