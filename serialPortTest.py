from serial.tools import list_ports

for port in list_ports.comports():
    print(port.device)
    print(port.description)
    print()