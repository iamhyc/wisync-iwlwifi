
import time, struct
from Utility import *

T_S  = 1E6
T_MS = 1E3
T_US = 1E0

def main():
    t0, t1 = 0, 0
    sock_tx = udpWrapper(13333, argv[1])
    sock_rx = udpWrapper(12222, type='rx')
    
    ack_frame = struct.Struct('I')
    ctrl_frame = struct.Struct('III')
    period = 100*T_MS
    duration = 10*T_MS
    offset = int(argv[2]) * duration*T_MS

    buf = ctrl_frame.pack(period, offset, duration)
    while True:
        # sock_tx.send(buf)
        # time.sleep(1.0)
        # period 0, send ctrl
        t0 = time.time()
        sock_tx.send(buf)
        # period 1, recv echo
        sock_rx.recv(2048)
        t1 = time.time()
        # period 2
        raw = int((t1 - t0)/2*1E6)
        sock_tx.send(ack_frame.pack(raw))
        pass
    pass

if __name__ == '__main__':
    try:
        main()
    except Exception as e:
        print(e)
    finally:
        exit()