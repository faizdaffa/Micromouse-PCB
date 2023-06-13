#include <Arduino.h>
#include "parse.h"
#include "PID.h"

const int length_sendData = 300;
const int length_receiveData = 3;
float receive_data[length_receiveData]; // kp 0 ki 1 kd 2 
bool data_ready = false;

void setup()
{
  Serial.begin(9600);
  bluetooth.begin(9600);
  mpu6050_innit(); 
}

void loop()
{
  if (bluetooth.available())
  {
    parse_data(receive_data, length_receiveData);

    Serial.println("Start PID");
    pid(receive_data, 10, 10000);
    Serial.println("Finished PID");
    data_ready = true;
    if (data_ready)
    {
      for (size_t i = 0; i < count; i++)
      {
        Serial.println(yaw[i]);
        bluetooth.println(yaw[i]);
      }
      data_ready = false;
    }
  }
}
