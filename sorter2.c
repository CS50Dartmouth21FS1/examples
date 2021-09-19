/* 
 * sorter2.c - sort the lines from stdin
 *   (derived from sorter0.c)
 *   (array of pointers; use of readlinep)
 *
 * usage: sorter < infile
 * stdin: lines of text
 * stdout: numbered lines of text, in original order.
 * 
 * David Kotz, April 2016, 2017, 2019, 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include "readlinep.h"

/* ******************* main ************************************** */
int main()
{
  const int maxLines = 100;   // maximum number of lines
  char* lines[maxLines];      // array of lines, each a pointer to string
  int n = 0;                  // number of lines read

  // read the list of lines
  for (n = 0; n < maxLines && !feof(stdin); ) {
    char* line = readLinep();
    if (line != NULL) {
      lines[n] = line;
      n++; // only increment if no error
    }
  }

  printf("%d lines\n", n);
  // print the list of lines, and free as we go
  for (int i = 0; i < n; i++) {
    printf("%d: %s\n", i, lines[i]);
    free(lines[i]);
  }

  exit(0);
}
