/* 
 * pointer1 - a short program to demonstrate pointers.
 * 
 * David Kotz, April 2017, 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* CS = "Computer Science";

int main()
{
  printf(" CS = %12p, *CS = '%c', CS as string = '%s'\n", (void*) CS, *CS, CS);

  for (char* p = CS; *p != '\0'; p++) {
    printf(" p = %12p, *p = '%c'\n", (void*) p, *p);
  }

  return 0;
}
