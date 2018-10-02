
import random, string, time
from Utility import *

PAYLOAD=(379 - 5)

def main():
    random.seed('lab1112')
    counter = 0
    sock = udpWrapper(10086, type='tx')
    data = ''.join([random.choice(string.ascii_uppercase+string.digits) for x in range(PAYLOAD)])
    data = bytearray(data, 'utf-8')

    num = 0
    while num<10000:
        num += 1
        # data = ''.join([random.choice(string.ascii_uppercase+string.digits) for x in range(PAYLOAD)])
        counter += 1
        tmp = bytearray(str(counter), 'utf-8')
        sock.send(data)
        # if num % 100 == 0:
        if True:
            a = [1+2 for x in range(6000)]
            pass
        # else:
        #     a = [1+2 for x in range(5800)]
        pass

    pass

if __name__ == '__main__':
    try:
        main()
    except Exception as e:
        print(e)
    finally:
        exit()