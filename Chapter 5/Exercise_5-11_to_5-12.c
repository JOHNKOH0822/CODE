#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define TABSTOP 8
void detab(int tabstops[], int ntabs)
{
    int i, j, c, col, space;
    col = 0;
    while ((c = getchar()) != EOF)
    {
        if (c == '\t')
        {
            if (ntabs == 0) // if didnt type in tabstops so n = 0
            {
                for (i = 0; i < 100; i++)
                {
                    tabstops[i] = (i + 1) * 8;
                }
                ntabs = 100; 
            }

            for(i = 0; i < ntabs ; i++)
            {
                if(tabstops[i] > col)
                {
                    space = tabstops[i] - col;
                    for (j = 0; j < space; j++)
                    {
                        putchar(' ');
                    }
                    break;
                }
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
            col++;
        }
    }
}

void entab(int tabstops[], int ntabs)
{
    int i, j, c, col, space_count, space;
    col = space_count = 0;

    while ((c = getchar()) != EOF)
    {
        if (c == ' ')
        {
            space_count++;
            col++;
            if(col % TABSTOP == 0)
            {
                putchar('\t');
                space_count = 0;
            }
        }
        else if (c == '\t')
        {
            if (ntabs == 0) // if didnt type in tabstops so n = 0
            {
                for (i = 0; i < 100; i++)
                {
                    tabstops[i] = (i + 1) * 8;
                }
                ntabs = 100; 
            }
            for(i = 0; i < ntabs ; i++)
            {
                if(tabstops[i] > col)
                {
                    space = tabstops[i] - col; // space needed
                    col = tabstops[i]; // set col to current tabstop cuz later we will add space
                    space_count += space; // update space count for the while loop in else
                    break;
                }
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
            else
            {
                putchar(c);
                col++;
            }
        }
    }
}
int main(int argc, char *argv[])
{
    int tabstops[100];
    int ntabs = 0;
    int i, m , n;
    while (--argc > 0)
    {
        ++argv;
        if ((*argv)[0] == '-')
            m = atoi(*argv + 1);  // skip the '-', read the number
        else if ((*argv)[0] == '+')
            n = atoi(*argv + 1);  // skip the '+', read the number
        else
            tabstops[ntabs++] = atoi(*argv);  // regular tab stop
    }
    if(n > 0)
    {
        tabstops[ntabs++] = m;  // store starting point first
        for(i = m; i < 100; ntabs++)
        {
            tabstops[ntabs] = ( i += n );
        }
    }
    entab(tabstops, ntabs);
    return 0;
}