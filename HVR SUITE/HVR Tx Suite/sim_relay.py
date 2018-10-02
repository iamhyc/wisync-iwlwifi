from sys import argv
from Utility import *
import queue
import pydivert

PROXY_PORT=[10086, 10087]
PROXY_ADDR=['192.168.0.3', '192.168.0.15']
# proxy_map={
#     '192.168.0.220': '192.168.0.3',
#     '192.168.0.221': '192.168.0.22'
# }
DBG = 0
SYSNO = int(argv[1])
RELAY_PORT = PROXY_PORT[SYSNO]
RELAY_ADDR = PROXY_ADDR[SYSNO]

def divertThread(q, iface_t):
    cnt = 0
    w = pydivert.WinDivert('false')
    w.open()
    while True:
        raw = q.get()
        v = memoryview(bytearray(raw))
        p = pydivert.Packet(v, iface_t, pydivert.Direction(0))
        p.dst_addr = RELAY_ADDR
        w.send(p, recalculate_checksum=True)

        cnt += 1
        # print(cnt, p.src_addr, p.dst_addr)
        pass
    pass

def relayThread(q, iface_t):
    count = 0
    sock_rx = udpWrapper(RELAY_PORT, type='rx')
    sock_tx = udpWrapper(12306, RELAY_ADDR) #FIXME: remind to remove this
    while True:
        count += 1
        buf = sock_rx.recv(2048)
        sock_tx.send(buf)
        # # q.put_nowait(buf)
        if DBG: print(count, len(buf))
        pass
    pass

def main():
    q = queue.Queue()
    config = load_json('./config.json')
    udp_port = config['udp_port']
    iface_t = get_iface(config['cap_iface'])
    tt = (
        # startThread(target=divertThread, args=(q, iface_t)),
		startThread(target=relayThread, args=(q, iface_t)),
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