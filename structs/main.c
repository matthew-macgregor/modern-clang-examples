#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Basic Struct
// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
struct Person 
{
    char *firstname, *lastname;
};

void person1()
{
    struct Person p;
    p.firstname = "Malcolm";
    p.lastname  = "Warnert";

    char buffer[50];
    sprintf(buffer, "%s %s", p.firstname, p.lastname);
    assert(strcmp(buffer, "Malcolm Warnert") == 0);
}

// Struct Member Access
// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
void member_access()
//   Struct variables are "fields" or "members", and can be 
//   accessed with the dot (".") operator. Fields don't get
//   initialized, so that is up to you.
{
    struct Person p;
    // Check that our char pointer points to garbage
    assert(&p.firstname != 0);
    // Initialize our char pointer to zero
    p.firstname = 0;
    assert(p.firstname == 0);
    char *phrase = "Hello World!";
    p.firstname = phrase;
    // Check that the address of firstname isn't null anymore
    assert(&p.firstname != 0);
    // Check that they are string-equal
    assert(strcmp(p.firstname, phrase) == 0);
    // Check that they point to the same area of memory
    assert(p.firstname == phrase);
}

// Struct Initialization
// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
void struct_initialization()
{
    struct point
    {
        int x, y;
    } p = { 5, 6 }, q = { 0, 0 };

    struct point r = { 1, 2 };
    assert(p.x == 5 && p.y == 6);
    assert(q.x == 0 && q.y == 0);
    assert(r.x + r.y == 3);

    // Added in C99, even better!
    struct point c99 = { .x = 99, .y = 99 };
    assert(c99.x + c99.y == 198);
}

// Unnamed Structs
// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
void unnamed_struct()
{
    // You can create an unnamed struct and its 
    // object declarations:
    struct
    {
        int x, y;
    } p1, p2;

    p1.x = 5;
    p1.y = 5;
    p2.x = 3;
    p2.y = 3;

    assert(p1.x + p1.y == 10);
    assert(p2.x + p2.y == 6);
}

// Typedef Structs
// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
void typedef_struct()
{
    typedef struct Person Person;

    // Since we typedef'd it above, we don't need to use 
    // struct Person here.
    Person p;
    p.firstname = "Mildred";
    assert(strcmp(p.firstname, "Mildred") == 0);
}

// Struct Pointers
// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

//   Structs are value types so the memory gets copied around
//   which is obviously inefficient. So use pointers!

struct Dog
{
    char needs_walk;
};
//   prototype the walk_dog func so we can refer to it before 
//   defining it
void walk_dog(struct Dog *dog); 

void struct_pointers()
{
    struct Dog dog = { .needs_walk = 1 };
    walk_dog(&dog); // pass by reference
    assert(dog.needs_walk == 0);
}

void walk_dog(struct Dog *dog)
{
    // By passing the address of the dog, we're avoiding the 
    // need to copy the struct.

    dog->needs_walk = 0; // walked the dog...

    // Note: when using a pointer to struct, you need to
    // access fields with the -> operator.
}

// Bitfields
// ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
void bitfields()
{
    // Bitfields allow us to represent memory at the bit level.
    struct bits
    {
        // type, field name, : number of bits
        unsigned char a : 1;
        unsigned char b : 1;
        unsigned char c : 6;
    } a;

    assert(sizeof(a) == 1); // 1 byte, size of char
    a.a = 1;
    a.b = 1;
    a.c = 0b101010;
    assert(a.c == 42);
    // Now, let's turn it back into a char
    unsigned char x = (a.a << 7) + (a.b << 6) + a.c;
    printf("%d\n", x);
    assert(x == 0b11101010); // 234
    char buffer[10];
}

int main(void)
{
    person1();
    unnamed_struct();
    typedef_struct();
    member_access();
    struct_initialization();
    struct_pointers();
    bitfields();
    return 0;
}