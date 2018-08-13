#
#             Author: Michael Marven
#       Date Created: 03/11/18
# Date Last Modified: 06/10/18
#            Purpose: Linux Makefile for hash table implementation
#
#

CC=g++
DEBUG=-g
WARN=-Wall
CFLAGS=$(DEBUG) $(WARN)
PROGS=ht_impl

all: $(PROGS)
    
ht_impl : ht_impl.o
	$(CC) $(CFLAGS) ht_impl.o -o ht_impl

ht_impl.o : ht_impl.cpp
	$(CC) $(CFLAGS) -c -std=gnu++11 ht_impl.cpp

clean:
	rm -rf *.o $(PROGS)
