#Script description: Get Data (Temp and Hum) from Arduino
import serial
import time
import os

from getPort import port

arduino_port = port # Don't worry by the port
baud_rate = 9600 # Baudios
ser = serial.Serial(arduino_port, baud_rate, timeout=1)

time.sleep(2)

while True:
    data = ser.readline().decode('utf-8').rstrip()

    print(data)
    #if data:
        #humidity, temperature = data.split(",")