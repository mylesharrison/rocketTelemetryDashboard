#include <Arduino.h>
#include <Wire.h>

#include "sensors.h"
#include "logger.h"

unsigned long lastRead = 0;
const unsigned long readInterval = 100;

void setup() {
  Serial.begin(115200);
  delay(3000);
  Serial.println("BOOT");

  Wire.begin(41, 42);
  Serial.println("I2C STARTED");

  setupMPU();
  Serial.println("MPU SETUP COMPLETE");

  setupBME();
  Serial.println("BME SETUP COMPLETE");

  Serial.println("Sensors ready.");
  Serial.println("time,ax,ay,az,gx,gy,gz,mpuTemp,bmeTemp,altitude,pressure,humidity");

  setupLogger();
}

void loop() {
  if (millis() - lastRead >= readInterval) {
    lastRead = millis();
    
    String row = getTelemetryCSV();
    Serial.println(row);
    logTelemetryCSV(row);
  }
}