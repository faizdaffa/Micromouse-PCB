#include <Arduino.h>
#include "parse.h"

const int length_sendData = 300;
const int length_receiveData = 3;
float receive_data[length_receiveData];
float yaw[length_sendData];
bool data_ready = false;

void setup()
{
  Serial.begin(9600);
  bluetooth.begin(9600);
}

void loop()
{
  if (bluetooth.available())
  {
    parse_data(receive_data, length_receiveData);
    for (size_t i = 0; i < length_sendData; i++)
    {
      yaw[i] = i;
      delay(10);
    }
    Serial.println("Finished PID");

    data_ready = true;
    if (data_ready)
    {

      for (size_t i = 0; i < length_sendData; i++)
      {
        Serial.println(yaw[i]);
        bluetooth.println(yaw[i]);
      }

      data_ready = false;
    }
  }
}
