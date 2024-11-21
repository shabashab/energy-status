#include "StatusDisplay.h"

void StatusDisplay::begin() {
  bool begin_status = display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);

  Serial.print("Display begin status: ");
  Serial.println(begin_status);
}

void StatusDisplay::print(EnergyStatus& status) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);

  display.print("Temperature: ");
  display.print(status.getTemperature());
  display.println("C");

  display.print("Humidity: ");
  display.print(status.getHumidity());
  display.println("%");

  display.print("Power 1: ");
  display.println(status.getPower1() ? "ON" : "OFF");

  display.print("Power 2: ");
  display.println(status.getPower2() ? "ON" : "OFF");

  display.display();
}