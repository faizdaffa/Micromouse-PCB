/* Get tilt angles on X and Y, and rotation angle on Z
    Angles are given in degrees
  License: MIT
*/
#include "Wire.h"
#include <MPU6050_light.h>

MPU6050 mpu(Wire);
unsigned long timer = 0;
float z = 0;

void mpu6050_innit()
{
  Wire.begin();
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while (status != 0) { } // stop everything if could not connect to MPU6050
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(3000);
  mpu.calcOffsets(); // gyro and accelero
  Serial.println("Done!\n");
}

void data_mpu6050()
{
  mpu.update();
  if ((millis() - timer) > 10)  // print data every 10ms
  {
    // Serial.print("X : ");
    // Serial.print(mpu.getAngleX());
    // Serial.print(" Y : ");
    // Serial.print(mpu.getAngleY());
    z = mpu.getAngleZ();
    Serial.print(" Z : ");
    Serial.println(z);
    timer = millis();
  }
}