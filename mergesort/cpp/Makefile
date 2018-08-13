#
#             Author: Michael Marven
#       Date Created: 03/13/18
# Date Last Modified: 03/13/18
#            Purpose: Linux Makefile for Mergesort implementation
#
#

CC=g++
DEBUG=-g
WARN=-Wall
LIBC=-stdlib=libc++
LANG=-std=c++11
CFLAGS=$(DEBUG) $(WARN)
PROGS=ms_impl

all: $(PROGS)
    
ms_impl : ms_impl.o
	$(CC) $(CFLAGS) $(LIBC) ms_impl.o -o ms_impl

ms_impl.o : ms_impl.cpp
	$(CC) $(CFLAGS) $(LIBC) -c $(LANG) ms_impl.cpp

clean:
	rm -rf *.o $(PROGS)
