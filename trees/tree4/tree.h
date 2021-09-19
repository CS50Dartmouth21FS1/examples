/* 
 * tree.h - header file for simple binary-tree module
 *  (version 4: keyed by a string instead of int)
 *
 * David Kotz - April 2016, 2017, 2021
 */

#ifndef __TREE_H
#define __TREE_H

#include <stdbool.h>

/**************** global types ****************/
typedef struct tree tree_t;  // opaque to users of the module

/**************** functions ****************/

/* Create a new (empty) tree; return NULL if error. */
tree_t* tree_new(void);

/* Insert item into the given tree; if key exists, its data is updated.
 * The item is described by a key and some data.
 * The key string is copied for use by the tree.
 * Returns false if error (e.g., tree or key is NULL).
 */
bool tree_insert(tree_t* tree, const char* key, void* data);

/* Return the data associated with the given key;
 * return NULL if tree is NULL or if key is not found.
 */
void* tree_find(tree_t* tree, const char* key);

#endif // __TREE_H
