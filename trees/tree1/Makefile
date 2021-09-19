# Makefile for 'tree' module
#
# David Kotz - April 2016, 2017, 2021

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb
LIBS =

.PHONY: clean test

treetest: treetest.o tree.o
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

treetest.o: tree.h
tree.o: tree.h

test: treetest
	./treetest

clean:
	rm -f *~
	rm -f *.o
	rm -rf treetest.dSYM
	rm -f treetest
