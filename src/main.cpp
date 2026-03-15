#include <Arduino.h>
#include "Encoder.h"
#include"Display.h"
#include "Menu.h"
#include "../../include/PinConfig.h"

Encoder encoderHandler(EN_CLK, EN_DT, EN_SW);

int32_t counter=0;

void setup() {
  Serial.begin(9600);
  encoderHandler.begin();
  Serial.println(counter);
}

void loop() {
  int32_t delta = encoderHandler.getDelta();
  if (delta != 0){
    counter = constrain(counter + delta, 0, 100);
    Serial.println(counter);
  }
  
  if (encoderHandler.wasClicked()) Serial.println("Clicked");
  
  
}