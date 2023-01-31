#include <Arduino.h>

#define ENC1 A7
#define ENC2 A6 
int ENC1_DATA;
int ENC2_DATA;

void encoder_innit()
{
  pinMode(ENC1,INPUT);
  pinMode(ENC2,INPUT);
}

void read_encoder()
{
  ENC1_DATA = digitalRead(ENC1); 
  ENC2_DATA = digitalRead(ENC2); 
  Serial.print(ENC1_DATA*5); 
  Serial.print(" ");
  Serial.print(ENC2_DATA*5);
  Serial.println();
}