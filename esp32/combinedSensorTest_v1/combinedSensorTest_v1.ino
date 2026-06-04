// Basic demo for accelerometer readings from Adafruit MPU6050
#include <Adafruit_BME280.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme;
Adafruit_MPU6050 mpu;

unsigned long lastRead = 0;
const unsigned long readInterval = 100; // read sensors every 100 ms

void setup() {
  Wire.begin(41,42)
  Serial.begin(115200);
  setupMPU();
  setupBME();
  Serial.println("Sensors ready. ");
  Serial.println("time,ax,ay,az,gx,gy,gz,mpuTemp,bmeTemp,altitude,pressure,humidity");
}

void loop() {
  if (millis() - lastRead >= readInterval){
    lastRead = millis();
    //printBMEData();
    //printMPUData();
    //Serial.println();
    printTelemetryCSV();
    delay(500);
  }
}
  void printTelemetryCSV(){
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    Serial.print(millis());
    Serial.print(",");

    Serial.print(a.acceleration.x);
    Serial.print(",");

    Serial.print(a.acceleration.y);
    Serial.print(",");

    Serial.print(a.acceleration.z);
    Serial.print(",");

    Serial.print(g.gyro.x);
    Serial.print(",");

    Serial.print(g.gyro.y);
    Serial.print(",");

    Serial.print(g.gyro.z);
    Serial.print(",");

    Serial.print(temp.temperature);
    Serial.print(",");

    Serial.print(bme.readTemperature());
    Serial.print(",");

    Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.print(",");

    Serial.print(bme.readPressure()/ 100.0F);
    Serial.print(",");
    Serial.println(bme.readHumidity());
  }
  void printMPUData(){
    
    /* Get new sensor events with the readings */
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

  /* Print out the values */
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
void setupBME(){
    unsigned status;
    // default settings
    status = bme.begin(0x76);  
    // You can also pass in a Wire library object like &Wire2
    // status = bme.begin(0x76, &Wire2)
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
