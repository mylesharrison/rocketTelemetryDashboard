#include "logger.h"

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

#define SD_CS 47
#define SD_SCK 36
#define SD_MOSI 35
#define SD_MISO 34

SPIClass sdSPI(HSPI);
bool sdReady = false;

bool setupLogger(){
    sdSPI.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);
    Serial.println("SPI STARTED");

    if (!SD.begin(SD_CS, sdSPI)) {
        Serial.println("SD Card Initialization Failed!");
        sdReady = false;
        return false;
  }

    Serial.println("SD Card Ready.");
    sdReady = true;

    SD.remove("/telemetryData.csv");

    File file = SD.open("/telemetryData.csv", FILE_WRITE);

    if (!file) {
        Serial.println("Could not open telemetryData.csv");
        sdReady = false;
        return false;
    }

    file.println("time,ax,ay,az,gx,gy,gz,mpuTemp,bmeTemp,altitude,pressure,humidity");
    file.close();

    Serial.println("telemetryData.csv OK");
    return true;
}  
void logTelemetryCSV(const String& row) {
    if (!sdReady) {
        return;
    }

    File file = SD.open("/telemetryData.csv", FILE_APPEND);

    if (file) {
        file.println(row);
        file.close();
    } else {
        Serial.println("WARNING: Could not open telemetryData.csv during logging");
    }
}

