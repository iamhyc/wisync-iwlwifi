#! /usr/bin/python3

import socket, time, queue, threading, argparse
from Utility import *
import pydivert

CAP_IFACE = 'Intel(R) Ethernet Connection I217-LM'
PROXY_PORT = [10086, 10087]
PROXY_ADDR = ['192.168.0.220', '192.168.0.221']

def get_raw(packet):
    return bytearray(packet.raw)

def run_thread(pkt_q):
    global vargs
    count, length = 0, 0
    skt = [udpWrapper(pt, type='tx') for pt in PROXY_PORT]
    
    while True:
        p = pkt_q.get()
        p_data = get_raw(p)
        idx = PROXY_ADDR.index(p.dst_addr)
        skt[idx].send(p_data)

        if vargs.DBG:
            count += 1
            length += len(p_data)
            remains = pkt_q.qsize()
            print("%d\t%d\t%.2f MB"%(count, remains, length/1E6))
            pass
        pass
    
    pass

def put_thread(pkt_q):
    w = pydivert.WinDivert("inbound and tcp")
    w.open()

    while True:
        packet = w.recv()
        if packet.dst_addr in PROXY_ADDR:
            pkt_q.put(packet)
        else:
            w.send(packet)
        pass
    pass

def main():
    pkt_q = queue.Queue()
    tt = (
        startThread(target=run_thread, args=(pkt_q, )),
        startThread(target=put_thread, args=(pkt_q, )),
    )

    printh('CapMain', 'Now on %s'%(str(CAP_IFACE)), 'green')
    watchLoop(tt, hook=exit)
    pass

if __name__ == '__main__':
    global vargs
    try:
        parser = argparse.ArgumentParser(
            description='VLC Tx Data Daemon.')
        parser.add_argument('--debug', dest='DBG', action='store_true', default=False,
            help='output debug message on the console.')
        vargs = parser.parse_args()

        main()
    except Exception as e:
        printh('CapMain', e, 'red')
    finally:
        exit()
