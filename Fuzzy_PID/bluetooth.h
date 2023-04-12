#include <SoftwareSerial.h>
SoftwareSerial bluetooth(12, 13);

void bluetooth_innit()
{
  bluetooth.begin(9600);
}

void sendToApp(String text)
{
    if (bluetooth.available())
    {
        String command = bluetooth.readString();
        Serial.println(command);
    }
}
