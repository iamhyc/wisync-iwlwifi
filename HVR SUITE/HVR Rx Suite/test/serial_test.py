
import serial
from serial.tools import list_ports

plist = list(list_ports.comports())
if len(plist) == 0:
    print('no serial port')
    exit()
    
com_name = list(plist[0])[0]
fd = serial.Serial(com_name, 115200, parity=serial.PARITY_EVEN, timeout=10)

print(fd.read(10))

fd.write(b'0123456789abcdefg')

fd.close()