#! /usr/bin/python
'''
Tx Capture Daemon.py
@author: Mark Hong
@level: debug
'''
import socket, time, queue, threading
from Utility import *
import pydivert
global w, iface_t
DBG = 0
PROXY_PORT = [10086, 10087]
PROXY_ADDR = ["192.168.0.220", "192.168.0.221"]

def get_raw(packet):
    return bytearray(packet.raw)

def run_thread(pkt_q):
    skt = list()
    for port in PROXY_PORT:
        skt.append(udpWrapper(port, type='tx'))

    count, length = 0, 0
    while True:
        p = pkt_q.get()
        udp_packet = get_raw(p)
        idx = PROXY_ADDR.index(p.dst_addr)
        skt[idx].send(udp_packet)

        count += 1
        length += len(udp_packet)
        remains = pkt_q.qsize()
        if DBG: print("%d\t%d\t%.2f MB"%(count, remains, length/1E6))
        pass #while
    pass #def

def put_thread(pkt_q, server_addr):
    global flt_ctrl

    flt_ctrl = "inbound and tcp"
    w = pydivert.WinDivert(flt_ctrl)
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
    global struct_helper
    global flt_ctrl, iface_t

    ##init parameter from json
    config = load_json('./config.json')
    iface_t = get_iface(config['cap_iface'])
    ipAddr = get_ipAddr(config['cap_iface'])
    
    ##socket & thread init
    pkt_q = queue.Queue()
    tt = (
        startThread(target=run_thread, args=(pkt_q, )),
        startThread(target=put_thread, args=(pkt_q, config['server_addr'])),
    )

    printh("CapMain", "Now on %s"%(str(iface_t)), "green")
    watchLoop(tt, hook=tx_exit)
    pass

def tx_exit():
    w.close()
    pass

if __name__ == '__main__':
    try:
        main()
    except Exception as e:
        printh("CapMain", e, 'red')
    finally:
        exit()
