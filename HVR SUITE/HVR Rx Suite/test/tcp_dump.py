import pydivert
from Utility import *

def dumpThread():
    w = pydivert.WinDivert("inbound and ip")
    w.open()
    while True:
        p = w.recv()
        w.send(p, recalculate_checksum=False)
        print(p.src_addr, p.dst_addr)
        pass
    pass

def main():
    tt = (
		startThread(target=dumpThread),
	)
    printh("CapMain", "TCP Dump Start", "green")
    watchLoop(tt, hook=exit)
    pass

if __name__ == '__main__':
    try:
        main()
    except Exception as e:
        print(e)
    finally:
        exit()