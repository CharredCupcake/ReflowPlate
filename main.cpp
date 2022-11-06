#include <Arduino.h>
#include "Thermistor.h"

//Thermistor vars
const size_t TEMP_PIN = A0;
const double RT0  = 10000;
const double B  = 3950;
const double T0  = 90 + 273.15;
const double VCC  = 5;
const double R  = 10000;
Thermistor T1(TEMP_PIN, T0, RT0, B, VCC, R);
//

//LED vars
const size_t RED_PIN  = 10;
const size_t YELLOW_PIN  = 9;
const size_t GREEN_PIN  = 8;
//

//Relay vars
const size_t RELAY_PIN = 5;
//

//Control vars
const double MAX_PREHEAT_TEMP = 110;
const double MAX_SOAK_TEMP = 140;
const double MAX_REFLOW_TEMP = 180;
const unsigned long REFLOW_TIME = 90000;
//

//Button vars
const size_t BUTTON_PIN = 4;
//

//Timer vars
unsigned long currentTime = 0;
unsigned long passedTime = 0;
long timeLeft = 0;
//

void setup() {
  Serial.begin(9600);
  pinMode(TEMP_PIN, INPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  digitalWrite(RELAY_PIN, HIGH);
  digitalWrite(RED_PIN, LOW);
  digitalWrite(YELLOW_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
}

void loop() {

  digitalWrite(RELAY_PIN, HIGH);
  while (digitalRead(BUTTON_PIN) == LOW)
  {
  }

  delay(150);
  Serial.println(T1.GetTempInC());
  digitalWrite(RED_PIN, HIGH);
  digitalWrite(RELAY_PIN, LOW);
  
  while (T1.GetTempInC() < MAX_PREHEAT_TEMP)
  {
    delay(500);
    Serial.println(T1.GetTempInC());
  }

  Serial.println(T1.GetTempInC());
  digitalWrite(YELLOW_PIN, HIGH);
  digitalWrite(RED_PIN, LOW);

  while (T1.GetTempInC() < MAX_SOAK_TEMP)
  {
    delay(500);
    Serial.println(T1.GetTempInC());
  }

  Serial.println(T1.GetTempInC());
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(YELLOW_PIN, LOW);

  timeLeft = REFLOW_TIME;
  while (timeLeft > 0)
  {
    currentTime = millis();
    if (T1.GetTempInC() >= MAX_REFLOW_TEMP - 15)
    {
      digitalWrite(RELAY_PIN, HIGH);
    }
    else
    {
      digitalWrite(RELAY_PIN, LOW);
    }
    delay(500);
    passedTime = millis() - currentTime;
    if (timeLeft - passedTime < 0)
    {
      timeLeft = 0;
      break;
    }
    timeLeft = timeLeft - passedTime;
    Serial.println(T1.GetTempInC());
    Serial.print("Time Left: ");
    Serial.println(timeLeft);
  }
  digitalWrite(GREEN_PIN, LOW);
}