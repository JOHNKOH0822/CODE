#include <stdio.h>
void squeeze(char s1[], char s2[]);
int main()
{
    char s1[1000], s2[1000];
    int c, i = 0, j = 0;
    while ((c = getchar()) != '\n' && c != EOF && i < 999)
    {
        s1[i++] = c;
    }
    s1[i] = '\0';
        while ((c = getchar()) != '\n' && c != EOF && j < 999)
    {
        s2[j++] = c;
    }
    s2[j] = '\0';
    squeeze(s1, s2);
    printf("%s\n", s1);
    return 0;
}
void squeeze(char s1[], char s2[])
{
    int i, j, k;
    int found;
    for (i = j = 0; s1[i] != '\0' ; i++)
    {
        found = 0;
        for ( k = 0; s2[k] != '\0'; k++)
        {
            if (s1[i] == s2[k])
            {
                found = 1;
                break;
            }
        }
        if (!found)
        {
            s1[j++] = s1[i];
        }
    }
    s1[j] = '\0';
}
