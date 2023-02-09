#include <Arduino.h>
#include <NewPing.h>

#define TRIGGER_1  2 // Kanan
#define ECHO_1     3
#define TRIGGER_2 10 // Depan
#define ECHO_2    11
#define TRIGGER_3 12 // Kiri
#define ECHO_3    13
#define MAX      400
#define SONAR_NUM  3

NewPing sonar[SONAR_NUM] = {
    // Sensor object array.
    NewPing(TRIGGER_1, ECHO_1, MAX), // Each sensor's trigger pin, echo pin, and max distance to ping.
    NewPing(TRIGGER_2, ECHO_2, MAX),
    NewPing(TRIGGER_3, ECHO_3, MAX)
};

int kanan = 0;
int depan = 0;
int kiri = 0;

void read_ultrasonik()
{
    delay(50);

    kanan = sonar[0].ping_cm(); // Send ping, get ping time in microseconds (uS).
    depan = sonar[1].ping_cm(); // Send ping, get ping time in microseconds (uS).
    kiri  = sonar[2].ping_cm(); // Send ping, get ping time in microseconds (uS).

    Serial.print("Kanan: ");
    Serial.print(kanan);
    Serial.print("    Depan: ");
    Serial.print(depan);
    Serial.print("    Kiri: ");
    Serial.println(kiri);
}