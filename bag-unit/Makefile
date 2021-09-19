# Makefile for 'bag' module WITH UNIT_TEST
#
# David Kotz, April 2016, 2017, 2019, 2021
# updated by Xia Zhou, July 2016, 2018, January 2019

OBJS = bagtest.o bag.o file.o mem.o 
LIBS =

# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING)
CC = gcc
MAKE = make
# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

bagtest: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

bagtest.o: bag.h file.h
bag.o: bag.h
file.o: file.h

unittest: bag.c mem.o
	$(CC) $(CFLAGS) -DUNIT_TEST bag.c mem.o -o unittest
	./unittest

.PHONY: test valgrind clean

# expects a file `test.names` to exist; it can contain any text.
test: bagtest test.names
	./bagtest < test.names

# expects a file `test.names` to exist; it can contain any text.
valgrind: bagtest test.names
	$(VALGRIND) ./bagtest < test.names

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f bagtest
	rm -f unittest
