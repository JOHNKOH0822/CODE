// NOTE : I turn the entire dcl and undcl to functions and call them in main
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAXTOKEN 100
enum { NAME, PARENS, BRACKETS }; // NAME = 0, PARENS = 1, BRACKETS = 2
void dcl(void);
void dirdcl(void);
int gettoken(void);
int getch(void);
void ungetch(int);
void dcl_program(void);  // the dcl main logic
void undcl_program(void); // the undcl main logic
/* Exercise 5-18 */
void error_recover(void);
int tokentype; /* stores what kind of token was last read. either NAME, PARENS, BRACKETS, or a single character like '(', '*', '\n'. */
char token[MAXTOKEN]; /*  stores the actual text of the last token read  e.g. "argv" or "[13]" or "()"*/
char name[MAXTOKEN]; /*  stores the identifier name found during parsing  e.g. "argv" or "pf"*/
char datatype[MAXTOKEN]; /* stores the base type from the beginning of the declaration. e.g. "int" or "char" */
char out[1000]; /* the output string being built up as parsing happens   e.g. "pointer to array[13] of"*/


/* convert declaration to words */
int main()
{
    dcl_program();
}

// when error ignore it and call gettoken() again
void error_recover(void)
{
    while(tokentype != '\n' && tokentype != EOF)
    {
        gettoken();
    }
}


void dcl_program(void)
{
    while(gettoken() != EOF) /* 1st token on line */
    {
        strcpy(datatype, token);  // save base type e.g "int" or "char"
        out[0] = '\0'; // clear output string
        dcl(); // parse the rest
        if(tokentype != '\n') 
        {
            printf("syntax error");
        }
        printf("%s : %s %s\n", name , out, datatype);
    }
    return ;
}

void undcl_program(void)
{
    int type;
    char temp[MAXTOKEN];
    while(gettoken() != EOF)
    {
        strcpy(out, token);
        while((type = gettoken()) != '\n')
        {
            if(type == PARENS || type == BRACKETS)
            {
                strcat(out, token);
            }
            else if(type == '*')
            {
                if(strchr(out, '(') != NULL || strchr(out, '[') != NULL) // check whether ( appear in output string or not
                {
                    sprintf(temp, "(*%s)", out);
                }
                else
                {
                    sprintf(temp, "*%s", out);
                }
                strcpy(out, temp);
            }
            // since the NAME here is for int or char.. then it add the int before the token 
            // since we converting the "argv: pointer to int" back to int *argv
            else if(type == NAME)
            {
                sprintf(temp, "%s %s", token, out);
                strcpy(out, temp);
            }
            else
            {
                printf("invalid input at %s\n", token);
            }
        }
    }
    printf("%s\n", out);
    return;
}

#define MAXVAL 100  
#define BUFFSIZE 100 
#define MAXLINE 1000
int sp = 0;
double val[MAXVAL];
int buf[BUFFSIZE]; 
int bufp = 0; 
int getch(void) // to get the char
{
    return(bufp > 0) ? buf[--bufp] : getchar(); 
}
void ungetch(int c) 
{
    if(bufp >= BUFFSIZE)
    {
        printf("ungetch : too many characters\n");
    }
    else 
    {
        buf[bufp++] = c; 
    }
}

int gettoken(void)
{
    int c, getch(void);
    void ungetch(int);
    char *p = token;
    while((c = getch()) == ' ' || c == '\t') // skip spaces or tab
    {
        ; 
    }
    if(c == '(')
    {
        if((c = getch()) == ')')
        {
            strcpy(token, "()");
            return tokentype = PARENS;
        }
        else if(isalnum(c))
        {
            *p++ = '('; // store opening (
            *p++ = c; // store first char of argument
            for( ; (*p++ = getch()) != ')'; )
            {
                ;
            }
            *p = '\0';
            return tokentype = PARENS;
        }
        else
        {
            ungetch(c);
            return tokentype = '(';
        }
    }
    else if(c == '[')
    {
        for(*p++ = c; (*p++ = getch()) != ']'; )
        {
            ;
        }
        *p = '\0';
        return tokentype = BRACKETS;
    }
    else if(isalpha(c))
    {
        for(*p++ = c; isalnum(c = getch()); )
        {
            *p++ = c;
        }
        *p = '\0';
        ungetch(c); // to push back the non alphanumeric char cuz it will stop at it when the for loop exit
        return tokentype = NAME ;
    }
    else
    {
        return tokentype = c;
    }
}

/* dirdcl: parse a direct declarator */
void dirdcl(void)
{
    int type;
    if (tokentype == '(')  /* ( dcl ) */
    {
        dcl();
        if (tokentype != ')')
        {
            printf("error: missing )\n");
            error_recover();
        }
    } 
    // Exercise 5-20 handle quantifiers
    else if (tokentype == NAME) /* variable name */
    {
        if(strcmp(token, "const") == 0 || strcmp(token, "volatile") == 0 || strcmp(token, "unsigned") == 0)
        {
            strcat(out, token);
            strcat(out, " ");
        }
        strcpy(name, token);
    }
    else
    {
        printf("error: expected name or (dcl)\n");
        error_recover();
    }
    while ((type=gettoken()) == PARENS || type == BRACKETS)
    {
        if(type == PARENS)
        {
            strcat(out, " function");
            strcat(out, token);  // append "(int, char *)" 
            strcat(out, " returning");
        }
        else
        {
            strcat(out, " array");
            strcat(out, token); // things between [ and ]
            strcat(out, " of");
        }
    }
}

/* dcl: parse a declarator */
// dcl = optional * + direct-dcl
void dcl(void)
{
    int ns;

    for(ns = 0; gettoken() == '*' ; )
    {
        ns++;
    }
    dirdcl(); // after counting all the * then call dcl to handle name 
    while(ns -- > 0) // back here
    {
        strcat(out, " pointer to");
    }
}
