#include "bluetooth.h"
#include "oled.h"
#include "button.h"
#include <Arduino.h>

float size_number;
float kd;
float ki;
float kp;
String operation_status;
String status_pid;

void setup()
{
  Serial.begin(9600);
  bluetooth.begin(9600);
  size_number = change_size();
  operation_status = changeOperation();
  status_pid = doPID();
  start_display();
  for (uint16_t i = 0; i < noOfButtons; ++i)
  {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
}

void loop()
{
  display.clearDisplay();
  uint16_t choosen_channel = select_channel();
  if (counter[0] == 1)
  {
    kp = control_value(kp, size_number, operation_status);
  }
  else if (counter[0] == 2)
  {
    ki = control_value(ki, size_number, operation_status);
  }
  else if (counter[0] == 3)
  {
    kd = control_value(kd, size_number, operation_status);
  }
  else if (counter[0] == 4)
  {
    operation_status = changeOperation();
  }
  else if (counter[0] == 5)
  {
    size_number = change_size();
  }
  else
  {
    status_pid = doPID();
  }
  display_selector(choosen_channel, kp, ki, kd, size_number, operation_status, status_pid);
  display.display();
}