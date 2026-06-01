#include <SPI.h>
#include <SD.h>

const int CS_PIN = 5;
void setup() {
  Serial.begin(115200);
  //error handler for 
  //No SD card inserted,
  //Wrong wiring,
  //Bad CS pin,Corrupted card, 
  //or SPI communication failure
  if(!SD.begin(CS_PIN)){
    Serial.println("SD Card Initialization Failed!");
    return;
  }
  Serial.println("SD Card Ready.");
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
