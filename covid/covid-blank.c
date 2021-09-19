/* THIS FILE HAS 'BLANKS' THAT YOU NEED TO FILL IN */
/*
 * covid - print summary of vaccine data from JHU COVID dataset.
 * 1. read the csv file, bursting each line into array of strings.
 * 2. convert the array of strings into a struct.
 * 3. add the struct to a linked list of structs.
 * 4. when complete, print a tabular summary.
 *
 * The dataset was downloaded from https://github.com/govex/COVID-19
 * into ~/cs50-dev/shared/COVID-19/data_tables/vaccine_data/us_data/hourly/
 * where we focus on vaccine_data_us.csv - we expect that file as our input.
 *
 * David Kotz 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "file.h"

/* ************** local constants *********** */
// Structure of the data is defined by first line of the file
const char* header = "FIPS,Province_State,Country_Region,Date,Lat,Long_,Vaccine_Type,Doses_alloc,Doses_shipped,Doses_admin,Stage_One_Doses,Stage_Two_Doses,Combined_Key";
const int numFields = 13; // number of comma-sep fields defined by the header

/* ************** local types *********** */
typedef struct {
  char* csv;            // the original csv-format line
  int FIPS;             // FIPS code (0 if missing)
  char* Province_State; // name of province or state ("" if missing)
  char* Country_Region; // name of country or region ("" if missing)
  char* Date;           // date for this data ("" if missing)
  float Lat;            // latitude for this location (0 if missing)
  float Long;           // longitude for this location (0 if missing)
  char* Vaccine_Type;   // vaccine type (brand) or "All"
  int Doses_alloc;      // doses allocated (0 if missing)
  int Doses_shipped;    // doses shipped (0 if missing)
  int Doses_admin;      // doses administered (0 if missing)
  int Stage_One_Doses;  // stage one doses (0 if missing)
  int Stage_Two_Doses;  // stage two doses (0 if missing)
  char* Combined_Key;   // name of location ("" if missing)
} vacdata_t;

/* ************** local function prototypes *********** */
static bool csvBurst(char* csv, char* fields[], const int numFields);
static bool extractData(BLANK csv, BLANK fields[], BLANK datap);
bool str2int(const char string[], int* nump);
bool str2float(const char string[], float* nump);

/* ************************ main ********************** */
int
main(const int argc, const char* argv[])
{
  const char* progName = argv[0]; // name of this program

  // check for correct number of arguments
  if (argc != 2) {
    fprintf(stderr, "usage: %s data.csv\n", progName);
    exit(1);
  }

  const char* fileName = argv[1]; // name of input file (if present)
  FILE* fp;                       // the input file, once opened
  int numLines;                   // number of lines in input file
  char* line;                     // one line from the input file

  // open the input file
  if ((fp = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "cannot open file '%s'\n", fileName);
    exit(2);
  }

  // count number of lines in the input file
  numLines = BLANK;
  if (numLines < 2) {
    fprintf(stderr, "file '%s' appears too short\n", fileName);
    exit(3);
  }

  // read the header line from input
  line = BLANK;
  if (line == NULL) {
    fprintf(stderr, "file '%s' missing header line\n", fileName);
    exit(4);
  }
  if (strcmp(line, header) != 0) {
    fprintf(stderr, "mismatched header line '%s'\n", line);
    exit(5);
  }
  free(line);

  // allocate array to hold all the data
  int numRows = numLines-1;
  vacdata_t BLANK data = BLANK;
  if (data == NULL) {
    fprintf(stderr, "cannot allocate memory for %d rows\n", numRows);
    exit(6);
  }

  // read each line of data
  for (int row = 0; row < numRows; row++) {
    line = file_readLine(fp);
    if (line == NULL) {
      fprintf(stderr, "unexpected error or EOF after %d rows\n", row);
      exit(7);
    }

    // burst the line into its comma-separated components
    char* fields[numFields]; // pointers into line
    if (!csvBurst(line, fields, numFields)) {
      fprintf(stderr, "error parsing line '%s'\n", line);
      exit(8);
    }

    // convert the string array to fill in this row's struct
    if (!extractData(line, fields, &data[row])) {
      fprintf(stderr, "error extracting data from line '%s'\n", line);
      exit(9);
    }

    // do not free(line); it is saved inside data; free it below.
  }

  // close the input file
  fclose(fp);

  // print a tabular summary
  printf("%9s %-10s [%5s %7s] %-20s\n",
         "Doses", "Date", "Lat", "Long", "Location");
  for (int row = 0; row < numRows; row++) {
    if (strcmp(data[row].Vaccine_Type, "All") == 0) {
      printf("%9d %-10s [%5.2f %7.2f] %-20s\n",
             data[row].Doses_admin,
             data[row].Date,
             data[row].Lat,
             data[row].Long,
             data[row].Combined_Key);
    }
  }

  // free all memory
  /* BLANK */

  exit(0);
}

