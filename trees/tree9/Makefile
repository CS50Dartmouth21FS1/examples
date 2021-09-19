# Makefile for 'tree' module
#  (unit testing)
#
# David Kotz - May 2016, April 2017, 2021
# updated by Xia Zhou, July 2016

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb -DTESTING
LIBS =

# List of weather-station xml files to fetch and use
STATIONS = KLEB.xml KMWN.xml KBOS.xml KLAX.xml PHJR.xml

.PHONY: test1 test2 clean

treetest: treetest.o tree.o mem.o readlinep.o
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

unittest: tree.h tree.c mem.h unittest.h mem.o
	$(CC) $(CFLAGS) -DUNIT_TEST tree.c mem.o -o unittest

treetest.o: tree.h readlinep.h
tree.o: tree.h mem.h
mem.o: mem.h
readlinep.o: readlinep.h

test1: treetest $(STATIONS)
	./treetest $(STATIONS)

test2: unittest
	./unittest

$(STATIONS):
	curl -s https://w1.weather.gov/xml/current_obs/$@ > $@

clean:
	rm -f *~
	rm -f *.o
	rm -rf *.dSYM
	rm -f treetest
	rm -f unittest
	rm -f $(STATIONS)
