#
#             Author: Michael Marven
#       Date Created: 03/10/18
# Date Last Modified: 03/10/18
#            Purpose: Linux Makefile for simple linked list implementation
#
#

CC=g++
DEBUG=-g
WARN=-Wall
CFLAGS=$(DEBUG) $(WARN)
PROGS=ll_impl

all: $(PROGS)
    
ll_impl : ll_impl.o
	$(CC) $(CFLAGS) ll_impl.o -o ll_impl

ll_impl.o : ll_impl.cpp
	$(CC) $(CFLAGS) -c -std=gnu++11 ll_impl.cpp

clean:
	rm -rf *.o $(PROGS)
