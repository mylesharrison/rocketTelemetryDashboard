import serial
PORT = "COM3"
BAUD = 115200

with serial.Serial(PORT, BAUD, timeout=1) as esp32:
    print(f"Connected to {PORT}. Press Ctrl+C to stop.")

    while True:
        line = esp32.readline().decode("utf-8", errors="ignore").strip()
                                       
        if line:
            print(line)