#include <Arduino.h>
#include <ultrasonik.h>

float min[27];
float rule[27];


float A, B;

//Membership Function
float kiri_dekat [] = {0, 10, 20};
float kiri_sedang[] = {10, 20, 30};
float kiri_jauh  [] = {20, 30, 40};

float depan_dekat [] = {0, 10, 20};
float depan_sedang[] = {10, 20, 30};
float depan_jauh  [] = {20, 30, 40};

float kanan_dekat [] = {0, 10, 20};
float kanan_sedang[] = {10, 20, 30};
float kanan_jauh  [] = {20, 30, 40};

//Membership Function Output Sudut (Singleton)
float sudut_kiri  = -90;
float sudut_lurus = 0;
float sudut_kanan = 90;


//-----------Fuzzifikasi-----------
//Membership Function Input US_Kiri
float US_kiri_dekat()
{
 // untuk  kondisi kiri dekat
  if (kiri <= kiri_dekat[0])
  {
    return 1;
  }
  else if (kiri > kiri_dekat[1] && kiri <= kiri_dekat[2]) 
  {
    return (kiri_dekat[2] - kiri)/(kiri_dekat[2] - kiri_dekat[1]);
  }
  else if (kiri > kiri_dekat[2])
  {
    return 0;
  }
}
float US_kiri_sedang()
{
  // untuk kondisi kiri sedang
  if (kiri <= kiri_sedang[0])
  {
    return 0;
  }
  else if (kiri > kiri_sedang[0] && kiri <= kiri_sedang[1]) 
  {
    return (kiri - kiri_sedang[0])/(kiri_sedang[1] - kiri_sedang[0]);
  }
  else if (kiri > kiri_sedang[1] && kiri <= kiri_sedang[2]) 
  {
    return (kiri_sedang[2] - kiri)/(kiri_sedang[2] - kiri_sedang[1]);
  }
  else if (kiri > kiri_sedang[2])
  {
    return 0;
  }
}
float US_kiri_jauh()
{
  // untuk kondisi kiri jauh
  if (kiri <= kiri_jauh[0])
  {
    return 0;
  }
  else if (kiri > kiri_jauh[0] && kiri <= kiri_jauh[1]) 
  {
    return (kiri - kiri_jauh[0])/(kiri_jauh[1] - kiri_jauh[0]);
  }
  else if (kiri > kiri_jauh[1])
  {
    return 1;
  }
}

//Membership Function Input US_Depan
float US_depan_dekat()
{
 // untuk  kondisi depan dekat
  if (depan <= depan_dekat[1])
  {
    return 1;
  }
  else if (depan > depan_dekat[1] && depan <= depan_dekat[2]) 
  {
    return (depan_dekat[2] - depan)/(depan_dekat[2] - depan_dekat[1]);
  }
  else if (depan > depan_dekat[2])
  {
    return 0;
  }
}
float US_depan_sedang()
{
  // untuk kondisi depan sedang
  if (depan <= depan_sedang[0])
  {
    return 0;
  }
  else if (depan > depan_sedang[0] && depan <= depan_sedang[1]) 
  {
    return (depan - depan_sedang[0])/(depan_sedang[1] - depan_sedang[0]);
  }
  else if (depan > depan_sedang[1] && depan <= depan_sedang[2]) 
  {
    return (depan_sedang[2] - depan)/(depan_sedang[2] - depan_sedang[1]);
  }
  else if (depan > depan_sedang[2])
  {
    return 0;
  }
}
float US_depan_jauh()
{
  // untuk kondisi depan jauh
  if (depan <= depan_jauh[0])
  {
    return 0;
  }
  else if (depan > depan_jauh[0] && depan <= depan_jauh[1]) 
  {
    return (depan - depan_jauh[0])/(depan_jauh[1] - depan_jauh[0]);
  }
  else if (depan > depan_jauh[1])
  {
    return 1;
  }
}

//Membership Function Input US_Kanan
float US_kanan_dekat()
{
  // untuk  kondisi kanan dekat
  if (kanan <= kanan_dekat[1])
  {
    return 1;
  }
  else if (kanan > kanan_dekat[1] && kanan <= kanan_dekat[2]) 
  {
    return (kanan_dekat[2] - kanan)/(kanan_dekat[2] - kanan_dekat[1]);
  }
  else if (kanan > kanan_jauh[2])
  {
    return 0;
  }
}
float US_kanan_sedang()
{
  // untuk kondisi depan sedang
  if (kanan <= kanan_sedang[0])
  {
    return 0;
  }
  else if (kanan > kanan_sedang[0] && kanan <= kanan_sedang[1]) 
  {
    return (kanan - kanan_sedang[0])/(kanan_sedang[1] - kanan_sedang[0]);
  }
  else if (kanan > kanan_sedang[1] && kanan <= kanan_sedang[2]) 
  {
    return (kanan_sedang[2] - kanan)/(kanan_sedang[2] - kanan_sedang[1]);
  }
  else if (kanan > kanan_sedang[2])
  {
    return 0;
  }
}
float US_kanan_jauh()
{
  // untuk kondisi depan jauh
  if (kanan <= kanan_jauh[0])
  {
    return 0;
  }
  else if (kanan > kanan_jauh[0] && kanan <= kanan_jauh[1]) 
  {
    return (kanan - kanan_jauh[0])/(kanan_jauh[1] - kanan_jauh[0]);
  }
  else if (kanan > kanan_jauh[1])
  {
    return 1;
  }
}

//Min
float Min(float x, float y, float z) 
{
    float min = x;
    if (y < min)
    {
        min = y;
    }
    if (z < min) 
    {
        min = z;
    }
    return min;
}

