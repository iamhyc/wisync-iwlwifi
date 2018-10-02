
import socket, string, random
# from optparse import OptionParser
from Utility import *

length = 503
port = 10086
data = ''.join([random.choice(string.uppercase+string.digits) for x in xrange(length)])

def main():
	skt = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

	while True:
		raw_input('Tap to continue...')
		data = ''.join([random.choice(string.uppercase+string.digits) for x in xrange(length)])
		print(data)
		skt.sendto(data, ('127.0.0.1', port))
		pass
	pass

if __name__ == '__main__':
	try:
		main()
	except Exception as e:
		pass
	finally:
		exit()