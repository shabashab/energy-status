#include <Arduino.h>
#include <movingAvg.h>

#define MOVING_AVERAGE_SAMPLES_COUNT 256

class PowerMeter {
private:
  movingAvg avg = movingAvg(MOVING_AVERAGE_SAMPLES_COUNT);
  pin_size_t pin;
public:
  PowerMeter(pin_size_t read_pin);
public:
  void collect();
  int getAnalogValue();
  bool getPowerStatus();
};
