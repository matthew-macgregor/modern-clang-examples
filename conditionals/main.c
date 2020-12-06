#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int main(void)
{
    int falsey = 0; // zero is "false"
    int truthy = 1; // any non-zero int is "true"

    // Don't get confused with return codes. A process
    // returns 0 on success.

    // Don't get confused with strcmp(), which returns
    // 0 if the strings are exactly equal, b/c it's a compare.

    if (truthy)
    {
        assert(truthy == true);
    }

    if (!falsey)
    {
        assert(falsey == false);
    }

    srand(time(NULL));

    int x = rand() % 3;
    switch (x) {
        case 0: printf("ZERO: %d\n", x); break;
        case 1: printf("ONE: %d\n", x); break;
        default: printf("No idea: %d\n", x); break;
    }

    return 0;
}