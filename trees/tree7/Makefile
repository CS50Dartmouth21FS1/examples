# Makefile for 'tree' module
#  (added memory module, -DTESTING for tree.c)
#
# David Kotz - April 2016, 2017, 2021

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb -DTESTING
LIBS =

.PHONY: clean test

treetest: treetest.o tree.o mem.o
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

treetest.o: tree.h
tree.o: tree.h mem.h
mem.o: mem.h

test: treetest
	./treetest

clean:
	rm -f *~
	rm -f *.o
	rm -rf treetest.dSYM
	rm -f treetest
