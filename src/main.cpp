#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "Encoder.h"
#include "Display.h"
#include "Menu.h"
#include "../../include/PinConfig.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

Encoder encoderHandler(EN_CLK, EN_DT, EN_SW);
Display display(lcd);
Menu menu("Main Menu");

MenuItem motorToggle("Motor", false, []() {
  Serial.println("Motor action executed");
});
MenuItem heaterToggle("Heater", false, []() {
  Serial.println("Heater action executed");
});
int temperature = 25;
MenuItem setTemperature("Set Temp", &temperature);
int speed = 0;
MenuItem setSpeed("Set Speed", &speed);
MenuItem exitItem("Exit", []() {
  Serial.println("Exit action executed");
});

void setup() {
  Serial.begin(9600);
  encoderHandler.begin();
  display.begin();
  // Add items to the menu
  menu.addItem(&motorToggle);
  menu.addItem(&heaterToggle);
  menu.addItem(&setTemperature);
  menu.addItem(&setSpeed);
  menu.addItem(&exitItem);

}

void loop() {
  
  if(display.needsUpdate()) display.render(menu);

  int32_t delta = encoderHandler.getDelta();
  if (delta != 0){
    display.setNeedsUpdate(true);
    menu.navigate(delta);
  }
  
  if (encoderHandler.wasClicked()) {
    menu.selec();
    display.setNeedsUpdate(true);
}
  
}