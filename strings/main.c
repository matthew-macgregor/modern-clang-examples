#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

// memchr - searches num bytes for value, returns pointer to first value or null
// const void * memchr ( const void * ptr, int value, size_t num );
void memchr_ex ()
{
    char s1[] = "Hello World";
    char *v = memchr(s1, 'W', 10);
    assert(*v == 'W');
    v = memchr(s1, 'X', 10);
    assert(v == NULL);
}

// memcmp - Compares num bytes, returns 0 if match, does not stop at \0
// int memcmp ( const void * ptr1, const void * ptr2, size_t num );
void memcmp_ex ()
{
    char buffer1[] = "alfownepojs\0asd";
    char buffer2[] = "alfownepojs\0asd";
    int r = memcmp(buffer1, buffer2, sizeof(buffer1));
    assert(r == 0);
    buffer2[5] = 'X';
    r = memcmp(buffer1, buffer2, sizeof(buffer1));
    assert(r > 0);
}

// memcpy - copy num bytes from source to dest, returns dest
// void * memcpy ( void * destination, const void * source, size_t num );
void memcpy_ex ()
{
    char buffer1[] = { 0x01, 0x02, 0x0F };
    char buffer2[3];
    char *b = memcpy(buffer2, buffer1, 3);
    assert(b[2] == 0x0F);
}

// memmove - move block of bytes from source to dest, returns dest.
// Source and dest can overlap.
// void * memmove ( void * destination, const void * source, size_t num );
void memmove_ex ()
{
    char str[] = "In a hole in the ground, there lived a Hobbit...";
    char *s = memmove(str, str + 10, 13);
    assert(strcmp(s, "in the groundthe ground, there lived a Hobbit...") == 0);
}

// memset - fill num bytes of ptr to value, returns ptr
// void * memset ( void * ptr, int value, size_t num );
void memset_ex ()
{
    char str[] = "In a hole in the ground, there lived a Hobbit...";
    memset(str + 5, '*', 4);
    memset(str + strlen(str) - 9, '*', 6);
    assert(
        strcmp(str, "In a **** in the ground, there lived a ******...") == 0
    );
}

// strchr - Returns a pointer to the first occurrence of character in the C string str.
// const char * strchr ( const char * str, int character );
void strchr_ex ()
{
    char str[] = "0XXX0XXXY0XXX";
    char *y = strchr(str, 'Y');
    assert(y[0] == 'Y');
    assert(y[1] == '0');
    char *n = strchr(str, 'W');
    assert(n == NULL);
}

// strcmp - Compares strings char by char <0, 0, >0
// int strcmp ( const char * str1, const char * str2 );
void strcmp_ex ()
{
    char s1[] = "Stromboli Express";
    char s2[] = "Stromboli Express";
    char s3[] = "Stramboli Express";
    assert(strcmp(s1, s2) == 0);
    assert(strcmp(s2, s3) > 0);
    assert(strcmp(s3, s1) < 0);
}

// strncmp - Compares up to n chars of str
// int strncmp ( const char * str1, const char * str2, size_t num );
void strncmp_ex ()
{
    char s2[] = "Stromboli Express";
    char s3[] = "Stramboli Express";
    assert(strncmp(s2, s3, 3) == 0);
    assert(strncmp(s2, s3, 5) > 0);
}

// strcoll - Compares s1 to s2 via LC_COLLATE category of the C locale currently selected.
// int strcoll ( const char * str1, const char * str2 );
void strcoll_ex ()
{
    // strcoll is more expensive than strcmp
    char *strs[ ] = { "ch", "h" };
    setlocale(LC_COLLATE, "cs_CZ.UTF-8" );
    assert(strcoll(strs[0], strs[1]) > 0);
    setlocale(LC_COLLATE, "en_US.UTF-8");
    assert(strcoll(strs[0], strs[1]) < 0);
}

// strcspn - returns number of leading characters not in str2
// size_t strcspn ( const char * str1, const char * str2 );
void strcspn_ex ()
{
    char str[] = "Y2K in the year 2000";
    char search[] = "0";
    assert(strcspn(str, search) == strlen(str) - 3);
}

// strerror - gets a string message from error number
// char * strerror ( int errnum );
void strerror_ex ()
{
    // Locale specific, so not a great example
    printf("Error example (locale): %s\n", strerror(EINVAL));
}

// strncat - Appends source to destination, plus null terms, up to n chars.
// char * strncat ( char * destination, const char * source, size_t num );
void strncat_ex ()
{
    char buffer[20] = "Hello";
    strncat(buffer, " World        !", 6);
    assert(strcmp(buffer, "Hello World") == 0);
}

