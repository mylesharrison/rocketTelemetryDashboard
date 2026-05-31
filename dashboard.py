import csvLogger
import livePlot
import serial
import os
import matplotlib.pyplot as plt

PORT = "COM3"
BAUD = 115200




# Open the serial port and read telemetry data
with serial.Serial(PORT, BAUD, timeout=1) as esp32:
    print(f"Connected to {PORT}. Press Ctrl+C to stop.")
    
    while True:
        # Read a line of telemetry data from the ESP32
        line = esp32.readline().decode("utf-8", errors="ignore").strip()                             
        if not line or line.startswith("time,"):
            continue
        # Split the line into components
        parts = line.split(",")
        if len(parts) != 12:
            continue
        
        # Unpack the telemetry data
        time_ms, ax, ay, az, gx, gy, gz, mpu_temp, bme_temp, altitude, pressure, humidity = parts

        #calls the csv logger and live plot functions
        csvLogger.csv_logger(line)
        livePlot.graphPlot(time_ms, altitude)

        #clears the console
        os.system("cls")

        # Display telemetry data in a readable format
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