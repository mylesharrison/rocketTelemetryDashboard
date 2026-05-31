import os
def csv_logger(line):
    with open("telemetry.csv", "a") as f:
        # If the file is new, write the header
        if os.path.getsize("telemetry.csv") == 0:
            f.write("time_ms,ax,ay,az,gx,gy,gz,mpu_temp,bme_temp,altitude,pressure,humidity\n")
            # Unpack the telemetry data
        f.write(line + "\n")