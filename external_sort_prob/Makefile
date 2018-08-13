#
#             Author: Michael Marven
#       Date Created: 03/18/18
# Date Last Modified: 03/18/18
#            Purpose: Linux Makefile for TRI programming challenge files
#
#

CC=g++
DEBUG=-g
WARN=-Wall
LANG=-std=c++11
CFLAGS=$(DEBUG) $(WARN)
PROGS=ext_sort

all: $(PROGS)

ext_sort : ext_sort.o ExternalSort.o CommonDefs.o
	$(CC) $(CFLAGS) ext_sort.o ExternalSort.o CommonDefs.o -o ext_sort
    
ExternalSort.o : ExternalSort.cpp ExternalSort.h CommonDefs.h
	$(CC) $(CFLAGS) -c $(LANG) ExternalSort.cpp

CommonDefs.o : CommonDefs.cpp CommonDefs.h
	$(CC) $(CFLAGS) -c $(LANG) CommonDefs.cpp

ext_sort.o : ext_sort.cpp ExternalSort.h CommonDefs.h
	$(CC) $(CFLAGS) -c $(LANG) ext_sort.cpp
    
clean:
	rm -rf *.o $(PROGS)
