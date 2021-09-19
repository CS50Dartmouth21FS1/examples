# Makefile for 'covid' program
#
# David Kotz 2021

DATA = ~/cs50-dev/shared/COVID-19/data_tables/vaccine_data/us_data/hourly/vaccine_data_us.csv
OBJS = covid.o file.o
LIBS =

CFLAGS = -Wall -pedantic -std=c11 -ggdb
CC = gcc
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

covid: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

covid.o: file.h
file.o: file.h

.PHONY: test valgrind clean

test: covid $(DATA)
	./covid $(DATA)

valgrind: covid $(DATA)
	$(VALGRIND) ./covid $(DATA)

clean:
	rm -f *~ *.o
	rm -f covid
	rm -f core
