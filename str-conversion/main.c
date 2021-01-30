#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define BASE_10 10

void ex_atoi()
{
    int i = atoi("55");
    assert(i == 55);
    i = atoi("abc");
    // zero is not guaranteed by the standard!
    assert(i == 0);
}

void ex_strtol()
{
    char *numstr = "12345EightyEight";
    char *last;
    long result = strtol(numstr, &last, BASE_10);
    assert(result == 12345);
    assert(strcmp(last, "EightyEight") == 0);
}

int main(void)
{
    ex_atoi();
    ex_strtol();
    return 0;
}