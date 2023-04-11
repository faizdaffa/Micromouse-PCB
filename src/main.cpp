#include <Arduino.h>
// #include "motor.h"
#include "compas.h"
#include "ultrasonik.h"
#include "PID.h"
#include "bluetooth.h"

long previousMillis = 0;

void setup()
{
  Serial.begin(9600);
  // Serial.println("START");
  // mpu6050_innit();
  // motor_innit();
  bluetooth_innit();
}

void loop()
{
  // if (millis() - previousMillis > 1000)
  // {
  //   sendToApp("1");
  //   previousMillis = millis();
  // }

  bluetooth.println("12");
}
