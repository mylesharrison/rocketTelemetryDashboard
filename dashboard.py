import serial
import os

PORT = "COM3"
BAUD = 115200

with serial.Serial(PORT, BAUD, timeout=1) as esp32:
    print(f"Connected to {PORT}. Press Ctrl+C to stop.")

    while True:
        line = esp32.readline().decode("utf-8", errors="ignore").strip()
                                       
        if not line or line.startswith("time,"):
            continue

        parts = line.split(",")

        if len(parts) != 12:
            continue
        
        time_ms, ax, ay, az, gx, gy, gz, mpu_temp, bme_temp, altitude, pressure, humidity = parts

        os.system("cls")

        print("=== Rocket Telemetry Dashboard ===")
        print(f"Time: {time_ms} ms")
        print(f"Altitude: {altitude} m")
        print(f"Pressure: {pressure} hPa")
        print(f"Humidity: {humidity} %")
        print(f"BME Temp: {bme_temp} °C")
        print(f"MPU Temp: {mpu_temp} °C")
        print()
        print(f"Accelerometer X/Y/Z: {ax} / {ay} / {az}")
        print(f"Gyroscope X/Y/Z: {gx} / {gy} / {gz}")