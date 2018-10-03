# Usage: python sim_ctrl_kai.py [client_number]
import serial
from serial.tools import list_ports
import time, struct
from Utility import *

T_S  = 1E6
T_MS = 1E3
T_US = 1E0
S_LIST = list(list_ports.comports())

def serial_init(idx):
    if len(S_LIST) <= idx: return -1
    
    com_name = list(S_LIST[idx])[0]
    fd = serial.Serial(com_name, 115200, parity=serial.PARITY_EVEN)
    return fd

def ctrlThread(idx):
    fd = serial_init(idx)
    if fd==0:
        print('No Serial Connected!')
        return

    t0, t1 = 0, 0
    ack_frame = struct.Struct('I')
    ctrl_frame = struct.Struct('III')
    period   = int(100.000*T_MS) #NOTE: static data
    duration = int(90.000*T_MS) #NOTE: static data
    offset   = idx * duration
    duration = period-offset if idx==1 else duration

    buf = ctrl_frame.pack(period, offset, duration)

    while True:
        # period 0, send ctrl
        t0 = time.time()
        fd.write(buf)

        # # period 1, recv echo
        # fd.read(len(buf)) #length same as ctrl_frame
        # t1 = time.time()
        
        # # period 2
        # raw = int((t1 - t0)/2*1E6)
        # fd.write(ack_frame.pack(raw))

        print('{} send (T-{period}, o-{offset}, d-{duration})...'.
            format(idx, period=period, offset=offset, duration=duration))
        time.sleep(300)
        pass
    pass

def main():
    tt = (
        startThread(target=ctrlThread, args=(0, )),
        # startThread(target=ctrlThread, args=(1, ))
    )
    printh("CtrlMain", "Serial On [2]", "green")
    watchLoop(tt, exit)
    pass

if __name__ == '__main__':
    try:
        main()
    except Exception as e:
        print(e)
    finally:
        exit()