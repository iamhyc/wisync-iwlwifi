
import socket, random, string
from time import sleep

skt = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
skt.connect(('127.0.0.1', 10086))

GB=1024*1024*1024

counter = 0
random.seed(123456789)
raw_input('press ENTER to continue...')
with open('./text_tx.txt', 'wb') as f:
	while counter<(GB/127.00):
		txt = ''.join(random.choice(string.uppercase+string.digits) for x in xrange(125))
		txt += '\n\r'
		f.write(txt)
		skt.send(txt)
		counter += 1
		print(counter)
		# sleep(0.001)
		pass
	pass

# counter = 0
# raw_input('press ENTER to continue...')
# with open('./test.bin', 'rb+') as f:
# 	while True:
# 		tmp = f.read(127)
# 		if len(tmp)<127:
# 			padding = [255]*(127-len(tmp))
# 			tmp += str(bytearray(padding))
# 			counter += 1
# 			print(counter)
# 			skt.send(tmp)
# 			sleep(1E-3)
# 			break
# 		else:
# 			counter += 1
# 			print(counter)
# 			skt.send(tmp)
# 			sleep(1E-3)
# 			pass
# 		pass
# 	pass
