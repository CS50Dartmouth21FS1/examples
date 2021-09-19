/* 
 * sorter6.c - sort the lines from stdin
 *   (derived from sorter5.c)
 *   (remove duplicates)
 *
 * usage: sorter < infile
 * stdin: lines of text
 * stdout: lines of text, in sorted order, without duplicates.
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
void listnode_delete(struct listnode* nodep);

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

  // remove duplicates from list
  for (struct listnode* nodep = head.next; nodep != NULL; ) {
    if (nodep->next != NULL && strcmp(nodep->line, nodep->next->line) == 0) {
      // duplicate detected; remove nodep->next from list
      struct listnode* duplicate = nodep->next;
      nodep->next = nodep->next->next;
      listnode_delete(duplicate);
      n--;
    } else {
      // only advance when we do not find a duplicate
      nodep = nodep->next;
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
    // insert the new node at alphabetical place in list
    struct listnode* place = headp;
    // slide along the list to the right place
    while (place->next != NULL && strcmp(line, place->next->line) > 0) {
      place = place->next;
    }
    // On exit, place points at last item on the list, or 
    // place points at a middle item, but new line comes before place->next.
    // Thus, we want to insert 'nodep' after place and before place->next.
    nodep->next = place->next;
    place->next = nodep;
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

/* ******************* listnode_delete ********************** */
/* listnode_delete: delete memory for the given node;
 * frees *both* the listnode and its content line. 
 */
void listnode_delete(struct listnode* nodep)
{
  if (nodep != NULL) {
    if (nodep->line != NULL) {
      free(nodep->line);
    }
    free(nodep);
  }
}
