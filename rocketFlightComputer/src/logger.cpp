#include "logger.h"

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

#define SD_CS 47
#define SD_SCK 36
#define SD_MOSI 35
#define SD_MISO 34

SPIClass sdSPI(FSPI);
bool sdReady = false;

void setupLogger(){
    sdSPI.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);
    Serial.println("SPI STARTED");

    if (!SD.begin(SD_CS, sdSPI)) {
        Serial.println("SD Card Initialization Failed!");
        return;
  }

    Serial.println("SD Card Ready.");
    sdReady = true;

    SD.remove("/telemetryData.csv");

    File file = SD.open("/telemetryData.csv", FILE_WRITE);

    if (file) {
        file.println("time,ax,ay,az,gx,gy,gz,mpuTemp,bmeTemp,altitude,pressure,humidity");
        file.close();
        Serial.println("telemetryData.csv Ready.");
  } else {
    Serial.println("Could not open telemetryData.csv!");
  }
}  
void logTelemetryCSV(String row){
    if (sdReady) {
    File file = SD.open("/telemetryData.csv", FILE_APPEND);

    if (file) {
        file.println(row);
        file.close();
    } else {
      Serial.println("Could not open file!");
        }
    }
}

