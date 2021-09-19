/*
 * bag8.c: a first construction of a 'bag' data structure,
 * for use with sorter8.c.  For a clean, complete 'bag' module,
 * see the lab3 starter kit or libcs50 in TSE code (labs 4-5-6).
 * 
 * David Kotz 2021
 */

#ifndef __BAG__
#define __BAG__

#include <stdio.h>
#include <stdbool.h>

/* the bag as a whole */
typedef struct bag bag_t;

/* ********************* bag_new ************************* */
/* bag_new: create a new bag.
 *
 * We return:
 *   a pointer if success, NULL if failure.
 * We guarantee:
 *   the bag is initialized as empty.
 * Caller is responsible for:
 *   eventually calling bag_delete()
 * Notes:
 *   
 */
bag_t* bag_new(void);

/* ********************* bag_insert ************************* */
/* bag_insert: insert the given item into the bag.
 *
 * We assume:
 *   caller provides a valid bag pointer valid item pointer.
 * We return:
 *   true if success, false if failure.
 * We guarantee:
 *   item pointer will be retained in bag; item itself is not copied.
 * Caller is responsible for:
 *   later pulling the item out of the bag and free'ing it if appropriate.
 * Notes:
 *   Note the bag stores a copy of the item pointer - but not the item itself.
 */
bool bag_insert(bag_t* bag, void* item);

/* ********************* bag_extract ************************* */
/* bag_extract: extract an item (any item) from the bag.
 * We assume:
 *   caller provides a valid bag pointer.
 * We return:
 *   an item pointer, or NULL if bag is empty or if some failure.
 * We guarantee:
 *   return of an item from the bag, if bag is not empty.
 * Caller is responsible for:
 *   freeing the item if that is appropriate.
 */
void* bag_extract(bag_t* bag);


/* ********************* bag_print ************************* */
/* bag_print: print a bag, calling the func on each item.
 * We assume:
 *   caller provides a valid bag;
 *   caller provides a valid print-function pointer.
 *   output should go to stdout.
 * We return:
 *   nothing.
 * We print:
 *   the list of items, separated by comma-space, surrounded by {curly brackets}.
 * Caller is responsible for:
 *   printing a following newline if desired.
 * Notes:
 *   All our output is to stdout so printfunc should also print to stdout.
 *   We print nothing if bag==NULL; we print empty strings if printfunc==NULL.
 */
void bag_print(bag_t* bag, FILE* fp, void (*printfunc)(FILE* fp, void* item));

#endif // __BAG__
