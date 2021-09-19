# Makefile for 'tree' module
#  (added targets for 'make test')
#  (added readlinep.o and readlinep.h)
#
# David Kotz - April 2016, 2017, 2021

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb -DTESTING
LIBS =

# List of weather-station xml files to fetch and use
STATIONS = KLEB.xml KMWN.xml KBOS.xml KLAX.xml PHJR.xml

.PHONY: test clean

treetest: treetest.o tree.o mem.o readlinep.o
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

treetest.o: tree.h readlinep.h
tree.o: tree.h mem.h
mem.o: mem.h
readlinep.o: readlinep.h

test: treetest $(STATIONS)
	./treetest $(STATIONS)

$(STATIONS):
	curl -s https://w1.weather.gov/xml/current_obs/$@ > $@

clean:
	rm -f *~
	rm -f *.o
	rm -rf *.dSYM
	rm -f treetest
	rm -f $(STATIONS)
