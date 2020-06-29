import csv
import serial
from pathlib import Path
import time

data_folder = Path("C:/Users/Amogh/DSA/jogging.txt")
port = '/dev/tty/S0'
ard = serial.Serial(port,9600)
time.sleep(2)
count = 0

def transmit_data(row):
    global ard, count
    row.append('$')
    for i in row:
        ard.write(row[i].encode())

with open(data_folder) as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    line_count = 0
    for row in csv_reader:
        if line_count == 0:
            print(f'Column names are {", ".join(row)}')
        else:
            if line_count==1:
                transmit_data(row)
        line_count += 1
    print(f'Processed {line_count} lines.')







