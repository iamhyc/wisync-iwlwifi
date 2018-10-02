
import random, string, time
from Utility import *

PAYLOAD=1500#(379 - 5)

def main():
    random.seed('lab1112')
    sock = udpWrapper(10086, type='tx')
    data = ''.join([random.choice(string.ascii_uppercase+string.digits) for x in range(PAYLOAD)])

    while True:
        # data = ''.join([random.choice(string.ascii_uppercase+string.digits) for x in range(PAYLOAD)])
        sock.send(bytes(data, 'utf-8'))
        a = [1+2 for x in range(5900)]
        pass

    pass

if __name__ == '__main__':
    try:
        main()
    except Exception as e:
        print(e)
    finally:
        exit()