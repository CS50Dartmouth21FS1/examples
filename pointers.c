/* Program:     pointers.c
 * Author:      Taylor Hardin
 * Date:        Mon May 24 12:50:43 EDT 2021
 *
 * Description: My attempt at explaining pointers. 
 * If all you read is this, then my one takeaway is:
 *    pointers are just memory addresses and the type of the pointerd
 *    (e.g., char, int) tells the computer how to interpret the contents
 *    of memory at a given address.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum type {
    CHAR,
    CHAR_POINTER,
    FLOAT,
    INT,
    SHORT
} type_e;

void print_mem_map(void* start, int byteLen, type_e type);
void print_mem_map_char(char* start, int byteLen);
void print_mem_map_float(float* start, int byteLen);
void print_mem_map_int(int* start, int byteLen);
void print_mem_map_char_pointer(char** start, int byteLen);
void print_mem_map_short(short* start, int byteLen);

int main() {
    // 1. Arrays are actually pointers! Indeed, look at what we get when we print the variable 
    //    stackString---it holds a memory address. Notice you can print addresses (i.e., pointers)
    //    with the %p modifier, but you need to cast your pointer to a (void* ) because that is
    //    the type that %p expects. Array variables are special pointers in that the addresses they
    //    store cannot change nor can the size of the memory chunk the address points to. Notice I
    //    call it stackString because arrays get placed in your program's stack memory.
    printf("*******************\n");
    printf("*** STEPS 1 - 6 ***\n");
    printf("*******************\n");
    char stackString[] = "Dogs chase cats";
    printf("stackString   = %p\n", (void* ) stackString);

    // 2. When you think of pointers, you probably think of malloc. This function is essentially
    //    you asking the computer "Hey, I need a memory chunk of size X please". The computer finds
    //    an available chunk and returns a memory address for the start of that chunk---this address
    //    is your pointer and is what gets stored in the heapString variable. Notice I called this
    //    heapString because malloc returns addresses to chunks of heap memory (not stack memory).
    char* heapString = (char* ) malloc(strlen(stackString) + 1);
    strcpy(heapString, stackString);
    printf("heapString    = %p\n", (void* ) heapString);

    // 3. Sometimes you want to copy the contents of one memory chunk to another. Often times, I see
    //    students try to copy by declaring a new pointer such as the one below. In fact, all we did
    //    here was create a copy of a memory address---not a copy of the contents at that address.
    //    Compare the addresses in heapString and pointerCopy and you will see they are the same.
    char* pointerCopy = heapString;
    printf("pointerCopy   = %p\n", (void* ) pointerCopy);

    // 4. If we want to copy the contents of memory, we first need a new chunk of memory. Ask the
    //    computer for a memory chunk large enough to store our contents (in this case we want
    //    enough to store the string pointed to by heapString). Compare the addresses in heapString
    //    and stringCopy and you will see they are DIFFERENT, but later when we print the contents
    //    of the two memory chunks you will see that they are the same.
    char* stringCopy = (char* ) malloc(strlen(heapString) + 1);
    strcpy(stringCopy, heapString);
    printf("stringCopy    = %p\n", (void* ) stringCopy);
    printf("\n");

    // 5. To further illustrate copying a pointer vs copying the contents of memory, lets modify
    //    the first char that pointerCopy points to. You will see that it also updates the first
    //    char that heapString points to because they contain the same memory address, whereas
    //    stringCopy will remain unchanged because its address points to a different chunk of memory
    pointerCopy[0] = 'L';

    // 6. Let's look at the contents of the memory chunks at each of the addresses that our pointers
    //    point to. Take your time and look at the memory addresses. As I said, heapString and
    //    pointerCopy contain the same address (i.e., point to the same piece of memory) but
    //    stackString and stringCopy point to different chunks of memory.
    printf("Printing contents of memory chunk starting at address stored in stackString\n");
    print_mem_map((void* ) stackString, strlen(stackString) + 1, CHAR);
    printf("\n");

    printf("Printing contents of memory chunk starting at address stored in heapString\n");
    print_mem_map((void* ) heapString,  strlen(heapString) + 1,  CHAR);
    printf("\n");
    
    printf("Printing contents of memory chunk starting at address stored in pointerCopy\n");
    print_mem_map((void* ) pointerCopy, strlen(pointerCopy) + 1, CHAR);
    printf("\n");

    printf("Printing contents of memory chunk starting at address stored in stringCopy\n");
    print_mem_map((void* ) stringCopy,  strlen(stringCopy) + 1,  CHAR);
    printf("\n");

    // 7. Now, let's look at double pointers (or, pointers to pointers). You may be surprised to see
    //    that these are also simply just memory addresses. Below I ask the computer for space to
    //    hold 4 character pointers. In other words, I am asking for enough space to store 4 memory
    //    addresses---addresses that point to memory chunks where characters are being stored.
    printf("********************\n");
    printf("*** STEPS 7 - 11 ***\n");
    printf("********************\n");
    char** strings = (char** ) calloc(4, sizeof(char* ));

    // 8. First, let's print out the value stored in strings. Notice that it is just a memory
    //    address, much like the ones stored in the variables we declared above! Indeed, pointers
    //    and double pointers are exactly the same; the only difference is in the contents of
    //    the memory that each points to. For our char* , we are storing the address of a chunk of
    //    memory that contains characters. For char** , we are storing the address of a chunk of
    //    memory that contains addresses (addresses to chunks of memory where chars are stored).
    printf("strings = %p\n", (void* ) strings);
    printf("\n");

    // 9. The chunk of memory starting at the address held in strings should only contain zeros
    //    since I allocated it with calloc. Let's check by printing the contents of memory starting
    //    at the address held in the variable strings.
    printf("Printing contents of memory chunk starting at address stored in strings\n");
    print_mem_map((void* ) strings, 4 * sizeof(char* ), CHAR_POINTER);
    printf("\n");

    // 10. Let's populate the chunk of memory that strings points to. Notice how I can use both
    //     pointer and array notation to achieve the same effect: increment the address stored in
    //     strings by some value (e.g., 0, 1, 2, 3, 4) and then go to that new address and store the
    //     value on the right side of the equals sign. Here, we are storing the addresses held by
    //     the 4 pointer variables we declared at the begining of the program.
    *strings       = stackString;
    strings[1]     = heapString;
    *(strings + 2) = pointerCopy;
    strings[3]     = stringCopy;

    // 11. Print the contents of the chunk of memory that strings points to again to see that we have
    //     now copied all of the values held in our 4 pointer variables. Indeed, the chunk of memory
    //     that strings points to should now have all 4 addresses stored in our stackString,
    //     heapString, pointerCopy, and stringCopy variables.
    printf("Printing contents of memory chunk starting at address stored in strings\n");
    print_mem_map((void* ) strings, 4 * sizeof(char* ), CHAR_POINTER);
    printf("\n");

    for (int i = 0; i < 4; i++) {
        printf("Printing contents of memory chunk starting at address stored in strings[%d]\n", i);
        print_mem_map((void* ) strings[i], strlen(strings[i]) + 1, CHAR);
        printf("\n");
    }

    // 12. How do these concepts apply to data types other than char (e.g., int* , float* )? Well
    //     they work exactly the same; all pointers, regardless of type, are simply variables that
    //     hold a memory address. And memory at its most basic level is just a string of 1s and 0s.
    //     The type is there to tell the computer how to interpret the 1s and 0s at a given memory
    //     address. Below, I will try to demonstrate this concept with some c casting fun.
    //
    //     Again, types tell the computer how to interpret memory, and part of the information
    //     contained within a type is the size of the type. Let's look at some type sizes.
    //     Notice how all the pointers HAVE THE SAME SIZE REGARDLESS OF TYPE. This is because,
    //     once again, pointers are just variables that store memory addresses. Thus, all pointers
    //     are of size 8, because that is the size of a memory address (at least on modern machines) 
    printf("*********************\n");
    printf("*** STEPS 12 - 14 ***\n");
    printf("*********************\n");
    printf("sizeof(char)      = %lu\n", sizeof(char));
    printf("sizeof(double)    = %lu\n", sizeof(double));
    printf("sizeof(float)     = %lu\n", sizeof(float));
    printf("sizeof(int)       = %lu\n", sizeof(int));
    printf("sizeof(short)     = %lu\n", sizeof(short));
    printf("sizeof(char* )    = %lu\n", sizeof(char* ));
    printf("sizeof(double* )  = %lu\n", sizeof(double* ));
    printf("sizeof(float* )   = %lu\n", sizeof(float* ));
    printf("sizeof(int* )     = %lu\n", sizeof(int* ));
    printf("sizeof(short* )   = %lu\n", sizeof(short* ));
    printf("sizeof(void* )    = %lu\n", sizeof(void* ));
    printf("sizeof(char** )   = %lu\n", sizeof(char** ));
    printf("sizeof(double** ) = %lu\n", sizeof(double** ));
    printf("sizeof(float** )  = %lu\n", sizeof(float** ));
    printf("sizeof(int** )    = %lu\n", sizeof(int** ));
    printf("sizeof(short** )  = %lu\n", sizeof(short** ));
    printf("sizeof(void** )   = %lu\n", sizeof(void** ));
    printf("\n");

    // 13. Now, let's do some casting to illustrate how we can interpret the same chunk of memory
    //     in different ways. Recall heapString is a pointer to a chunk of memory containing chars.
    //     Well, what if we tell the computer to interpret that chunk of memory another way? Notice
    //     that all of the variables below contain the same memory address, but when we print out
    //     the contents of that memory chunk in step 14 it gets interpreted differently based on
    //     the type of the pointer holding the address (e.g., float* , int* , short* ).
    float* heapFloats  = (float* )  heapString;
    int*   heapInts    = (int* )    heapString;
    short* heapShorts  = (short* )  heapString;
    printf("heapFloats  = %p\n", (void* ) heapFloats);
    printf("heapInts    = %p\n", (void* ) heapInts);
    printf("heapShorts  = %p\n", (void* ) heapShorts);
    printf("heapString  = %p\n", (void* ) heapString);
    printf("\n");

    // 14. Look carefully at the addresses: both the float and int addresses increased by 4 but the
    //     short only increased by 2! The computer knows that an int is 4 bytes long and thus
    //     increments the address by 4 bytes so we actually get the next int instead of just the
    //     next byte. The same goes for shorts and any other type; the computer will increment or
    //     decrement your memory addresses according to the size of the pointer type storing that
    //     address. Check out the print_mem_map functions for further explanation.
    printf("Printing contents of memory chunk starting at address stored in heapFloats\n");
    print_mem_map((void* ) heapFloats, strlen(heapString) + 1, FLOAT);
    printf("\n");
    
    printf("Printing contents of memory chunk starting at address stored in heapInts\n");
    print_mem_map((void* ) heapInts, strlen(heapString) + 1, INT);
    printf("\n");
    
    printf("Printing contents of memory chunk starting at address stored in heapShorts\n");
    print_mem_map((void* ) heapShorts, strlen(heapString) + 1, SHORT);
    printf("\n");
    
    printf("Printing contents of memory chunk starting at address stored in heapString\n");
    print_mem_map((void* ) heapString,  strlen(heapString) + 1,  CHAR);

    //     I hope the casting tricks I just showed help you better understand why your bag, set,
    //     and hashtable modules used void*  for the items: the modules simply accept the address
    //     to a chunk of memory but do not know how to interpret the contents of that memory chunk.
    //     By doing this our modules are capable of storing anything, because the "items" they are
    //     storing are really just memory addresses. The user of the module, however, does know the
    //     type of data being stored at these addresses. Thus, when they retrieve the "item"
    //     (i.e., memory address) they cast the address to the appropriate type to let the computer
    //     know how to interpret the contents of said memory chunk.
    return 0;
}

/* Function:    print_mem_map()
 * Description: Dispatch function used to call the appropriate print function for a given type
 * 
 * param:       {void* } start   - the address of a chunk of memory whose contents we want to print
 * param:       {int   } byteLen - the length of the chunk of memory in bytes
 * param:       {type_e} type    - the type of data stored in the memory chunk
 * */
