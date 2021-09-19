/* 
 * sorter3.c - sort the lines from stdin
 *   (derived from sorter2.c)
 *   (finally sort!; void*; casting)
 *
 * usage: sorter < infile
 * stdin: lines of text
 * stdout: numbered lines of text, in sorted order.
 * 
 * David Kotz, April 2016, 2017, 2019, 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readlinep.h"

/* string-comparison function usable with qsort() */
int strcmpp(const void* a, const void* b);

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

  // sort the list with quicksort
  qsort(lines, n, sizeof(char*), strcmpp);

  printf("%d lines\n", n);
  // print the list of lines, and free as we go
  for (int i = 0; i < n; i++) {
    printf("%d: %s\n", i, lines[i]);
    free(lines[i]);
  }

  exit(0);
}

/* ******************* strcmpp ************************************** */
/* 
 * strcmpp: like strcmp but args passed as char** instead of char*,
 * compatible with qsort.  Cast each argument as needed.
 * from http://arstechnica.com/civis/viewtopic.php?f=20&t=607813
 */
int strcmpp(const void* a, const void* b)
{
  return strcmp(*((char**) a), *((char**) b));
}
