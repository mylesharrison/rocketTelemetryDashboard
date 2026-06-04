#include <SPI.h>
#include <SD.h>

#define SD_CS 47
#define SD_SCK 35
#define SD_MOSI 34
#define SD_MISO 33

SPIClass sdSPI(FSPI);
bool sdReady = false;
void setup() {
  Serial.begin(115200);
  delay(3000);
  //error handler for 
  //No SD card inserted,
  //Wrong wiring,
  //Bad CS pin,Corrupted card, 
  //or SPI communication failure
  sdSPI.begin(SD_SCK,SD_MISO,SD_MOSI,SD_CS);
  if(!SD.begin(SD_CS, sdSPI)){
    Serial.println("SD Card Initialization Failed!");
    return;
  }
  Serial.println("SD Card Ready.");
  sdReady = true;
  SD.remove("/telemetryData.csv");
  File file = SD.open("/telemetryData.csv", FILE_WRITE);
  
  if(file){
    file.println("time,ax,ay,az,gx,gy,gz,mpuTemp,bmeTemp,altitude,pressure,humidity");
    file.close();
    Serial.println("telemetryData.csv Ready.");
    //error handler if unable to access file
  }else{
    Serial.println("Could not open telemetryData.csv!");
  }

}

void loop() {
  File file = SD.open("/telemetryData.csv", FILE_APPEND);

  if(file){
    file.println("0,0,0,0,0,0,0,0,0,0,0,0");
    file.close();
    Serial.println("Test row written.");
    //error handler if unable to access file
  }else{
    Serial.println("Could not open file!");
  }
  delay(1000);
}
