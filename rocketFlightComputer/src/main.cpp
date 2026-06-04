#include <Adafruit_BME280.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

#define SD_CS 47
#define SD_SCK 36
#define SD_MOSI 35
#define SD_MISO 34
#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme;
Adafruit_MPU6050 mpu;

SPIClass sdSPI(FSPI);
bool sdReady = false;

unsigned long lastRead = 0;
const unsigned long readInterval = 100;

void setupMPU();
void setupBME();
void printMPUData();
void printBMEData();
void printTelemetryCSV();

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

void loop() {
  if (millis() - lastRead >= readInterval) {
    lastRead = millis();
    printTelemetryCSV();
    delay(500);
  }
}

void printTelemetryCSV() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  String row = String(millis()) + "," +
               String(a.acceleration.x) + "," +
               String(a.acceleration.y) + "," +
               String(a.acceleration.z) + "," +
               String(g.gyro.x) + "," +
               String(g.gyro.y) + "," +
               String(g.gyro.z) + "," +
               String(temp.temperature) + "," +
               String(bme.readTemperature()) + "," +
               String(bme.readAltitude(SEALEVELPRESSURE_HPA)) + "," +
               String(bme.readPressure() / 100.0F) + "," +
               String(bme.readHumidity());

  Serial.println(row);

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

void printMPUData() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  Serial.print("Acceleration X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");

  Serial.print("Rotation X: ");
  Serial.print(g.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g.gyro.y);
  Serial.print(", Z: ");
  Serial.print(g.gyro.z);
  Serial.println(" rad/s");

  Serial.print("Temperature: ");
  Serial.print(temp.temperature);
  Serial.println(" degC");
}

void printBMEData() {
  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println(" °C");

  Serial.print("Pressure = ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");

  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");

  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");

  Serial.println();
}

void setupBME() {
  unsigned status = bme.begin(0x76);

  if (!status) {
    Serial.println("Failed to find BME280");
    while (1) delay(10);
  }

  Serial.println("BME280 Found");
}

void setupMPU() {
  if (!mpu.begin(0x68)) {
    Serial.println("Failed to find MPU6050");
    while (1) delay(10);
  }

  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}