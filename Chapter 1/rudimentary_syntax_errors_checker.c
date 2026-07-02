#include <stdio.h>

#define MAX_STACK 1000
#define CODE 0
#define STRING 1
#define CHAR 2
#define LINE_COMMENT 3
#define BLOCK_COMMENT 4

int main() {
    int c, next_c;
    int state = CODE; //  start reading normal code
    
    char stack[MAX_STACK]; // The memory array to hold our brackets
    int top = 0;           // Points to the next empty slot in the stack
    
    int line = 1;  // Keeps track of what line we are on for error messages
    int error = 0; // A flag (0 = no error, 1 = error found)

    while ((c = getchar()) != EOF)
    {
        // If we hit an Enter key, increase the line count
        if (c == '\n')
        {
            line++;
        }

        // --- FILTER SECTION: What mode are we in? ---
        if (state == CODE)
        {
            if (c == '"')
            {
                state = STRING; // Enter string mode
            }
            else if (c == '\'')
            {
                state = CHAR;   // Enter character mode
            }
            else if (c == '/')
            {
                next_c = getchar(); // Peek at the next letter
                if (next_c == '/')
                {
                    state = LINE_COMMENT; // It's a // comment
                }
                else if (next_c == '*')
                {
                    state = BLOCK_COMMENT; // It's a /* comment
                }
                else 
                {
                    ungetc(next_c, stdin); // False alarm, put the letter back!
                }
            }
            // --- STACK SECTION: Only check brackets if we are in normal code ---
            else if (c == '(' || c == '[' || c == '{')  // If top reaches MAX_STACK, you have run out of memory. 
                                                        //  If top is 0 when you try to close a bracket, you have a syntax error (closing a bracket that was never opened).
            {
                if (top < MAX_STACK)
                {
                    stack[top++] = c; // Save the opening bracket and move 'top' up
                }
                else
                {
                    printf("Fatal: Stack overflow on line %d\n", line);
                    return 1; // Crash the program if we run out of memory
                }
            }
            else if (c == ')' || c == ']' || c == '}')
            {
                // If we see a closer, but the stack is empty, it's an error
                if (top == 0)
                {
                    printf("Error (Line %d): Closing '%c' has no matching opener.\n", line, c);
                    error = 1;
                }
                else
                {
                    top--; // Step back one slot to look at the last saved opener
                    char expected;
                    
                    // Figure out what opener we SHOULD be seeing
                    if (c == ')') 
                    { 
                        expected = '('; 
                    }
                    if (c == ']') 
                    { 
                        expected = '['; 
                    }
                    if (c == '}') 
                    { 
                        expected = '{'; 
                    }
                    
                    // Compare what we expect with what is actually in the stack
                    if (stack[top] != expected)
                    {   
                        printf("Error (Line %d): Found '%c', expected closer for '%c'.\n", line, c, stack[top]);
                        error = 1;
                    }
                }
            }
        } // End of CODE state

        // --- IGNORING STRINGS AND CHARACTERS ---
        else if (state == STRING)
        {
            if (c == '\\')
            {
                getchar(); // If we see a backslash, eat the next letter entirely so it can't trick us
            }
            else if (c == '"')
            {
                state = CODE; // Quote closed, back to normal
            }
        }
        else if (state == CHAR)
        {
            if (c == '\\')
            {
                getchar(); // Eat escaped character
            }
            else if (c == '\'')
            {
                state = CODE; // Char closed, back to normal
            }
        }

        // --- IGNORING COMMENTS ---
        else if (state == LINE_COMMENT)
        {
            if (c == '\n')
            {
                state = CODE; // Newline ends a line comment
            }
        }
        else if (state == BLOCK_COMMENT)
        {
            if (c == '*')
            {
                next_c = getchar(); // Peek to see if a slash comes next
                if (next_c == '/')
                {
                    state = CODE; // Block comment ended
                }
                else
                {
                    ungetc(next_c, stdin); // Not a slash, put the character back
                }
            }
        }
    } 

    // The file ended. If the stack isn't empty, we forgot to close something.
    if (top > 0 && !error) 
    {
        printf("Error (EOF): File ended but %d bracket(s) are still open.\n", top);
        printf("The last unclosed bracket was: '%c'\n", stack[top - 1]);
        error = 1;
    }

    if (!error) 
    {
        printf("Syntax check passed! All brackets balanced.\n");    
    }

    return 0;
}