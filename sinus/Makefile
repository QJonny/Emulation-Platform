#     Makefile for spin demos on Debian 7 i686
#     Copyright (C) 2013  Matthew Orlinski
prog=sinus

CFLAGS = -w -I../spin1_api -I../include -g -O$(O) -std=gnu99 -pthread
CC = /usr/bin/gcc
LDFLAGS = -Wl,-Ttext-segment=0x30000000 -pthread
LIB = -lm
# -Wl,-Ttext-segment=0x30000000 // puts the program code at a different address from 0x400000, should not collide with any SpiNNaker usage
EMU_DIR = emu

FILES = $(prog).c
OBJS = $(prog).o

emu_objs = \
	../emu/spin_emu_app.o \
	../emu/spin_emu.o \
	../emu/spin_emu_dispatcher.o \
	../emu/spin_emu_util.o \
	../emu/spin_emu_api.o \
	../emu/scamp_emu.o \
	../emu/spin_emu_devin.o \
	../emu/spin_emu_io.o

target:
	$(CC) $(CFLAGS) -c $(FILES)
	$(CC) $(LDFLAGS) -o $(prog)  $(OBJS) $(emu_objs) $(LIB)

clean:
	rm -f *.o $(prog)


