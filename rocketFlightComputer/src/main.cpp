#include <Arduino.h>
#include <Wire.h>

#include "sensors.h"
#include "logger.h"
#include "loraRadio.h"

unsigned long lastRead = 0;
const unsigned long readInterval = 1000;

bool systemReady = false;

void abortLaunch(const char* reason){
  Serial.println();
  Serial.println();
    Serial.println("********************************");
    Serial.println("FATAL PREFLIGHT FAILURE");
    Serial.println(reason);
    Serial.println("ABORT LAUNCH");
    Serial.println("********************************");

    while (true) {
        delay(1000);
    }
}

void setup() {
    Serial.begin(115200);
    delay(3000);

    Serial.println("BOOT");

    Wire.begin(41, 42);
    Serial.println("I2C STARTED");

    if (!setupMPU()) {
        abortLaunch("MPU6050 unavailable");
    }

    if (!setupBME()) {
        abortLaunch("BME280 unavailable");
    }

    if (!setupLogger()) {
        abortLaunch("SD logger unavailable");
    }

    if (!initLoRa()) {
        abortLaunch("LoRa radio unavailable");
    }

    

    systemReady = true;

    Serial.println();
    Serial.println("SYSTEM READY");
    Serial.println("time,ax,ay,az,gx,gy,gz,mpuTemp,bmeTemp,altitude,pressure,humidity");
}

void loop() {
    if (!systemReady) {
        delay(1000);
        return;
    }

    if (millis() - lastRead >= readInterval) {
        lastRead = millis();

        String row = getTelemetryCSV();

        Serial.println(row);
        logTelemetryCSV(row);

        if (!sendLoRaPacket(row)) {
            Serial.println("WARNING: LoRa packet failed. Continuing local logging.");
        }
    }
}