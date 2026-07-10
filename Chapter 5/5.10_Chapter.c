#include <stdio.h>
#include <string.h>
#define MAXLINE 1000


// argc and argv are how your program receives input from the terminal when it starts.
// if u type ./code hello world then u can pass it directly to the command

/* 1st version
    int i;
    for (i = 1; i < argc; i++)
    {
        printf("%s%s", argv[i], (i < argc-1) ? " " : ""); // 1st %s for agrv[] next is for " " print the command after ./code and the if loop is for spacing if is the last word no space needed
    }
    printf("\n");
    return 0;
*/
/*  2nd version
    while (--argc > 0) // check whether still got command pre-decrement to exclude ./code
    {
        printf("%s%s", *++argv, (argc > 1) ? " " : ""); // increase argv first then print argc
    }
    printf("\n");
    return 0;
*/

int getline (char *line, int max)
{
    int i = 0, c;
    while(-- max > 0 && (c = getchar()) != EOF && c != '\n')
    {
        *line++ = c;
        i++;
    }
    if(c == '\n')
    {
        *line++ = c;
        i++;
    }
    *line = '\0'; 
    return i;
}
/*
strstr(s, t) — searches for string t inside string s. returns a pointer to where t first appears in s,
or NULL if not found.
strstr("hello world", "world")  // returns pointer to "world" in the string
strstr("hello world", "xyz")    // returns NULL
*/

/*  1st version of spot pattern
    char line[MAXLINE];
    int found = 0;
    if(argc != 2) // if print more than 2 or less than 2 cant find pattern
    {
        printf("Usage: find pattern\n");
    }
    else
    {
        while(getline(line, MAXLINE) > 0)
        {
            if(strstr(line, argv[1])!= NULL) // compare the input line with command argv ( pattern )
            {
                printf("%s", line);
                found ++;
            }
        }
    }
    return found;


the outer while loop check the next argv is start with - or not  
the inner while loop check the current argv[0] whether the char after - is x or n or invalid

(*++argv)[0] see ++argv first so move to next argv move from argv[0] to [1] then * dereference last [0] check the first char o argv[1]

*++argv[0] see argv[0] first current string then ++argv[0] move it to next char then * dereference
 
*/
int main(int argc, char *argv[])
{
    char line[MAXLINE];
    long lineno = 0;
    int c, except = 0, number = 0, found = 0;
    while(--argc > 0 && (*++argv)[0] == '-') // --argv > 0 means still have arguements left and (*++argv)[0] == '-' means check next arguement is it start if - 
    // (*++argv)[0] moves to the next argument and checks its first character
    {
        while(c = *++argv[0]) // moves inside the current argument string 
        {
            switch(c)
            {
                case 'x':
                    except = 1;
                    break;
                
                case 'n':
                    number = 1;
                    break;
                
                default :
                    printf("find: illegal option %c\n", c);
                    argc = 0;
                    found = -1;
                    break;
            }
        }
    }
    if(argc != 1) // if not 1 means either no pattern or too many arguement
    {
        printf("Usage : find -x -n pattern\n");
    }
    else
    {
        while(getline(line, MAXLINE) > 0)
        {
            lineno++; // line number
            if((strstr(line, *argv) != NULL) != except) // if match found, strstr(...) != NULL gives you 1 
                                                        // except = 1 when -x reads so 1 != 1 is false so gives 0 then skip match input
            {
                if(number) // if number = 1
                {
                    printf("%ld:", lineno); // print the lineno
                }
                printf("%s", line);
                found ++;
            }
        }
    }
    return found;
}

