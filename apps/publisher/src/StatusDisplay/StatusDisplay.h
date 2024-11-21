#pragma once

#include <Adafruit_SSD1306.h>

#include "config.h"
#include "EnergyStatus/EnergyStatus.h"
#include "NetworkUpdatePublisher/NetworkUpdatePublisher.h"

// Default logo
static const unsigned char PROGMEM logo_bmp[] = { 0b00000000, 0b11000000,
                                                  0b00000001, 0b11000000,
                                                  0b00000001, 0b11000000,
                                                  0b00000011, 0b11100000,
                                                  0b11110011, 0b11100000,
                                                  0b11111110, 0b11111000,
                                                  0b01111110, 0b11111111,
                                                  0b00110011, 0b10011111,
                                                  0b00011111, 0b11111100,
                                                  0b00001101, 0b01110000,
                                                  0b00011011, 0b10100000,
                                                  0b00111111, 0b11100000,
                                                  0b00111111, 0b11110000,
                                                  0b01111100, 0b11110000,
                                                  0b01110000, 0b01110000,
                                                  0b00000000, 0b00110000 };

class StatusDisplay {
private:
  Adafruit_SSD1306 display = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
public:
  void begin();
  void print(EnergyStatus& status, NetworkUpdatePublisher& networkUpdatePublisher);
};