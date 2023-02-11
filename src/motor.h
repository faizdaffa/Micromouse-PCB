#include <Arduino.h>

#define M1A 4
#define M1B 5
#define M1E 6
#define M2A 7
#define M2B 8
#define M2E 9

int pwm = 50;

void motor_innit()
{
    pinMode(M1A, OUTPUT);
    pinMode(M1B, OUTPUT);
    pinMode(M1E, OUTPUT);
    pinMode(M2A, OUTPUT);
    pinMode(M2B, OUTPUT);
    pinMode(M2E, OUTPUT);
}

void maju()
{
    digitalWrite(M1A, HIGH);
    digitalWrite(M1B, LOW);
    analogWrite(M1E, pwm);
    digitalWrite(M2A, HIGH);
    digitalWrite(M2B, LOW);
    analogWrite(M2E, pwm);
}

void mundur()
{
    digitalWrite(M1A, LOW);
    digitalWrite(M1B, HIGH);
    analogWrite(M1E, pwm);
    digitalWrite(M2A, LOW);
    digitalWrite(M2B, HIGH);
    analogWrite(M2E, pwm);
}

void putar_kiri()
{
    digitalWrite(M1A, HIGH);
    digitalWrite(M1B, LOW);
    analogWrite(M1E, pwm);
    digitalWrite(M2A, LOW);
    digitalWrite(M2B, HIGH);
    analogWrite(M2E, pwm);
}

void putar_kanan()
{
    digitalWrite(M1A, LOW);
    digitalWrite(M1B, HIGH);
    analogWrite(M1E, pwm);
    digitalWrite(M2A, HIGH);
    digitalWrite(M2B, LOW);
    analogWrite(M2E, pwm);
}

void stop()
{
    digitalWrite(M1A, LOW);
    digitalWrite(M1B, LOW);
    analogWrite(M1E, 0);
    digitalWrite(M2A, LOW);
    digitalWrite(M2B, LOW);
    analogWrite(M2E, 0);
}

void tes_motor()
{
    maju();   delay(1000);
    stop();   delay(1000);
    mundur(); delay(1000);
    stop();   delay(1000);
}