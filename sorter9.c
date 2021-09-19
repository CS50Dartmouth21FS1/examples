/* 
 * sorter9.c - sort the lines from stdin
 *  (derived from sorter8.c, to use 'libcs50')
 *
 * usage: sorter < infile
 * stdin: lines of text
 * stdout: lines of text, in arbitrary order.
 * 
 * David Kotz, April 2016, 2017, 2019, 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "file.h"
#include "bag.h"

void printLine(FILE* fp, void* item);

/* ********************************************************* */
int main()
{
  int n = 0;             // number of lines read
  char* line;

  bag_t* bag = bag_new();
  if (bag == NULL)
    exit(1);

  // read the list of lines - any number of lines!
  while (!feof(stdin)) {
    line = readLinep();
    if (line != NULL) {
      bag_insert(bag, line);
      n++;
    }
  }
  
  // print the list of lines
  printf("%d lines:\n", n);
  bag_print(bag, stdout, printLine);
  putchar('\n');

  exit(0);
}

/* printLine, for use with bag_print */
void printLine(FILE* fp, void* item)
{
  char* line = item;
  fprintf(fp, "%s", line);
}
