from Utility import *
import queue, argparse

PROXY_PORT=[12306, 12307]
PROXY_ADDR=['192.168.3.2', '192.168.3.15']
RELAY_PORT = PROXY_PORT[0]
RELAY_ADDR = PROXY_ADDR[0]

def relayThread(q):
    global vargs
    count = 0
    sock_rx = udpWrapper(RELAY_PORT, type='rx')
    sock_tx = udpWrapper(RELAY_PORT, RELAY_ADDR)
    while True:
        # sock_tx.send(sock_rx.recv(1600))
        buf = sock_rx.recv(2048)
        sock_tx.send(buf)
        
        if vargs.DBG:
            count += 1
            print(count, len(buf))
        pass
    pass

def main():
    global vargs
    RELAY_PORT = PROXY_PORT[vargs.SYS_NO]
    RELAY_ADDR = PROXY_ADDR[vargs.SYS_NO]
    q = queue.Queue()

    tt = (
        startThread(target=relayThread, args=(q, )),
	)

    printh("CapMain", "Relay ON", "green")
    watchLoop(tt, hook=exit)
    pass

if __name__ == '__main__':
    global vargs
    try:
        parser = argparse.ArgumentParser(
            description='VLC Rx Data Daemon.')
        parser.add_argument('SYS_NO', nargs='?', type=int,
            help='the system index number.')
        parser.add_argument('--debug', dest='DBG', action='store_true', default=False,
            help='output debug message on the console.')
        vargs = parser.parse_args()

        main()
    except Exception as e:
        print(e)
    finally:
        exit()