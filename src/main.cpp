#include <Arduino.h>
#include "motor.h"
#include "encoder.h"
#include "compas.h"

void setup()
{
  Serial.begin(9600);
  Serial.println("START");
  motor_innit();
  encoder_innit();
  mpu6050_innit();
}

void loop()
{
  data_mpu6050();
  if (z < -0.5)
  {
    putar_kiri();
  }
  else if (z > 0.5)
  {
    putar_kanan();
  }
  else
  {
    stop();
  }
}