SHELL=/bin/bash
CC = gcc
SRC = ${wildcard *.c}
OBJS = ${patsubst %.c,%,$(SRC)}

GENL_CFLAGS = $(shell pkg-config --cflags libnl-genl-3.0)
GENL_LIBS = $(shell pkg-config --libs libnl-genl-3.0)
CFLAGS = $(GENL_CFLAGS) -Wall -g -O0 -pthread
LIBS = $(GENL_LIBS)
all:
	$(CC) -o iwlnl_cmd iwlnl_cmd.c iwlnl.c $(CFLAGS) $(LIBS)
	$(CC) -o iwlnl_ctrl iwlnl_ctrl.c iwlnl.c $(CFLAGS) $(LIBS)
	$(CC) -o iwlnl_script iwlnl_script.c iwlnl.c $(CFLAGS) $(LIBS)

clean:
	$(RM) ,*.sw? $(OBJS)

start:
	sudo ./iwlnl_ctrl &

stop:
	sudo pkill iwlnl_ctrl

prior:
	sh ./script/nl_prior.sh

reset:
	sh ./script/nl_reset.sh

last:
	sh ./script/nl_last.sh
