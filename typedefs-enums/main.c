#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

typedef unsigned char BYTE;

void trivial_typedef()
{
    BYTE b = 0;
    assert(sizeof(b) == 1);
}

typedef struct
{
    int hit_points;
} character;

void struct_typedef()
{
    character conan;
    conan.hit_points = 121;
    assert(conan.hit_points == 121);
}

enum color { RED, GREEN, BLUE };

void global_enum()
{
    enum color c = RED;
    assert(c == 0);
}

void local_enum()
{
    enum fruit { APPLE, BANANA, PEACH };
    enum fruit f = APPLE;
    assert(f == 0);
    bool y = false;
    switch(f)
    {
        case APPLE:
            y = true;
    }
    assert(y == true);
}

int main(void)
{
    local_enum();
    global_enum();
    trivial_typedef();
    struct_typedef();
    return 0;
}