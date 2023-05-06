#include <Arduino.h>
#include "bluetooth.h"
#include "oled.h"
#include "button.h"
#include "fuzzy.h"

float size_number;
float kd;
float ki;
float kp;
float sp_sudut;
float ld, ls, lj, dd, ds, dj, rd, rs, rj;
String operation_status;
String status_pid;

void setup()
{
  Serial.begin(9600);
  // bluetooth.begin(9600);
  // size_number = change_size();
  // operation_status = changeOperation();
  // status_pid = doPID();
  // start_display();
  // for (uint16_t i = 0; i < noOfButtons; ++i)
  // {
  //   pinMode(buttonPins[i], INPUT_PULLUP);
  // }
}

// void loop()
// {
//   display.clearDisplay();
//   uint16_t choosen_channel = select_channel();
//   if (counter[0] == 1)
//   {
//     kp = control_value(kp, size_number, operation_status);
//   }
//   else if (counter[0] == 2)
//   {
//     ki = control_value(ki, size_number, operation_status);
//   }
//   else if (counter[0] == 3)
//   {
//     kd = control_value(kd, size_number, operation_status);
//   }
//   else if (counter[0] == 4)
//   {
//     operation_status = changeOperation();
//   }
//   else if (counter[0] == 5)
//   {
//     size_number = change_size();
//   }
//   else
//   {
//     status_pid = doPID();
//   }
//   display_selector(choosen_channel, kp, ki, kd, size_number, operation_status, status_pid);
//   display.display();
// }

void loop()
{
  read_ultrasonik();
  Serial.print("Kiri: ");
  Serial.print(kiri);
  Serial.print(" Depan: ");
  Serial.print(depan);
  Serial.print(" Kanan: ");
  Serial.print(kanan);
  //sp_sudut = defuzzifikasi();
  // ld = US_kiri_dekat();
  // ls = US_kiri_sedang();
  // lj = US_kiri_jauh();
  dd = US_depan_dekat();
  ds = US_depan_sedang();
  dj = US_depan_jauh();
  // rd = US_kanan_dekat();
  // rs = US_kanan_sedang();
  // rj = US_kanan_jauh();
  // Serial.print("      " + String(ld));
  // Serial.print(" " + String(ls));
  // Serial.print(" " + String(lj));
  Serial.print("      " + String(dd));
  Serial.print(" " + String(ds));
  Serial.println(" " + String(dj));
  // Serial.print("      " + String(rd));
  // Serial.print(" " + String(rs));
  // Serial.println(" " + String(rj));
  // Serial.print("    setpoint: ");
  // Serial.println(sp_sudut);
  delay(500);
}