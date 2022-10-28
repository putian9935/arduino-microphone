import serial 
import time
import struct 
import matplotlib.pyplot as plt
from tqdm import tqdm 

ser = serial.Serial('COM9', 115200, timeout=0)

import numpy as np
from scipy.io.wavfile import write

def write_audio(data):
    rate = 16000
    scaled = np.int16(data / np.max(np.abs(data)) * 32767)
    write('test.wav', rate, scaled)

x = b''
ser.write(b'?')
tt = time.perf_counter()
for _ in tqdm(range(40)):
    while ser.in_waiting < 16382:
        pass 
    x += ser.read(16382)
print(len(x))
arr = struct.unpack(str(len(x)//2)+"h",x) 
write_audio(np.array(arr))