void print_mem_map(void* start, int byteLen, type_e type) {
    switch(type) {
        case CHAR:         print_mem_map_char((char* ) start, byteLen);          break;
        case CHAR_POINTER: print_mem_map_char_pointer((char** ) start, byteLen); break;
        case FLOAT:        print_mem_map_float((float* ) start, byteLen);        break;
        case INT:          print_mem_map_int((int* ) start, byteLen);            break;
        case SHORT:        print_mem_map_short((short* ) start, byteLen);        break;
        default:           break;
    }
}

/* Function:    print_mem_map_char()
 * Description: Prints the contents of a chunk of memory as characters
 * 
 * param:       {char* } start   - the address of a chunk of memory whose contents we want to print
 * param:       {int   } byteLen - the length of the chunk of memory in bytes
 * */
void print_mem_map_char(char* start, int byteLen) {
    // 1. Calculate the number of items in the memory chunk. Remember, different data types are
    //    different lengths. For instance, a chunk of size 8 could be interpreted as 8 characters
    //    or as 2 integers (chars are 1 byte long whereas ints are 4).
    int numItems = byteLen / sizeof(char);

    // 2. Loop over memory chunk and print the address where the current item is located and the
    //    item itself. Make sure to increment the address based on the current item. Remember that
    //    %p expects a void*  so we have to cast our address after we increment it.
    printf("Address        | Contents\n");
    for (int i = 0; i < numItems; i++) {
        printf("%p | '%c'\n", (void* ) (start + i), start[i]);
    }
}

