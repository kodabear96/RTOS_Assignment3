# 
#	Brief: Makefile for both Prg_1 and Prg_2 including packages SharedMemory whic his used by both programs #	and Timer/Threads wihich is used by Prg_1
#
#  	Author: Dakota Harkins
#  	Date: 29/04/2018
#

CC = gcc
CFLAGS = -Wall
# Wall enables all compiler's warning messages
# o2 - optimisation: that breaks wraparound arithmetic
.c.o:	
	$(CC) $(CFLAGS) -c $*.c #-c source file

all:	Prg_1 test clean 

Threads.o:	Threads.c Threads.h
	$(CC) -c Threads.c

Processes.o:	Processes.c Processes.h
	$(CC) -c Processes.c

Prg_1: Processes.o Threads.o Prg_1.o 
	$(CC) -o Prg_1 Prg_1.c Processes.o Threads.o  -lrt

clean:
	rm -rf *.o Prg_1

test: test1

test1:
	./Prg_1
