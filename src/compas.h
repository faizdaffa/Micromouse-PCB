/* Get tilt angles on X and Y, and rotation angle on Z
    Angles are given in degrees
  License: MIT
*/
#include <Arduino.h>
#include "Wire.h"
#include <MPU6050.h>

MPU6050 mpu;
float timeStep = 0.01;
unsigned long timer = 0;
float dataYaw = 55;

void mpu6050_innit()
{
  Wire.begin();
  while (!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  mpu.calibrateGyro();
  mpu.setThreshold(3);
}

//float getGyroZ()
// {
//   Vector norm = mpu.readNormalizeGyro();
//   dataYaw = dataYaw + norm.ZAxis * timeStep;
//   Serial.println(dataYaw);
//   delay((timeStep * 1000) - (millis() - timer));
//   return dataYaw;
// }
