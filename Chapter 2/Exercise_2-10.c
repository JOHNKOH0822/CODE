#include <stdio.h>
int lower(int c);
int main()
{
    int c;
    printf("Enter a sentence:\n");

    while ((c = getchar()) != EOF && c != '\n')
    {
        putchar(lower(c));
    }
    putchar('\n');
    return 0;
}
int lower(int c)
{
    return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c;
}

