/*
 * arguments - a demonstration of how C receives command-line arguments
 */

#include <stdio.h>

int
main(const int argc, const char* argv[])
{
  printf("%d arguments:\n", argc);
  for (int i = 0; i < argc; i++) 
    printf("%d: %s\n", i, argv[i]);
  return 0;
} 