/* Function:    print_mem_map_char_pointer()
 * Description: Prints the contents of a chunk of memory as addresses
 * 
 * param:       {char** } start   - the address of a chunk of memory whose contents we want to print
 * param:       {int    } byteLen - the length of the chunk of memory in bytes
 * */
void print_mem_map_char_pointer(char** start, int byteLen) {
    // 1. Calculate the number of items in the memory chunk. Remember, different data types are
    //    different lengths. For instance, a chunk of size 8 could be interpreted as 8 characters
    //    or as 2 integers (chars are 1 byte long whereas ints are 4).
    int numItems = byteLen / sizeof(char* );

    // 2. Loop over memory chunk and print the address where the current item is located and the
    //    item itself. Make sure to increment the address based on the current item. Remember that
    //    %p expects a void*  so we have to cast our address after we increment it.
    printf("Address        | Contents\n");
    for (int i = 0; i < numItems; i++) {
        printf("%p | %p\n", (void* ) (start + i), (void* ) (start[i]));
    }
}

/* Function:    print_mem_map_float()
 * Description: Prints the contents of a chunk of memory as floats
 * 
 * param:       {float* } start   - the address of a chunk of memory whose contents we want to print
 * param:       {int    } byteLen - the length of the chunk of memory in bytes
 * */
