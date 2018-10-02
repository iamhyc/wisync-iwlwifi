
import socket, string, random

PAYLOAD=379

header_length = 2
sync_length = 3
data_length = PAYLOAD - header_length - sync_length

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.connect(('127.0.0.1', 10086))
counter = 0

while True:
	data = ''.join([random.choice(string.ascii_uppercase+string.digits) for x in range(data_length)])
	input('Tap to continue...')
	counter += 1;
	print(counter, data)
	sock.send(bytearray(data, 'utf-8'))
	pass