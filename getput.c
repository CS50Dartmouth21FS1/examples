/*
 * getput: a short demo of getchar() and putchar()
 */

#include <stdio.h>
#include <stdlib.h>

int
main()
{
  char c;

  while ((c = getchar()) != EOF) {
    putchar(c);
  }
}
