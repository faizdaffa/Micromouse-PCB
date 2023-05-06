#include <Arduino.h>
#include <NewPing.h>

#define TRIGGER_1  2 // Kiri
#define ECHO_1     7
#define TRIGGER_2  9 // Depan
#define ECHO_2     8
#define TRIGGER_3 11 // Kanan
#define ECHO_3    10
#define MAX      400
#define SONAR_NUM  3

NewPing sonar[SONAR_NUM] = 
{
    // Sensor object array.
    NewPing(TRIGGER_1, ECHO_1, MAX), // Each sensor's trigger pin, echo pin, and max distance to ping.
    NewPing(TRIGGER_2, ECHO_2, MAX),
    NewPing(TRIGGER_3, ECHO_3, MAX)
};

float kiri  = 0;
float depan = 0;
float kanan = 0;

void read_ultrasonik()
{
    delay(50);

    kiri  = sonar[0].ping_cm(); // Send ping, get ping time in microseconds (uS).
    depan = sonar[1].ping_cm(); // Send ping, get ping time in microseconds (uS).
    kanan = sonar[2].ping_cm(); // Send ping, get ping time in microseconds (uS).

    // Serial.print("Kiri: ");
    // Serial.print(kiri);
    // Serial.print("    Depan: ");
    // Serial.print(depan);
    // Serial.print("    Kanan: ");
    // Serial.println(kanan);
}