/* *************** csvBurst ************************ */
/* csvBurst:
 *  Burst the string 'csv' into an array of strings 'fields',
 *  by expecting to find 'numFields' comma-separated fields in csv.
 *
 * We assume:
 *   We can modify 'csv' and 'fields'.
 * We return:
 *   true if the parsing is successful;
 *   false otherwise.
 * We guarantee:
 *   On successful return,
 *    The string 'csv' is modified to replace comma-separators with '\0';
 *    each entry of array 'fields' is a pointer into the string 'csv'.
 *   On an unsuccessful return,
 *    The string 'csv' may be modified but not completely,
 *    the array 'fields' may be modified but not completely.
 * Caller is responsible for:
 *   providing 'csv', a string we are allowed to modify;
 *   providing fields[numFields], whose entries we overwrite.
 * Notes:
 *  We take care around fields that are enclosed in "quotes", because
 *  they may contain embedded commas.
 *
 */
static bool
csvBurst(char* csv, char* fields[], const int numFields)
{
  if (csv == NULL || fields == NULL || numFields < 1) {
    return false;
  }

  char* s = csv;    // as we loop, s points at the start of field f
  for (int f = 0; f < numFields; f++) {
    // does this field begin with quote?
    if (*s == '"') {
      fields[f] = ++s;          // field begins after the open-quote
      char* p = strchr(s, '"'); // find the next quote
      if (p == NULL) {
        return false;           // missing close quote
      } else {
        *p = '\0';              // terminate at the close-quote
        s = p+1;                // move s past the close-quote
        if (*s == ',') {
          s++;                  // move s past the field-ending comma
        }
      }
    } else {
      fields[f] = s;            // field begins here
      char* p = strchr(s, ','); // find the next comma
      if (p == NULL) {          // comma not found
        if (f < numFields-1) {  // error if not the last field
          return false;
        }
      } else {                  // comma found
        *p = '\0';              // terminate at the comma
        s = p+1;                // move s past the comma
      }
    }
  }
  return true;
}

/* *************** extractData ************************ */
/* extractData:
 *  Extract the data from array fields[], which contain pointers
 *  into 'csv', into the struct at 'datap'.
 *
 * We assume:
 *   BLANK
 * We return:
 *   BLANK
 * We guarantee:
 *   BLANK
 * Caller is responsible for:
 *   BLANK
 * Notes:
 *   BLANK
 */
static bool
extractData(BLANK csv, BLANK fields[], BLANK datap)
{
  // defensive pointer checks
  BLANK;

  // the original csv-format line
  datap->csv = csv;

  // FIPS code (0 if missing)
  BLANK;

  // name of province or state ("" if missing)
  BLANK;

  // name of country or region ("" if missing)
  BLANK;

  // date for this data ("" if missing)
  BLANK;

  // latitude for this location (0 if missing)
  BLANK;

  // longitude for this location (0 if missing)
  BLANK;

  // vaccine type (brand) or "All"
  BLANK;

  // doses allocated (0 if missing)
  BLANK;

  // doses shipped (0 if missing)
  BLANK;

  // doses administered (0 if missing)
  BLANK;

  // stage one doses (0 if missing)
  BLANK;

  // stage two doses (0 if missing)
  BLANK;

  // name of location ("" if missing)
  BLANK;

  return true;
}


/* ***************** str2int ********************** */
/*
 * Convert a string to an integer, updating 'nump'.
 * Returns true if successful, or false if any error.
 * If the string is empty, 'nump' set to zero.
 * It is an error if there is any additional character beyond the number.
 */
bool str2int(const char string[], int* nump)
{
  if (nump == NULL) {
    return false;
  }

  if (string == NULL || *string == '\0') {
    BLANK;
    return true;
  } else {
    // We use sscanf() to parse a number, expecting there to be no following
    // character ... but if there is, the input is invalid.
    // For example, 1234x will be invalid, as would 12.34 or just x.
    char nextchar;
    return (sscanf(string, "%d%c", nump, &nextchar) == 1);
  }
}

/* ***************** str2float ********************** */
/*
 * Convert a string to an floating-point number, updating 'nump'.
 * Returns true if successful, or false if any error.
 * If the string is empty, 'nump' set to zero.
 * It is an error if there is any additional character beyond the number.
 */
bool str2float(const char string[], float* nump)
{
  if (nump == NULL) {
    return false;
  }

  if (string == NULL || *string == '\0') {
    BLANK;
    return true;
  } else {
    // We use sscanf() to parse a number, expecting there to be no following
    // character ... but if there is, the input is invalid.
    // For example, 1234x will be invalid, as would 12.34 or just x.
    char nextchar;
    return (sscanf(string, "%f%c", nump, &nextchar) == 1);
  }
}
