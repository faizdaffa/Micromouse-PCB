#include <Arduino.h>
#include <Wire.h>
#include "bluetooth.h"
#include "oled2.h"
#include "button2.h"
#include "compas.h"

// Timers
// unsigned long timer = 0;
// float timeStep = 0.01;

// Pitch, Roll and Yaw values
float pitch = 0;
float roll = 0;
float yaw = 0;

float size_number;
float kd;
float ki;
float kp;
String operation_status;
String tab_status = ">";
String start_status = "GO!";
uint16_t choosen_tab = 0;


void setup()
{
  Serial.begin(9600);
  bluetooth.begin(9600);
  size_number = change_size();
  operation_status = changeOperation();
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
  
  if (choosen_tab == 0)
  {  
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
      choosen_tab = select_tab(); 
    }
  }
  else if (choosen_tab == 1)
  {
    if (counter[0] == 1)
    {
      operation_status = changeOperation();
    }
    else if (counter[0] == 2)
    {
      size_number = change_size();
    }
    else if (counter[0] == 3)
    {
      choosen_tab = select_tab(); 
    }
  }
  display_selector(choosen_tab, choosen_channel, kp, ki, kd, operation_status, size_number, tab_status, start_status);
  display.display();
}
/*
void setup() 
{
  Serial.begin(9600);

  // Initialize MPU6050
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  
  // Calibrate gyroscope. The calibration must be at rest.
  // If you don't want calibrate, comment this line.
  mpu.calibrateGyro();

  // Set threshold sensivty. Default 3.
  // If you don't want use threshold, comment this line or set 0.
  mpu.setThreshold(3);
}

void loop()
{
  timer = millis();

  // Read normalized values
  Vector norm = mpu.readNormalizeGyro();

  // Calculate Pitch, Roll and Yaw
  pitch = pitch + norm.YAxis * timeStep;
  roll = roll + norm.XAxis * timeStep;
  yaw = yaw + norm.ZAxis * timeStep;

  // Output raw
  Serial.print(" Pitch = ");
  Serial.print(pitch);
  Serial.print(" Roll = ");
  Serial.print(roll);  
  Serial.print(" Yaw = ");
  Serial.println(yaw);

  // Wait to full timeStep period
  delay((timeStep*1000) - (millis() - timer));
}*/