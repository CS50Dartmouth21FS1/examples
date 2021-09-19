/* 
 * sorter1.c - sort the lines from stdin
 *  (derived from sorter0.c; read from a file named in argument)
 *  (not yet sorting; just loading and printing the lines)
 *
 * usage: sorter [filename]
 * filename: includes lines of text
 * stdin: used if filename not specified
 * stdout: numbered lines of text, in original order.
 * 
 * David Kotz, April 2016, 2017, 2019, 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include "freadline.h"

/* ***************** main ********************** */
int
main(const int argc, const char* argv[])
{
  const int maxLines = 100;   // maximum number of lines
  const int maxLength = 50;   // maximum length of a line (including null char)
  char lines[maxLines][maxLength];
  FILE* fp;                   // input file
  int n = 0;                  // number of lines read

  // validate arguments and open input file
  if (argc == 1) {
    fp = stdin;
  } else if (argc == 2) {
    fp = fopen(argv[1], "r");
    if (fp == NULL) {
      fprintf(stderr, "%s cannot open file '%s'\n", argv[0], argv[1]);
      exit(2);
    } 
  } else {
    fprintf(stderr, "usage: %s [filename]\n", argv[0]);
    exit(1);
  }

  // read the list of lines
  for (n = 0; n < maxLines && !feof(fp); ) {
    if (freadLine(fp, lines[n], maxLength)) {
      n++; // only increment if no error
    }
  }

  fclose(fp);

  printf("%d lines\n", n);
  // print the list of lines
  for (int i = 0; i < n; i++) {
    printf("%d: %s\n", i, lines[i]);
  }

  exit(0);
}
