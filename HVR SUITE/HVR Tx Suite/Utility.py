#! /usr/bin/python3
'''
Utility: useful general function utilities
@author: Mark Hong
@level: debug
'''
import ctypes, struct, json
import ifaddr
import time, socket, threading
from termcolor import colored, cprint

Gbps=1E9
Mbps=1E6
Kbps=1E3
bps=1E0

def formatThruput(value, unit='bps'):
	unit_chian = ['bps', 'Kbps', 'Mbps', 'Gbps']
	index = unit_chain.index(unit)
	delta = len(unit_chain) - index - 1
	while value<(1E3**delta): delta -=1
	value = value if delta<=0 else value/(1E3**delta)
	unit = unit_chain[index+delta]
	return (value, unit)

def R_T(txt): return colored(txt, 'red')
def G_T(txt): return colored(txt, 'green')
def B_T(txt): return colored(txt, 'blue')
def C_T(txt): return colored(txt, 'cyan')
def Y_T(txt): return colored(txt, 'yellow')
def M_T(txt): return colored(txt, 'magenta')

def load_json(uri):
	try:
		with open(uri) as cf:
			return json.load(cf)
	except Exception as e:
		raise e
	pass

def printh(tip, cmd, color=None, split=' '):
	print(
		colored('[%s]%s'%(tip, split), 'magenta')
		+ colored(cmd, color)
		+ ' '
		)
	pass

int2ip = lambda x: '.'.join([str(x/(256**i)%256) for i in xrange(3,-1,-1)])
ip2int = lambda x:sum([256**j*int(i) for j,i in enumerate(x.split('.')[::-1])])

def get_iface(target):
	adapters = ifaddr.get_adapters()

	for adapter in adapters:
		if target in adapter.nice_name:
			tmp_tuple = adapter.ips[0].ip
			iface_tuple = (tmp_tuple[2], tmp_tuple[1])
			return iface_tuple
		pass
	return (0, 0)
	pass

def get_ipAddr(target):
	adapters = ifaddr.get_adapters()

	for adapter in adapters:
		if target in adapter.nice_name:
			ipAddr = adapter.ips[1].ip
			return ipAddr
		pass
	return "0.0.0.0"
	pass

def startThread(target, args=()):
    args = tuple(args)
    t = threading.Thread(target=target, args=args)
    t.setDaemon(True)
    t.start()
    return t

def watchLoop(handle_t, hook=None):
    while True:
        for t in handle_t:
            if not t.is_alive():
                if hook==None:
                    exit()
                else:
                    hook()
                pass
            pass
        time.sleep(0.5)
        pass
    pass

def udpWrapper(port, ipAddr='127.0.0.1', type='tx'):
    ipAddr, port = str(ipAddr), int(port)
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    if type=='tx':
        sock.connect((ipAddr, port))
    else:
        sock.bind((ipAddr, port))
    return sock

#next rewrite with greenlet, factory and collection
def exec_watch(process, hook=None, fatal=False, gen=True):
	if gen:#external loop
		process.start()
		t = threading.Thread(target=exec_watch, args=(process, hook, fatal, False))
		t.setDaemon(True)
		t.start()
		pass
	else:#internal loop
		while process.is_alive(): pass
		if fatal and hook: hook()
		pass
	pass

def join_helper(t_tuple):
	for t in t_tuple:
		try:
			if t.is_alive(): t.join()
		except Exception as e:
			raise e
		pass
	pass

