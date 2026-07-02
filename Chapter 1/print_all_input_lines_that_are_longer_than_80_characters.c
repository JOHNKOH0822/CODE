#include <stdio.h>

#define MAXLINE 1000
int getline(char line[], int maxline);	
int main()
{
    int len;
    char line[MAXLINE];

    while ((len = getline(line, MAXLINE)) > 0)
    {
        if (len > 80)
        {
            printf("%s", line);
        }
    }

    return 0;
}

int getline(char s[], int lim)
{
    int c, i, len;
    len = 0;
    for (i = 0; (c = getchar()) != EOF && c != '\n'; i++)
    {
        if (i < lim - 1)
            s[i] = c;

        len++;
    }

    if (c == '\n')
    {
        if (i < lim - 1)
            s[i] = c;

        len++;
        i++;
    }

    if (i < lim)
        s[i] = '\0';

    return len;
}