#include <stdio.h>
#define CODE 0          // normal code
#define SLASH 1         // saw a '/'
#define COMMENT 2       // inside /* comment */
#define STAR 3          // saw '*' inside comment (possible end)
#define STRING 4        // inside string
#define CHAR 5          // inside char
#define ESCAPE_STR 6    // escape inside string
#define ESCAPE_CHR 7    // escape inside char
#define LINE_COMMENT 8  // inside // comment
int main() {
    int c;
    int state = CODE;
    while ((c = getchar()) != EOF)
    {
        if (state == CODE) // normal code
        {
            if (c == '/')
            {
                state = SLASH; // might be start of comment
            }
            else if (c == '"') 
            {
                putchar(c);
                state = STRING; // enter string
            }
            else if (c == '\'') 
            {
                putchar(c);
                state = CHAR; // enter char literal
            }
            else
            {
                putchar(c); // normal character
            }
        }
        else if (state == SLASH) // see a / in the code
        {
            if (c == '*') // see a * so is /* and is comment
            {
                state = COMMENT; // enter comment
            }
            else if (c == '/') // see another / means // then is a comment
            {
                putchar('/');
                state = LINE_COMMENT; // enter line comment
            }
            else if (c == '"')  
            {
                putchar('/'); // print /" which is a string
                putchar(c);
                state = STRING; 
            }
            else if (c == '\'')
            {
                putchar('/'); // print /' which is char
                putchar(c);
                state = CHAR;
            }
            else 
            {
                putchar('/'); // not a comment so just print
                putchar(c);
                state = CODE; // normal code
            }
        }
        else if (state == COMMENT) // if is comment as u can see no putchar means didnt print 
        {
            if (c == '*') 
            {
                state = STAR; // possible end of comment
            }
        }
        else if (state == STAR) 
        {
            if (c == '/')
            {
                state = CODE; // end of comment
            }
            else if (c == '*')
            {
                state = STAR; // stay as star to avoid ****** case
            }
            else
            {
                state = COMMENT; // back to comment
            }
        }
        else if (state == STRING)
        {
            putchar(c);
            if (c == '"')
            {
                state = CODE; // end of string
            }
            else if (c == '\\')
            {
                state = ESCAPE_STR; // handle escape
            }
        }
        else if (state == ESCAPE_STR)
        {
            putchar(c); // print escape char
            state = STRING; // return to string
        }
        else if (state == CHAR)
        {
            putchar(c);
            if (c == '\'')
            {
                state = CODE; // end of char
            }
            else if (c == '\\')
            {
                state = ESCAPE_CHR; // escape in char
            }
        }
        else if (state == ESCAPE_CHR)
        {
            putchar(c); // print char
            state = CHAR; 
        }
        else if (state == LINE_COMMENT) // if is line comment then dont print
        {
            if (c == '\n') // but if is newline then u need to print cuz no more in line comment state
            {
                putchar('\n');
                state = CODE;
            }
            
        }
        
    }
    if (state == SLASH) /* Edge case: file ends after single '/' */
    {
        putchar('/'); // print '/' 
    }
    
    return 0;
}