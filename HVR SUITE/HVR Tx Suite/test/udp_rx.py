
import socket
from Utility import *

def workThread():
	sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	sock.bind(('', 10086))
	counter = 0

	while True:
		data = sock.recvfrom(2048)
		counter += 1
		print(counter)
		pass
	pass

def main():
	tt = (startThread(target=workThread), )
	watchLoop(tt)
	pass

if __name__ == '__main__':
	try:
		main()
	except Exception as e:
		print(e)
	finally:
		exit()

