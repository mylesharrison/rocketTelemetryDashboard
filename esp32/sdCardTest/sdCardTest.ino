#include <SPI.h>
#include<SD.h>

const int CS_PIN = 5;

void setup() {
  Serial.begin(115200);

  if (!SD.begin(CS_PIN)){
    Serial.println("SD Card Failed");
    return;
  }

  Serial.println("SD card ready");

  File file = SD.open("/test.txt", FILE_WRITE);

  if (file) {
    file.println("Hello SD card");
    file.close();
    Serial.println("Wrote to file");
  } else {
    Serial.println("Could not open file");
  }

}

void loop() {
  // put your main code here, to run repeatedly:

}
