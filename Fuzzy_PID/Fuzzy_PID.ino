#include "bluetooth.h"
#include "pid.h"
#include "ultrasonik.h"

char data = 0;

void setup()
{
  Serial.begin(9600);
  Serial.println("START");
  mpu6050_innit();
  motor_innit();
  bluetooth_innit();
}

void loop()
{
  float yaw = getGyroZ();
  Serial.println(yaw);
  bluetooth.println(String(yaw));
  pid(yaw);
  readFromApp();
  // read_ultrasonik();
  // tes_motor();
  // delay(100);
}
