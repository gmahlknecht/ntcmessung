#include <Arduino.h>

const int SAMPLETIME = 100;
const int SENSOR_PIN = A6;
const int ADC_RESOLUTION_BIT = 10;
const int ADC_RES = pow(2, ADC_RESOLUTION_BIT);

//sensor data
const long RN = 2200;
const double TN = 298.15;
const long B = 3977;

const long R1 = 2200;
const double UB = 5.0;

int lastread = 0; //time of last measurement

void setup() {
  Serial.begin(115200);
}

void loop() {
  int nowMillis = millis();
  if (lastread + SAMPLETIME < nowMillis) {
    lastread = nowMillis;

    //1) Read analog values 0 - 1024
    int analog_value = analogRead(SENSOR_PIN);

    //2) Spannung berechnen
    double us = UB / ADC_RES * analog_value;

    //3) Widerstand ermitteln
    long rs = (UB-us) * R1 / us;

    //4) Temperatur berechnen
    double tempC = B * TN / ( B + log((double)rs / RN) * TN) - 273.15;
    
    Serial.print(">avalue:");
    Serial.println(analog_value);
    Serial.print(">vs:");
    Serial.println(us);
    Serial.print(">rs:");
    Serial.println(rs);
    Serial.print(">temp:");
    Serial.println(tempC);
  }
}
