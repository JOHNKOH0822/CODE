#include <stdio.h>
#define TABSTOP 8

int main()
{
    int i, c, col, space_count;
    col = space_count = 0;

    while ((c = getchar()) != EOF)
    {
        if (c == ' ')
        {
            space_count++;
            col++;
            if (col % TABSTOP == 0)
            {
                putchar('\t');
                space_count = 0;
            }
        }
        else
        {
            while (space_count > 0)
            {
                putchar(' ');
                space_count--;
            }

            if (c == '\n')
            {
                putchar('\n');
                col = 0;
                space_count = 0;
            }
            else if (c == '\t')
            {
                putchar('\t');
                col += (TABSTOP - (col % TABSTOP));
            }
 
            else
            {
                putchar(c);
                col++;
            }
        }
    }
    return 0;
}
