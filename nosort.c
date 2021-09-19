/*
 * nosort - an example about handling of command-line switches;
 *  supports command lines such as "sort -r -u -n", but not "sort -run".
 * It also displays an old-style approach to looping over (argc,argv),
 * stepping through the arguments by changing each variable.
 */

#include<stdio.h>
#include<stdbool.h>

int
main(int argc, char* argv[])
{
  char* progname = argv[0];   // name of this program
  bool unique =  false;       // -u
  bool reverse = false;       // -r
  bool numsort = false;       // -n
  
  // this loop changes argc and argv as it loops
  while((argc > 1) && (argv[1][0] == '-')) {

    // argv[1][0] is the '-'
    // argv[1][1] is the first letter
    char opt = argv[1][1];
    
    switch (opt) {

    case 'r': 
      reverse = true;
      break;
    case 'u':
      unique = true;
      break;
    case 'n':
      numsort = true;
      break;
    case '\0':
      fprintf(stderr, "Error: missing option '-'\n");
      fprintf(stderr, "Usage:  %s [-r] [-u] [-n] filename...\n", progname);
      return 0;
      
    default:
      fprintf(stderr, "Error: bad option '-%c'\n", opt);
      fprintf(stderr, "Usage:  %s [-r] [-u] [-n] filename...\n", progname);
      return 1;
    }

    // decrement the number of arguments left
    // increment the argv pointer to the next argument
    argc--; argv++;
  }

  if (numsort)  printf("numeric sort\n");
  if (unique)   printf("unique sort\n");
  if (reverse)  printf("reverse sort\n");
  if (argc > 1) printf("next argument '%s'\n", argv[1]);
  
  // ...other processing

  return 0;
}
