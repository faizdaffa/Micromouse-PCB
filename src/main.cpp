#include <Arduino.h>
#include "motor.h"
#include "encoder.h"
#include "compas.h"
#include "ultrasonik.h"

void setup()
{
  Serial.begin(9600);
  Serial.println("START");
  motor_innit();
  mpu6050_innit();
  //encoder_innit();
}

void loop()
{
  read_ultrasonik();
  data_mpu6050();
  if      (z < -1.0) { putar_kiri();}
  else if (z > 1.0)  { putar_kanan();}
  else               { stop();}
}
