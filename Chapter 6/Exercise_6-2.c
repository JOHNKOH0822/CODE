#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define MAXWORD 100
#define NKEYS (sizeof keytab / sizeof(keytab[0])) 
#define MAXVAL 100  
#define BUFFSIZE 100 
#define MAXLINE 1000
int sp = 0;
double val[MAXVAL];
int buf[BUFFSIZE]; 
int bufp = 0; 
int getch(void) 
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

int getword_mod(char *word, int lim)
{
    int c, next_c;
    char *w = word;

    while ((c = getch()) != EOF)
    {
        if (isspace(c))
        {
            ; // keep looping/skipping spaces
        }
        else if (c == '#')
        {
            while ((c = getch()) != '\n' && c != EOF)
            {
                ; // skip preprocessor lines
            }
        }
        else if (c == '/')
        {
            next_c = getch();
            if (next_c == '*')
            {
                // Skip block comments /* ... */
                int prev = 0;
                while ((c = getch()) != EOF) // can reuse c cuz old c is no longer neededd and the outer loop will reset c
                {
                    if (prev == '*' && c == '/')
                    {
                        break;
                    }
                    prev = c;
                }
            }
            else if (next_c == '/')
            {
                // Skip single-line comments // ...
                while ((c = getch()) != '\n' && c != EOF)
                {
                    ;
                }
            }
            else
            {
                ungetch(next_c);
                break; // It's a division operator, exit loop to process it
            }
        }   
        else if (c == '"')
        {
            // Skip string constants
            while ((c = getch()) != '"' && c != EOF)
            {
                if (c == '\\') 
                {
                    getch(); // skip escaped characters like \"
                }
            }
        }
        else if (c == '\'')
        {
            // Skip character constants like "\n"
            while ((c = getch()) != '\'' && c != EOF)
            {
                if (c == '\\') 
                {
                    getch(); // skip escaped characters like \'
                }
            }
        }
        else
        {
            break; // Found a valid target character, exit loop
        }
    }

    // If we reached the end of the file, exit immediately and signal EOF
    if (c == EOF)
    {
        return EOF;
    }

    // Store the first validated character
    *w++ = c; 

    // If it is not an identifier starter, treat it as a single-char token
    if (!isalpha(c) && c != '_') 
    {
        *w = '\0'; 
        return c; 
    }

    // Collect valid identifier characters (alphanumeric + underscores)
    for ( ; --lim > 1; w++) 
    {
        c = getch();
        if (isalnum(c) || c == '_')
        {
            *w = c;
        }
        else
        {
            ungetch(c); // Push back the non-identifier character boundary
            break;
        }
    }
    *w = '\0'; 
    return word[0]; 
}

char *keywords[] = {"auto","break","case","char","const","continue",
                    "default","do","double","else","enum","extern","float","for",
                    "goto","if","int","long","register","return","short","signed",
                    "sizeof","static","struct","switch","typedef","union","unsigned",
                    "void","volatile","while"};
int nkeywords = sizeof(keywords)/sizeof(keywords[0]);

int is_keyword(char *w) // check whether is keyword or not to exclude keyword
{
    for(int i = 0; i < nkeywords; i++)
        if(strcmp(w, keywords[i]) == 0)
            return 1;
    return 0;
}

struct tnode {
    char *key;              // first 6 chars
    int count;
    struct tnode *names;    // tree of full names sharing this key
    struct tnode *left;     // left child of main tree
    struct tnode *right;    // right child of main tree
};

struct tnode *talloc(void)
{
    // reserve exactly enough memory for one tnode then return a pointer to it
    // then malloc return void* and (strcut tnode *) turn it into pointer to struct tnode
    return (struct tnode *) malloc(sizeof(struct tnode));
}

/* make a duplicate of s */
char * my_strdup(char *s)
{
    char *p;
    // malloc reserve the memory of string s + 1 is for the bytes of char '\0' 
    // char * let the pointer pointing to char 
    p = (char *) malloc(strlen(s) + 1 );
    if(p != NULL) // memory allocation does not fail
    {
        strcpy(p, s); // copy
    }
    return p;
}

struct tnode *addname(struct tnode *p, char *w)
{
    int cond;
    if(p == NULL) // new full name found
    {
        p = talloc();
        p -> key = my_strdup(w);
        p -> names = NULL;
        p ->left = p->right = NULL ;
    }
    else if((cond = strcmp(w, p->key)) == 0) // full name already exist
    {
        ; // skip
    }
    else if(cond < 0)
    {
        p -> left = addname(p->left, w);
    }
    else
    {
        p -> right = addname(p->right, w);
    }
    return p ;
}

struct tnode *addtree(struct tnode *p, char *key, char *w) // key is first 6, w is full name
{
    int cond;
    if(p == NULL) // empty slot found means new word detected
    {
        p = talloc();
        p->key = my_strdup(key);   // store the key
        p->count = 1;        // first name added
        p->names = NULL;
        p->left = p->right = NULL; // this key node has no full names stored yet
        p->names = addname(p->names, w); // add full name to names subtree
    }
    else if((cond = strcmp(key, p->key)) == 0) // key already exist
    {
        p->names = addname(p->names, w); // add w to existing names subtree
        p->count++;
    }
    else if(cond < 0) // the word is before the current node alphabetically so go left
    {
        p -> left = addtree(p->left, key, w);
    }
    else // > 0 means word is after the current node
    {
        p -> right = addtree(p->right, key, w);
    }
    return p;
}

void printnames(struct tnode *p)
{
    if(p != NULL)
    {
        printnames(p->left);
        printf("%s ", p->key);  // full name stored in key field
        printnames(p->right);
    }
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
    if(p != NULL)
    {
        treeprint(p -> left); // print everything smaller first
        if(p-> count > 1)
        {
            printf("%s: ", p->key);  // print the prefix key
            printnames(p->names);    // print all full names
            printf("\n");
        } 
        treeprint(p -> right); // print everything larger after
    }
}

int main(int argc, char *argv[])
{
    int i, n = 6;
    if(argc > 1)
    {
        n = atoi(argv[1]);       
    }
    struct tnode *root;
    char word[MAXWORD], key[MAXWORD];
    root = NULL; // start with empty tree

    while(getword_mod(word, MAXWORD) != EOF)
    {
        if(isalpha(word[0]) && !is_keyword(word)) // start with alphabet
        {
            for(i = 0; i < n && word[i] != '\0'; i++)
            {
                key[i] = word[i];
            }
            key[i] = '\0';
            root = addtree(root, key, word);
        }
    }
    treeprint(root); // print results in order
    return 0;
}