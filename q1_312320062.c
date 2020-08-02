#define _BSD_SOURCE
#include <stdio.h>
#include <stdlib.h>

char globBuf[65536];            /* 1. Uninitialized data(BSS) */
int primes[] = { 2, 3, 5, 7 };  /* 2. Initialized data */

static int
square(int x)                   /* 3. Text(Code segment)*/
{
    int result;                 /* 4. STACK(stack frame of square()) */

    result = x * x;
    return result;              /* 5. By register */
}

static void
doCalc(int val)                 /* 6. Text(Code segment) */
{
    printf("The square of %d is %d\n", val, square(val));

    if (val < 1000) {
        int t;                  /* 7. STACK(stack frame of doCalc()) */
//b 13 info locals
        t = val * val * val;
        printf("The cube of %d is %d\n", val, t);
    }
}

int
main(int argc, char* argv[])    /* 8. Text(Code segment) */
{
    static int key = 9973;      /* 9. Initialized data */
    static char mbuf[10240000]; /* 10. Uninitialized data(BSS) */
    char* p;                    /* 11. STACK(stack frame of main()) */


    doCalc(key);

    exit(EXIT_SUCCESS);
}