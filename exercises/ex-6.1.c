/* Compile the program in Listing 6-1 (mem_segments.c), and list its size using
ls –l. Although the program contains an array (mbuf) that is around 10 MB in
size, the executable file is much smaller than this. Why is this?

mbuf is part of the "Uninitialized segment" and thus need not to have allocated
space for its  data.
*/

#include <stdio.h>
#include <stdlib.h>


char globBuf[65536];            /* Uninitialized data segment */
int primes[] = { 2, 3, 5, 7 };  /* Initialized data segment */


static int
square(int x)                   /* Allocated in frame for square() */
{
    int result;                 /* Allocated in frame for square() */
    result = x * x;
    return result;              /* Return value passed via register */
}


static void
doCalc(int val)                 /* Allocated in frame for doCalc() */
{
    printf("The square of %d is %d\n", val, square(val));
    if (val < 1000) {
        int t;                  /* Allocated in frame for doCalc() */
        t = val * val * val;
        printf("The cube of %d is %d\n", val, t);
    }
}


int
main(int argc, char *argv[])    /* Allocated in frame for main() */
{
    static int key = 9973;      /* Initialized data segment */
    static char mbuf[10240000]; /* Uninitialized data segment */
    char *p;                    /* Allocated in frame for main() */
    p = malloc(1024);           /* Points to memory in heap segment */
    doCalc(key);
    exit(EXIT_SUCCESS);
}
