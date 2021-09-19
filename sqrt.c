/*
 * sqrt - demonstrate use of the math library
 * 
 * usage:
 *    sqrt [number]...
 * where 'number' is an integer or floating-point number
 * 
 * To compile, you must link with the math library:
 *    mygcc sqrt.c -lm -o sqrt
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>   // declares all functions from the math library

int
main(const int argc, const char *argv[])
{
  int exit_status = 0;
  
  for (int i = 1; i < argc; i++) {
    float number; // the numeric equivalent to the argument
    char extra;   // any extraneous characters after parsing number

    if (sscanf(argv[i], "%f%c", &number, &extra) == 1) {
      printf("sqrt(%f) = %f\n", number, sqrt(number));
    } else {
      printf("%s: invalid number\n", argv[i]);
      exit_status++;
    }
  }

  return exit_status;
}