void print_mem_map_float(float* start, int byteLen) {
    // 1. Calculate the number of items in the memory chunk. Remember, different data types are
    //    different lengths. For instance, a chunk of size 8 could be interpreted as 8 characters
    //    or as 2 integers (chars are 1 byte long whereas ints are 4).
    int numItems = byteLen / sizeof(float);

    // 2. Loop over memory chunk and print the address where the current item is located and the
    //    item itself. Make sure to increment the address based on the current item. Remember that
    //    %p expects a void*  so we have to cast our address after we increment it.
    printf("Address        | Contents\n");
    for (int i = 0; i < numItems; i++) {
        printf("%p | %f\n", (void* ) (start + i), start[i]);
    }
}

/* Function:    print_mem_map_int()
 * Description: Prints the contents of a chunk of memory as ints
 * 
 * param:       {int* } start   - the address of a chunk of memory whose contents we want to print
 * param:       {int  } byteLen - the length of the chunk of memory in bytes
 * */
void print_mem_map_int(int* start, int byteLen) {
    // 1. Calculate the number of items in the memory chunk. Remember, different data types are
    //    different lengths. For instance, a chunk of size 8 could be interpreted as 8 characters
    //    or as 2 integers (chars are 1 byte long whereas ints are 4).
    int numItems = byteLen / sizeof(int);

    // 2. Loop over memory chunk and print the address where the current item is located and the
    //    item itself. Make sure to increment the address based on the current item. Remember that
    //    %p expects a void*  so we have to cast our address after we increment it.
    printf("Address        | Contents\n");
    for (int i = 0; i < numItems; i++) {
        printf("%p | %d\n", (void* ) (start + i), start[i]);
    }
}

/* Function:    print_mem_map_short()
 * Description: Prints the contents of a chunk of memory as shorts
 * 
 * param:       {short* } start   - the address of a chunk of memory whose contents we want to print
 * param:       {int    } byteLen - the length of the chunk of memory in bytes
 * */
void print_mem_map_short(short* start, int byteLen) {
    // 1. Calculate the number of items in the memory chunk. Remember, different data types are
    //    different lengths. For instance, a chunk of size 8 could be interpreted as 8 characters
    //    or as 2 integers (chars are 1 byte long whereas ints are 4).
    int numItems = byteLen / sizeof(short);

    // 2. Loop over memory chunk and print the address where the current item is located and the
    //    item itself. Make sure to increment the address based on the current item. Remember that
    //    %p expects a void*  so we have to cast our address after we increment it.
    printf("Address        | Contents\n");
    for (int i = 0; i < numItems; i++) {
        printf("%p | %d\n", (void* ) (start + i), start[i]);
    }
}
