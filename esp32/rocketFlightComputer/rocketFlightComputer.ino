// Rocket Flight Computer
//Reads MPU6050 and BME280 sensor data
//Prints information to serial monitor
//logs data to sd card as a csv file

#include <Adafruit_BME280.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

#define SEALEVELPRESSURE_HPA (1013.25)
//global sensor variables updated by readSensors()
//used by printTelemetryCSV() and logDataToSD()
float ax, ay, az;
float gx, gy, gz;
float mpuTemp;
float bmeTemp;
float altitude;
float pressure;
float humidity;
//SD card chip select pin
const int CS_PIN = 5;

Adafruit_BME280 bme;
Adafruit_MPU6050 mpu;
//timing variables 
unsigned long lastRead = 0;
const unsigned long readInterval = 100; // read sensors every 100 ms

void setup() {
  Serial.begin(115200);
  setupMPU();
  setupBME();
  Serial.println("Sensors ready.");
  setupSDCard();
  Serial.println("time,ax,ay,az,gx,gy,gz,mpuTemp,bmeTemp,altitude,pressure,humidity");
}

void loop() {
  if (millis() - lastRead >= readInterval){
    lastRead = millis();
    //reads sensors and updates variables
    readSensors();
    //prints current variables
    printTelemetryCSV();
    //logs current variables
    logDataToSD();
  }
}
  void printTelemetryCSV(){
    Serial.print(millis());
    Serial.print(",");

    Serial.print(ax);
    Serial.print(",");

    Serial.print(ay);
    Serial.print(",");

    Serial.print(az);
    Serial.print(",");

    Serial.print(gx);
    Serial.print(",");

    Serial.print(gy);
    Serial.print(",");

    Serial.print(gz);
    Serial.print(",");

    Serial.print(mpuTemp);
    Serial.print(",");

    Serial.print(bmeTemp);
    Serial.print(",");

    Serial.print(altitude);
    Serial.print(",");

    Serial.print(pressure);
    Serial.print(",");
    Serial.println(humidity);
  }
  

void setupBME(){
    unsigned status;
    status = bme.begin(0x76);  
    if (!status) {
        Serial.println("Failed to find BME280");
        while (1) delay(10);
    }
    Serial.println("BME280 Found");
}
void setupMPU() {
  // Try to initialize!
  if (!mpu.begin(0x68)) {
    Serial.println("Failed to find MPU6050");
    while (1) delay(10);
  }
  Serial.println("MPU6050 Found!");
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  }

void setupSDCard(){
  if(!SD.begin(CS_PIN)){
    Serial.println("SD Card Initialization Failed!");
    return;
  }
  Serial.println("SD Card Ready.");
  //for testing, delete old file every time esp32 starts
  //prevents old test data from mixing with new test data.
  //needs rework
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

void logDataToSD(){
  File file = SD.open("/telemetryData.csv", FILE_APPEND);

  if(file){
    file.print(millis());
    file.print(",");
    file.print(ax);
    file.print(",");
    file.print(ay);
    file.print(",");
    file.print(az);
    file.print(",");
    file.print(gx);
    file.print(",");
    file.print(gy);
    file.print(",");
    file.print(gz);
    file.print(",");
    file.print(mpuTemp);
    file.print(",");
    file.print(bmeTemp);
    file.print(",");
    file.print(altitude);
    file.print(",");
    file.print(pressure);
    file.print(",");
    file.println(humidity);
    //close after each row to ensure data is saved if power is lost
    file.close();
  }else{
    Serial.println("Could not open telemetryData.csv!");
  }
}

void readSensors(){
  sensors_event_t a, g, temp;
  mpu.getEvent(&a,&g,&temp);

  ax = a.acceleration.x;
  ay = a.acceleration.y;
  az = a.acceleration.z;

  gx =g.gyro.x;
  gy = g.gyro.y;
  gz = g.gyro.z;

  mpuTemp = temp.temperature;

  bmeTemp = bme.readTemperature();
  altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
  pressure = bme.readPressure()/100.0F;
  humidity = bme.readHumidity();
}
