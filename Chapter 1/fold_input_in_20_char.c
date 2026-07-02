#include <stdio.h>
#define MAXCOL 20  
int main() {
    int c, col;
    char line[MAXCOL];
    int auto_wrapped = 0; /* Status if we just forced a line break (is a boolean) */

    col = 0;
    while ((c = getchar()) != EOF)
    {
        if (auto_wrapped) /*If this is true which means auto_wrapped != 0*/
        {
            if (c == ' ' || c == '\t') 
            {
                continue; /* kills the current turn and move to getchar meaning read the next char */
            } 
            else
            {
                auto_wrapped = 0; /* A real character arrived, reset status*/
            }
        }
        line[col] = c;
        col++;

        if (c == '\n') /*if input is next line and not over limit*/
        {
            for (int i = 0; i < col; i++) 
            {
                putchar(line[i]);
            }
            col = 0;
            auto_wrapped = 0; /* Reset status become initial */
        }
        else if (col >= MAXCOL) 
        {
            int break_pt = -1;
            for (int i = col - 1; i >= 0; i--) /*scan back to find a space or tab*/
            {
                if (line[i] == ' ' || line[i] == '\t') 
                {
                    break_pt = i;
                    break; /*exit the for loop and execute the code after loop*/
                }
            }

            if (break_pt != -1) /*IF there is a space*/
            {
                for (int i = 0; i < break_pt; i++) /*Print everything before the space*/
                {
                    putchar(line[i]);
                }
                putchar('\n');
                int new_col = 0;
                for (int i = break_pt + 1; i < col; i++) /*Refresh memory let the remaining become front*/
                {
                    line[new_col] = line[i];
                    new_col++;
                }
                col = new_col;
                if (col == 0)                 /* col == 0 means we break the thing ngam ngam at maxcol */
                {
                    auto_wrapped = 1;
                }
            } 
            else 
            {
                for (int i = 0; i < col; i++) /*print everything in col
                                                but always remember the col never exceed maxcol 
                                                cuz it will stopped once it is equal*/
                {
                    putchar(line[i]);
                }
                putchar('\n'); 
                col = 0;
                auto_wrapped = 1; 
            }
        }
    }
    return 0;
}