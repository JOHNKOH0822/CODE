#include <stdio.h>
#define TABSTOP 8
int main()
{
    int i, c, col, space;
    col = 0;
    while ((c = getchar()) != EOF)
    {
        if (c == '\t')
        {
            space = TABSTOP - (col % TABSTOP);
            for ( i = 0; i < space; i++)
            {
                putchar(' ');
            }
            col += space;
        }
        else if (c == '\n')
        {
            putchar('\n');
            col = 0;
        }
        else
        {
            putchar(c);
            col ++;
        }
    }
    return 0;
}
