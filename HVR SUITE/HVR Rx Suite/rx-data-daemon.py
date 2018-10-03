from sys import argv
from Utility import *
import queue

PROXY_PORT=[12306, 12307]
PROXY_ADDR=['192.168.3.2', '192.168.3.15']

DBG = 0
SYSNO = int(argv[1])
RELAY_PORT = PROXY_PORT[SYSNO]
RELAY_ADDR = PROXY_ADDR[SYSNO]

def relayThread(q):
    count = 0
    sock_rx = udpWrapper(RELAY_PORT, type='rx')
    sock_tx = udpWrapper(RELAY_PORT, RELAY_ADDR)
    while True:
        # sock_tx.send(sock_rx.recv(1600))
        buf = sock_rx.recv(2048)
        sock_tx.send(buf)
        
        if DBG:
            count += 1
            print(count, len(buf))
        pass
    pass

def main():
    q = queue.Queue()
    tt = (
        startThread(target=relayThread, args=(q, )),
	)

    printh("CapMain", "Relay ON", "green")
    watchLoop(tt, hook=exit)
    pass

if __name__ == '__main__':
    try:
        main()
    except Exception as e:
        print(e)
    finally:
        exit()