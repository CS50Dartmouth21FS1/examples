/* 
 * parseArgs: demonstrate how to validate and unpack command-line arguments
 * 
 * usage: parseArgs inputFilename outputFilename nLines
 *   like head -nLines inputFilename > outputFilename
 * 
 * David Kotz 2019, 2021
 */

#include <stdio.h>
#include <stdlib.h>

// function prototype
void
parseArgs(const int argc, char* argv[], 
           char** inputFilename, char** outputFilename, int* nLines);

/* ******************* main ******************* */
int
main(const int argc, char* argv[])
{
  // declare and initialize variables for each of the expected arguments
  char* inputFilename  = NULL; // name of the input file
  char* outputFilename = NULL; // name of the output file
  int nLines           = 0;    // number of lines to copy from in to out

  // Call a function to extract those arguments from command-line arguments;
  // notice we must pass the *address of* each variable, so the function
  // can change the value of our local variables.
  parseArgs(argc, argv, &inputFilename, &outputFilename, &nLines);

  // interesting part of the program
  // copy_file(inputFilename, outputFilename, nLines);
}

/* ******************* parseArgs ******************* */
/* Handle the messy business of parsing command-line arguments, so main()
 * is cleaner and clearer. To do so, we need a copy of the argc,argv provided
 * to main(), and we need *pointers* to variables that should be updated.
 * We return 'void' because we only return when successful; otherwise,
 * we print error or usage message to stderr and exit non-zero.
 */
void
parseArgs(const int argc, char* argv[], 
           char** inputFilenamep, char** outputFilenamep, int* nLinesp)
{
  const char* progName = argv[0]; // name of this program

  if (argc != 4) {
    fprintf(stderr, "usage: %s inputFilename outputFilename nLines\n", progName);
    exit(1);
  }

  // Save pointers to the filename arguments;
  // to do so, we must dereference the pointers we have, to obtain access
  // to those variables that live in the calling function.
  *inputFilenamep  = argv[1];
  *outputFilenamep = argv[2];

  // A local variable to name the string holding nLines, for now.
  const char* nLinesString = argv[3];

  // try to open input file
  FILE *fp;
  if ( (fp = fopen(*inputFilenamep, "r")) == NULL) {
    fprintf(stderr, "%s: '%s' not readable\n", progName, *inputFilenamep);
    exit(2);
  }
  fclose(fp);

  // try to open output file
  if ( (fp = fopen(*outputFilenamep, "w")) == NULL) {
    fprintf(stderr, "%s: '%s' not writeable\n", progName, *outputFilenamep);
    exit(3);
  }
  fclose(fp);

  // try to convert nLines to an int
  *nLinesp = 0;               // initialize calling function's value
  char excess;                // any excess chars after the number
    
  // if the argument is valid, sscanf should extract exactly one thing.
  if (sscanf(nLinesString, "%d%c", nLinesp, &excess) != 1) {
    fprintf(stderr, "%s: '%s' invalid integer\n", progName, nLinesString);
    exit(4);
  }

  if (*nLinesp < 0) {
    fprintf(stderr, "%s: '%d' must be >= 0\n", progName, *nLinesp);
    exit(5);
  }

}
