/* 
 * sorter0.c - sort the lines from stdin
 *  (not yet sorting; just loading and printing the lines)
 *
 * usage: sorter < infile
 * stdin: lines of text
 * stdout: numbered lines of text, in original order.
 * 
 * David Kotz, April 2016, 2017, 2019, 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include "readline.h"

/* ***************** main ********************** */
int
main()
{
  const int maxLines = 100;   // maximum number of lines
  const int maxLength = 50;   // maximum length of a line (including null char)
  char lines[maxLines][maxLength];
  int n = 0;                  // number of lines read

  // read the list of lines
  for (n = 0; n < maxLines && !feof(stdin); ) {
    if (readLine(lines[n], maxLength)) {
      n++; // only increment if no error
    }
  }

  printf("%d lines\n", n);
  // print the list of lines
  for (int i = 0; i < n; i++) {
    printf("%d: %s\n", i, lines[i]);
  }

  exit(0);
}
