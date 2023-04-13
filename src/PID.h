#include <Arduino.h>

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
void stop()
{
    digitalWrite(M1A, LOW);
    digitalWrite(M1B, LOW);
    analogWrite(M1E, 0);
    digitalWrite(M2A, LOW);
    digitalWrite(M2B, LOW);
    analogWrite(M2E, 0);
}

void pid(float yaw, float kp, float ki, float kd, uint16_t TIME_INTERVAL, uint16_t N_DATA)
{
    uint16_t count = 0;
    uint32_t previousMillis;
    while (count <= N_DATA)
    {
        if (millis() - previousMillis > TIME_INTERVAL)
        {

            digitalWrite(M1A, HIGH);
            digitalWrite(M1B, LOW);
            digitalWrite(M2A, HIGH);
            digitalWrite(M2B, LOW);

            error = sp - yaw;
            integralE = integralE + error;
            derivativeE = error - lastError;

            float P = kp * error;
            float I = (ki * integralE) * dt;
            float D = (kd / dt) * derivativeE;

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

            Serial.println("count : " + String(count));
            previousMillis = millis();
            count += 1;
        }
    }
}