// strpbrk
// const char * strpbrk ( const char * str1, const char * str2 );
void strpbrk_ex ()
{
    char haystack[] = "Zero One Two Xero";
    char needle[] = "ZX";
    char *found = strpbrk(haystack, needle);
    assert(found == haystack);
    found = strpbrk(++found, needle); // skip the first char
    assert(found == (haystack + 13));
}

// strrchr - returns pointer to last char in str or null
// const char * strrchr ( const char * str, int character );
void strrchr_ex ()
{
    char haystack[] = "Robots Xtra";
    char *needle = strrchr(haystack, 'X');
    assert(needle == (haystack + 7));
    needle = strrchr(haystack, '\0');
    // You can use it to find the end of a string
    assert(needle == haystack + strlen(haystack));
}

// strspn - Returns length of start of string containing chars from s2
// size_t strspn ( const char * str1, const char * str2 );
void strspn_ex ()
{
    char s1[] = "1000 times the amount";
    char nset[] = "0123456789";
    int i = strspn(s1, nset);
    assert(i > 0 && i == 4);
}

// strstr - returns a ptr to 1st s2 in s1 or null
// const char * strstr ( const char * str1, const char * str2 );
void strstr_ex ()
{
    char s1[] = "In a hole in the ground...";
    char s2[] = "hole";
    char *ptr = strstr(s1, s2);
    assert(ptr == (s1 + 5));
}

// strxfrm
// Skipping this -- locale-specific transform

// strcat
void strcat_ex ()
{
    char str1[11] = "Hello";
    char str2[10] = "World";
    strcat(str1, str2); // Append str2 to str1
    // Make sure that str1 has space first!
    assert(strcmp(str1, "HelloWorld") == 0);
}

// strcpy
// char * strcpy ( char * destination, const char * source );
void strcpy_ex ()
{
    /* Found errata on page 37 with this code: */
    char s1[12] = "Hello";
    char s2[12] = "World";
    /* Copy s1 into s2 */
    strcpy(s2, s1); /* s2 = "Hello" */
    assert(strcmp(s2, "Hello") == 0);

    strcpy(s2, "Whamm222");
    strcpy(s2, s1); // Result is "Hello" b/c of \0
    assert(strcmp(s2, "Hello") == 0);

    char str1[11] = "Hello";
    char str2[11] = "World";
    strcpy(str2, str1);
    // Make sure that str2 has space first!
    assert(strcmp(str2, "Hello") == 0);
}

// strncpy
// char * strncpy ( char * destination, const char * source, size_t num );
void strncpy_ex ()
{
    char buffer[20] = "Wild Horses";
    char str1[] = "Ten Thousand Words";
    strncpy(buffer, str1, 20);
    assert(strcmp(buffer, str1) == 0);
    strncpy(buffer, str1, 19);
    assert(strcmp(buffer, "Ten Thousand Words") == 0);
}

// strlen
// size_t strlen ( const char * str );
void strlen_ex ()
{
    char str1[] = "Futurama";
    int sz = strlen(str1);
    assert(sz == 8);
    assert(sizeof str1 == 9);
}

// sizeof - when used with strings
void sizeof_ex ()
{
    // sizeof only works for statically allocated strings
    // sizeof will count the null-term character
    char s1[] = "Hello";
    char s2[] = "World";
    char s3[sizeof(s1) + sizeof(s2) -1];
    strcpy(s3, s1);
    strcat(s3, s2);
    assert(strcmp(s3, "HelloWorld") == 0);
}

// strtok
// char * strtok ( char * str, const char * delimiters );
void strtok_ex ()
{
    char str[] = "In a hole in the ground...";
    char *pch;
    char *words[6];
    pch = strtok(str, " .");
    int i = 0;
    while (pch != NULL)
    {
        if (strcmp(pch, "") != 0)
        {
            words[i++] = pch;
        }
        pch = strtok(NULL, " .");
    }

    assert(strcmp(words[5], "ground") == 0);
}

void basic_string ()
{
    char str1[10] = "Hello";
    char str2[10] = "World";
    printf("%s %s\n", str1, str2);
}

int main(void)
{
    basic_string();
    memchr_ex();
    memcmp_ex();
    memcpy_ex();
    memmove_ex();
    memset_ex();
    strcat_ex();
    strncat_ex();
    strchr_ex();
    strrchr_ex();
    strcmp_ex();
    strcoll_ex();
    strncmp_ex();
    strcspn_ex();
    strcpy_ex();
    strncpy_ex();
    strerror_ex();
    strpbrk_ex();
    strlen_ex();
    strspn_ex();
    strstr_ex();
    sizeof_ex();
    strtok_ex();
    return 0;
}