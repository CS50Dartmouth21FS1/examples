/*
 * bag8.c: a first construction of a 'bag' data structure,
 * for use with sorter8.c.  For a clean, complete 'bag' module,
 * see the lab3 starter kit or libcs50 in TSE code (labs 4-5-6).
 * 
 * David Kotz 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include "bag8.h"     // note: important to include our own header file!

// the items in a bag
typedef struct bagnode {
  void* item;
  struct bagnode *next;
} bagnode_t;

// The following function is 'private' to this module and thus marked static.
static bagnode_t* bagnode_new(void* item);

// The bag as a whole
typedef struct bag {
  bagnode_t* head;
} bag_t;

/* ********************************************************* */
/* See bag8.h for complete interface description. */
bag_t*  
bag_new(void)
{
  bag_t* bag = malloc(sizeof(bag_t));

  if (bag != NULL) {
    bag->head = NULL;
  }
  return bag;
}


/* ********************************************************* */
/* See bag8.h for complete interface description. */
bool
bag_insert(bag_t* bag, void* item) 
{
  if (bag == NULL) {
    return false;
  }

  bagnode_t* node = bagnode_new(item);
  if (node == NULL) {
    return false;
  }

  // insert the new node at head of the list
  node->next = bag->head;
  bag->head = node;

  return true;
}

/* ********************************************************* */
/* See bag8.h for complete interface description. */
void*
bag_extract(bag_t* bag) 
{
  if (bag == NULL) {
    return NULL;
  } else if (bag->head == NULL) {
    return NULL;
  } else {
    // pull off the node at head of the list
    bagnode_t* node = bag->head;
    void* item = bag->head->item;
    bag->head = node->next;
    free(node);
    return item;
  }
}

/* ********************************************************* */
/* See bag8.h for complete interface description. */
void
bag_print(bag_t* bag, FILE* fp, void (*printfunc)(FILE* fp, void* item)) 
{
  if (bag == NULL) {
    return;
  } else {
    fprintf(fp, "{");
    for (bagnode_t* node = bag->head; node != NULL; node = node->next) {
      if (printfunc != NULL)
        (*printfunc)(fp, node->item);
      fprintf(fp, ", ");
    }
    fprintf(fp, "}");
  }
}

/* ********************* bagnode_new ************************* */
/* bagnode_new: create a new node to store the given item.
 * We assume:
 *   the pointer 'item' is a unique pointer.
 * We return:
 *   pointer to new node, if successful, else returns NULL.
 * We guarantee:
 *   item pointer will be retained in node; item itself is not copied.
 * Caller is responsible for:
 *   later deleting 'item'.
 * Notes:
 *   Note the node stores a copy of the item pointer - but not the item itself.
 */
bagnode_t*
bagnode_new(void* item) 
{
  // allocate memory for the new node
  bagnode_t* node = malloc(sizeof(bagnode_t));
  
  if (node == NULL) {
    return NULL;
  }

  // initialize node contents
  node->next = NULL;
  node->item = item;

  return node;
}
