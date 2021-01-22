#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdint.h>

/*
* Unions are structs where each field shares the same memory position.
*/

union variant
{               // Bytes:
    unsigned char ch;    // 1
    unsigned short sh;   // 2
};

void test_variant()
{
    union variant v;
    v.ch = 16;
    assert(v.ch == 16);
    v.sh = 16;
    assert(v.ch == 16);
    v.sh = 128;
    assert(v.ch == 128);
    v.sh = 1000;
    assert(v.ch == 232);
}

union mixed
{
    unsigned char bytes[4];
    struct { unsigned short hi, lo; } word;
    uint32_t uint;
} m;

void test_mixed()
{
    m.uint = 0xF00F00FF;
    assert(m.word.lo == 0xF00F);
    assert(m.word.hi == 0x00FF);
    assert(m.bytes[0] == 0xFF);
    assert(m.bytes[1] == 0x00);
    assert(m.bytes[2] == 0x0F);
    assert(m.bytes[3] == 0xF0);
}

int main(void)
{
    test_variant();
    test_mixed();
    return 0;
}