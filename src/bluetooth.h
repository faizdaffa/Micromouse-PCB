#include <Arduino.h>
#include <SoftwareSerial.h>
SoftwareSerial bluetooth(12, 13);

void bluetooth_innit()
{
    bluetooth.begin(9600);
    // Serial.println("Bluetooth is able to use");
}
