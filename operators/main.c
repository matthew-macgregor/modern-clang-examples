#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>

int32_t sum(int32_t x, ...)
{
    va_list argp;
    va_start(argp, x);
    int32_t sum = 0;
    for (int i = 0; i < x; ++i)
    {
        int32_t num = va_arg(argp, int32_t);
        sum += num;
    }
    va_end(argp);
    return sum;
}

void arithmetic_operators ()
{
    int x = 3 + 2;
    int y = 3 - 2;
    int z = 3 * 2;
    int a = 3 / 2;
    int b = 3 % 2;
    int32_t s = sum(5, x, y, z, a, b);
    printf("Sum == %d\n", s);
    assert(s == 14);
}

void integer_division ()
{
    int a = 3 / 2;
    assert(a == 1); // remainder is discarded
}

void floating_point_division ()
{
    float f = 3 / 2.0F;
    float ff = 3 / (float)2;
    assert(f == ff);
    printf("F %f FF %f \n", f, ff);
}

void logical_operators ()
{
    int x = (1 && 0);
    assert(x == 0);
    x = (1 || 0);
    assert(x == 1);
    x = !(1);
    assert(x == 0);
}

void booleans ()
{
    bool b = (true && false);
    assert(b == false);
    assert(b == 0);
    b = (true || false);
    assert(b == true);
    assert(b == 1);
    b = !(true);
    assert(b == false);
}

void bitwise_operators ()
{
    int x = 0b101 & 0b100;
    assert(x == 4 && x == 0b100);
    int y = 0b101 | 0b100;
    assert(y == 5 && y == 0b101);
    int z = 0b101 ^ 0b100;
    assert(z == 1 && z == 0b001);
    int a = 0b000 << 1;
    assert(a == 0 && a == 0b000 && a == 0x000);
    int b = 0b001 << 1;
    assert(b == 2 && b == 0b010 && b == 0x002);
    int c = 0b001 >> 1;
    assert(c == 0 && c == 0b000 && c == 0x000);
}

int main(int argc, char** argv) {
    arithmetic_operators();
    integer_division();
    floating_point_division();
    logical_operators();
    booleans();
    bitwise_operators();
    return 0;
}
