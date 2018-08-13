#
#             Author: Michael Marven
#       Date Created: 03/11/18
# Date Last Modified: 03/11/18
#            Purpose: Linux Makefile for AVL binary tree implementation
#
#

CC=g++
DEBUG=-g
WARN=-Wall
CFLAGS=$(DEBUG) $(WARN)
PROGS=avl_impl

all: $(PROGS)
    
avl_impl : avl_impl.o
	$(CC) $(CFLAGS) avl_impl.o -o avl_impl

avl_impl.o : avl_impl.cpp
	$(CC) $(CFLAGS) -c -std=gnu++11 avl_impl.cpp

clean:
	rm -rf *.o $(PROGS)
