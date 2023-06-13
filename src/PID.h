#include <Arduino.h>
#include "compas.h"

#define M1A A0
#define M1B A1
#define M1E 3
#define M2A 6
#define M2B 4
#define M2E 5

int pwmA;
int pwmB;
int pwmKa;
int pwmKi;
int Upper = 150;
int Lower = 20;
int basePWM = 50;

float sp = 0.0;
float z = 0.0;
float dt = 0.001;
float error, integralE, derivativeE, lastError;
float PID;
float yaw[200];
int count = 0;

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
    analogWrite(M1E, basePWM);
    digitalWrite(M2A, HIGH);
    digitalWrite(M2B, LOW);
    analogWrite(M2E, basePWM);
}
void mundur()
{
    digitalWrite(M1A, LOW);
    digitalWrite(M1B, HIGH);
    analogWrite(M1E, basePWM);
    digitalWrite(M2A, LOW);
    digitalWrite(M2B, HIGH);
    analogWrite(M2E, basePWM);
}
void putar_kiri()
{
    digitalWrite(M1A, HIGH);
    digitalWrite(M1B, LOW);
    analogWrite(M1E, basePWM);
    digitalWrite(M2A, LOW);
    digitalWrite(M2B, HIGH);
    analogWrite(M2E, basePWM);
}
void putar_kanan()
{
    digitalWrite(M1A, LOW);
    digitalWrite(M1B, HIGH);
    analogWrite(M1E, basePWM);
    digitalWrite(M2A, HIGH);
    digitalWrite(M2B, LOW);
    analogWrite(M2E, basePWM);
}
void motor_stop()
{
    digitalWrite(M1A, LOW);
    digitalWrite(M1B, LOW);
    analogWrite(M1E, 0);
    digitalWrite(M2A, LOW);
    digitalWrite(M2B, LOW);
    analogWrite(M2E, 0);
}

void pid(float PID_parameter[], uint16_t TIME_INTERVAL, uint16_t TIME_PID)
{
    uint32_t previousMillis;
    while(millis() < TIME_PID){

        if (millis() - previousMillis > TIME_INTERVAL)
        {
            //getGyroZ();
            digitalWrite(M1A, HIGH);
            digitalWrite(M1B, LOW);
            digitalWrite(M2A, HIGH);
            digitalWrite(M2B, LOW);
            yaw[count] = dataYaw;
            count += 1;
            error = sp - dataYaw;
            integralE = integralE + error;
            derivativeE = error - lastError;

            float P = PID_parameter[0] * error;
            float I = (PID_parameter[1] * integralE) * dt;
            float D = (PID_parameter[2] / dt) * derivativeE;

            lastError = error;

            PID = P + I + D;

            pwmA = basePWM - PID;
            if (pwmA > Upper)
            {
                pwmA = Upper;
            }
            if (pwmA < Lower)
            {
                pwmA = Lower;
            }
            pwmKa = pwmA;

            pwmB = basePWM + PID;
            if (pwmB > Upper)
            {
                pwmB = Upper;
            }
            if (pwmB < Lower)
            {
                pwmB = Lower;
            }
            pwmKi = pwmB;

            analogWrite(M1E, pwmKa);
            analogWrite(M2E, pwmKi);

            previousMillis = millis();
        }
    }
}
