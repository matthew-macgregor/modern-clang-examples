#include <assert.h>
#include <stdio.h>
#include <string.h>

void basic_string ()
{
    char str1[10] = "Hello";
    char str2[10] = "World";
    printf("%s %s\n", str1, str2);
}

void strcat_ex ()
{
    char str1[11] = "Hello";
    char str2[10] = "World";
    strcat(str1, str2); // Append str2 to str1
    // Make sure that str1 has space first!
    assert(strcmp(str1, "HelloWorld") == 0);
}

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

void strlen_ex ()
{
    char str1[] = "Futurama";
    int sz = strlen(str1);
    assert(sz == 8);
    assert(sizeof str1 == 9);
}

void sizeof_ex ()
{
    char s1[] = "Hello";
    char s2[] = "World";
    char s3[sizeof(s1) + sizeof(s2) -1];
    strcpy(s3, s1);
    strcat(s3, s2);
    assert(strcmp(s3, "HelloWorld") == 0);
}

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

    for (int i = 0; i < 6; i++)
    {
        printf(">> %s\n", words[i]);
    }
}

int main(void)
{
    basic_string();
    strcat_ex();
    strcpy_ex();
    strlen_ex();
    sizeof_ex();
    strtok_ex();
    return 0;
}