#include "sensors.h"

#include <Arduino.h>
#include <Adafruit_BME280.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
//#include <SD.h>

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme;
Adafruit_MPU6050 mpu;

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

bool setupBME() {
  unsigned status = bme.begin(0x76);

  if (!status) {
    Serial.println("BME280 init failed! Failed to find BME280");
    return false;
  }

  Serial.println("BME280 Found");
  return true;
}

bool setupMPU() {
  if (!mpu.begin(0x68)) {
    Serial.println("MPU6050 init failed! Failed to find MPU6050");
    return false;
  }

  Serial.println("MPU6050 Found");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  return true;
}

String getTelemetryCSV() {
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

  return row;
}