//rule base
void rule_base()
{
    // Kiri	    Depan	Kanan	Sudut
    //--------------------------------
    // Dekat	Dekat	Dekat	90
    min [0]= Min(US_kiri_dekat(), US_depan_dekat(), US_kanan_dekat());
    rule[0]= sudut_kanan;
    // Dekat	Dekat	Sedang	90
    min [1]= Min(US_kiri_dekat(), US_depan_dekat(), US_kanan_sedang());
    rule[1]= sudut_kanan;
    // Dekat	Dekat	Jauh	90
    min [2]= Min(US_kiri_dekat(), US_depan_dekat(), US_kanan_jauh());
    rule[2]= sudut_kanan;
    // Dekat	Sedang	Dekat	0
    min [3]= Min(US_kiri_dekat(), US_depan_sedang(), US_kanan_dekat());
    rule[3]= sudut_lurus;
    // Dekat	Sedang	Sedang	0
    min [4]= Min(US_kiri_dekat(), US_depan_sedang(), US_kanan_sedang());
    rule[4]= sudut_lurus;
    // Dekat	Sedang	Jauh	90
    min [5]= Min(US_kiri_dekat(), US_depan_sedang(), US_kanan_jauh());
    rule[5]= sudut_kanan;
    // Dekat	Jauh	Dekat	0
    min [6]= Min(US_kiri_dekat(), US_depan_jauh(), US_kanan_dekat());
    rule[6]= sudut_lurus;
    // Dekat	Jauh	Sedang	0
    min [7]= Min(US_kiri_dekat(), US_depan_jauh(), US_kanan_sedang());
    rule[7]= sudut_lurus;
    // Dekat	Jauh	Jauh	0
    min [8]= Min(US_kiri_dekat(), US_depan_jauh(), US_kanan_jauh());
    rule[8]= sudut_lurus;
    // Sedang	Dekat	Dekat	-90
    min [9]= Min(US_kiri_sedang(), US_depan_dekat(), US_kanan_dekat());
    rule[9]= sudut_kiri;
    // Sedang	Dekat	Sedang	90
    min [10]= Min(US_kiri_sedang(), US_depan_dekat(), US_kanan_sedang());
    rule[10]= sudut_kanan;
    // Sedang	Dekat	Jauh	90
    min [11]= Min(US_kiri_sedang(), US_depan_dekat(), US_kanan_jauh());
    rule[11]= sudut_kanan;
    // Sedang	Sedang	Dekat	0
    min [12]= Min(US_kiri_sedang(), US_depan_sedang(), US_kanan_dekat());
    rule[12]= sudut_lurus;
    // Sedang	Sedang	Sedang	0
    min [13]= Min(US_kiri_sedang(), US_depan_sedang(), US_kanan_sedang());
    rule[13]= sudut_lurus;
    // Sedang	Sedang	Jauh	90
    min [14]= Min(US_kiri_sedang(), US_depan_sedang(), US_kanan_jauh());
    rule[14]= sudut_kanan;
    // Sedang	Jauh	Dekat	0
    min [15]= Min(US_kiri_sedang(), US_depan_jauh(), US_kanan_dekat());
    rule[15]= sudut_lurus;
    // Sedang	Jauh	Sedang	0
    min [16]= Min(US_kiri_sedang(), US_depan_jauh(), US_kanan_sedang());
    rule[16]= sudut_lurus;
    // Sedang	Jauh	Jauh	0
    min [17]= Min(US_kiri_sedang(), US_depan_jauh(), US_kanan_jauh());
    rule[17]= sudut_lurus;
    // Jauh	    Dekat	Dekat	-90
    min [18]= Min(US_kiri_jauh(), US_depan_dekat(), US_kanan_dekat());
    rule[18]= sudut_kiri;
    // Jauh	    Dekat	Sedang	-90
    min [19]= Min(US_kiri_jauh(), US_depan_dekat(), US_kanan_sedang());
    rule[19]= sudut_kiri;
    // Jauh	    Dekat	Jauh	90
    min [20]= Min(US_kiri_jauh(), US_depan_dekat(), US_kanan_jauh());
    rule[20]= sudut_kanan;
    // Jauh	    Sedang	Dekat	-90
    min [21]= Min(US_kiri_jauh(), US_depan_sedang(), US_kanan_dekat());
    rule[21]= sudut_kiri;
    // Jauh	    Sedang	Sedang	-90
    min [22]= Min(US_kiri_jauh(), US_depan_sedang(), US_kanan_sedang());
    rule[22]= sudut_kiri;
    // Jauh	    Sedang	Jauh	90
    min [23]= Min(US_kiri_jauh(), US_depan_sedang(), US_kanan_jauh());
    rule[23]= sudut_kanan;
    // Jauh	    Jauh	Dekat	0
    min [24]= Min(US_kiri_jauh(), US_depan_jauh(), US_kanan_dekat());
    rule[24]= sudut_kiri;
    // Jauh	    Jauh	Sedang	0
    min [25]= Min(US_kiri_jauh(), US_depan_jauh(), US_kanan_sedang());
    rule[25]= sudut_lurus;
    // Jauh	    Jauh	Jauh	0
    min [26]= Min(US_kiri_jauh(), US_depan_jauh(), US_kanan_jauh());
    rule[26]= sudut_lurus;
}


float defuzzifikasi()
{
    rule_base();
    A = 0;
    B = 0;
    for (int i = 1; i <= 26; i++)
    {
        A += rule[i] * min[i];
        B += min[i];
    }
    Serial.print("      rule: " + String(A));
    Serial.print(" min: " + String(B));
    return A / B;
}

