SHELL=/bin/bash
CC = gcc
SRC = ${wildcard *.c}
OBJS = ${patsubst %.c,%,$(SRC)}
CFLAGS = -Wall -g -O0 -pthread

all:
	$(CC) -o iwlctrl iwlctrl.c wlsctrl.c $(CFLAGS)

clean:
	$(RM) ,*.sw? $(OBJS)

start:
	sudo ./iwlctrl &

stop:
	@echo `sudo pkill iwlctrl` >/dev/null
	@echo '[iwlctrl] process "iwlctrl" killed'
