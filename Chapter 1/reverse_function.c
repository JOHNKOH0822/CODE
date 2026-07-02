#include <stdio.h>

#define MAXLINE 1000

void reverse(char s[], int len);
int getline(char line[], int maxline);
int main()
{
    int len, i;
    char line[MAXLINE];

    while ((len = getline(line, MAXLINE)) > 0)
    {
        if (line[len - 1] == '\n')
        {
            len --;
        }
        reverse(line, len);
        printf("%s", line);
    }
 
    return 0;
}
int getline(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
    {
        s[i] = c;
    }
    if (c == '\n')
    {
        s[i] = c;
        i++;
    }
    s[i] = '\0';
    return i;
}
void reverse(char s[], int len)
{
    int i = 0;
    int j = len - 1;
    char temp;
    while (i < j)
    {
        temp = s[i]; //save current char to temporary char//
        s[i] = s[j]; //let the corresponding char to be current char//
        s[j] = temp; //let the position of corresponding char set as current char//
        i++;
        j--;
    }

}