#include <stdio.h>
#include <assert.h>

void pointer_to_pointer ()
{
    int i = 1;
    int *p = &i;
    int **r = &p;

    assert(*r == p);
    assert(**r == *p);

    printf("Address of p: %p\n", r);
    printf("Address of i: %p\n", *r);
    printf("Value of i: %d\n", **r);
}

int main(int argc, char** argv) {
    pointer_to_pointer();
}