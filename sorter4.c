/* 
 * sorter4.c - sort the lines from stdin
 *   (derived from sorter2.c)
 *   (linked list version instead of array)
 *
 * usage: sorter < infile
 * stdin: lines of text
 * stdout: lines of text, in arbitrary order.
 * 
 * David Kotz, April 2016, 2017, 2019, 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "readlinep.h"

// A structure for each node in linked list
struct listnode {
  char* line;
  struct listnode* next;
};

bool list_insert(struct listnode* headp, char* line);
struct listnode* listnode_new(char* line);

/* ******************* main ************************************** */
int main()
{
  struct listnode head = {NULL, NULL}; // dummy node at head of empty list
  int n = 0;                           // number of lines read

  // read the list of lines - any number of lines!
  while (!feof(stdin)) {
    char* line = readLinep();
    if (line != NULL) {
      if (list_insert(&head, line)) {
        n++; // only increment if no error
      }
    }
  }
  
  printf("%d lines:\n", n);
  // print the list of lines
  for (struct listnode* nodep = head.next; nodep != NULL; nodep = nodep->next)
    printf("%s\n", nodep->line);

  // here we are lazy and do not free the list. 

  exit(0);
}

/* ******************* list_insert ************************************** */
/* list_insert: insert the given line into the list.
 *
 * We assume:
 *   caller provides pointer to dummy list header node, 
 *   and a pointer 'line' to malloc'd string.
 * We return:
 *   true if success, false if failure for any reason.
 * We allocate:
 *   new listnode to hold the pointer 'line'.
 * Caller is responsible for:
 *   later free()ing the listnode.
 *   not otherwise deallocating the 'line' string.
 * Notes:
 *   The 'line' contents are *not* copied; the pointer is used in the list.
 */
bool
list_insert(struct listnode* headp, char* line) 
{
  struct listnode* nodep = listnode_new(line);

  if (headp == NULL || nodep == NULL) {
    return false;
  } else {
    // insert the new node at head of the list
    nodep->next = headp->next;
    headp->next = nodep;
  }
  return true;
}

/* ******************* listnode_new ************************************** */
/* listnode_new: create a new node to store the given line.
 * 
 * We assume:
 *   caller provides a pointer 'line' to malloc'd string.
 * We return:
 *   pointer to new node, if successful, else returns NULL.  
 * Caller is responsible for:
 *   later calling listnode_delete(nodep).
 * Notes:
 *   The 'line' contents are *not* copied; the pointer is used in the list.
 */
struct listnode* 
listnode_new(char* line) 
{
  // allocate memory for the new node
  struct listnode* nodep = malloc(sizeof(struct listnode));
  
  if (nodep == NULL) {
    return NULL;
  } else {
    // initialize node contents
    nodep->next = NULL;
    nodep->line = line;
  }

  return nodep;
}
