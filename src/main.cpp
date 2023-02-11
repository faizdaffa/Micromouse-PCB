#include <Arduino.h>
#include "encoder.h"
#include "compas.h"
#include "ultrasonik.h"
#include "PID.h"

char data = 0;

void setup()
{
  Serial.begin(9600);
  Serial.println("START");
  mpu6050_innit();
}

void loop()
{
  if(Serial.available() > 0 )
  {
    data = Serial.read();      //Read the incoming data and store it into variable
  }
  read_ultrasonik();
  data_mpu6050();
  pid();
}
