#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>

int mem_malloc_free()
{
    char *p = malloc(sizeof(char) * 25);
    if (p == NULL) return -1;

    if(!memcpy(p, "Hello World", 25 + 1)) return -1;

    if (p) free(p);
    p = NULL;

    return 0;
}

#define NAME_WIDTH 50
struct Person
{
    uint8_t age;
    char first_name[NAME_WIDTH];
    char last_name[NAME_WIDTH];
};

void mem_realloc()
{
    struct Person *people = malloc(sizeof(struct Person) * 10);
    struct Person *p = &people[9];
    p->age = 50;

    char* meredith = "Meredith";
    char* palmer = "Palmer";
    if(memcpy(p->first_name, meredith, strlen(meredith) + 1) != 0) return;
    if(memcpy(p->last_name, palmer, strlen(palmer) + 1) != 0) return;
    assert(people[9].age == 50);
    assert(strcmp(people[9].first_name, meredith) == 0);
    assert(strcmp(people[9].last_name, palmer) == 0);

    struct Person *people2 = realloc(people, sizeof(struct Person) * 20);
    if(people2 == NULL)
    {
        free(people);
        exit(1);
    }

    people[15].age = 19;
    assert(people[15].age == 19);
    free(people); 
}

void mem_calloc()
{
    // calloc initializes memory with zeroes
    int *i = calloc(6, sizeof(int));
    for (int j = 0; j < 6; j++)
    {
        assert(i[j] == 0);
    }
    free(i);
}

void mem_memset()
{
    const uint8_t sz = 6;
    const uint8_t bytes = sz * sizeof(int);
    int *array = (int*)malloc(bytes);
    memset(array, 0, bytes);
    for (int i = 0; i < sz; i++)
    {
        assert(array[i] == 0);
    }
    free(array);
}

int f(int ff)
{
    return ff + 1;
}

void mem_func_ptr()
{
    int (*fn)(int);

    fn = &f;
    // OR fn = f;

    assert(fn(0x00FF) == 256);
    assert((*fn)(11) == 12);
}

int main(void)
{
    // TODO: sometimes a Debug Assertion Failed: _CrtIsValidHeapPointer(block)
    // when running this test from VSCode (not command line).
    mem_malloc_free();
    mem_realloc();
    mem_calloc();
    mem_memset();
    mem_func_ptr();
    return 0;
}