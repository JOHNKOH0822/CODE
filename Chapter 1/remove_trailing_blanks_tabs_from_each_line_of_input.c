#include <stdio.h>

#define MAXLINE 1000

int getline(char line[], int maxline);
// 1. read a line 2. set i = len - 1 (last character) 3. move backward while it's space/tab/newline 4. cut string using '\0' 5. print cleaned line //
int main()
{
    int len, i;
    char line[MAXLINE];

    while ((len = getline(line, MAXLINE)) > 0)
    {
        i = len - 1;
        while (i >= 0 && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
        {
            i--;
        }
        if (i >= 0)
        {
            line[i + 1] = '\0';
            printf("%s\n", line);
        }
    }
    return 0;
}
// 1. read characters one by one 2. store into array 3. stop at newline or EOF or limit 4. optionally store newline 5. add '\0' to mark end 6. return length //
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

