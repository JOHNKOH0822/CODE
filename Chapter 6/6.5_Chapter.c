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

int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while(isspace(c =getch()))
    {
        ; 
    }
    /*\
    getword returns word[0] which is the first character of the word — but EOF is -1. 
    when the loop ends naturally, getword returns word[0] which could be '\0' (zero) not -1, 
    so != EOF is always true and the loop never exits properly.
    So need to end it
    */
    if(c == EOF)   
        return EOF;
    if(c != EOF)
    {
        *w++ = c; // store c first 
    }
    if(!isalpha(c)) // check the first char is alphabet 
    {
        *w = '\0'; // if is not alphabet immediately null terminate
    }
    for( ; --lim > 0; w++) // start at second slot cuz first slot have c already
    {
        if(!isalnum(*w = getch()))
        {
            ungetch(*w);
            break;
        }
    }
    *w = '\0'; // if for loop breaks or word too long null terminates
    return word[0]; // return the first char of whatever was read
}

struct tnode {              /* the tree node: */
    char *word;             /* points to the text */
    int count;              /* number of occurrences */
    struct tnode *left;     /* left child  pointing to itself*/
    struct tnode *right;    /* right child */
} ;

/*
 malloc = memory allocation
 int arr[100] : only can hold 100
 int *arr = malloc(n * sizeof(int));  DEPENDS ON N n x 4 = size of arr
 malloc can request enough bytes to hold n integers then either 
 return void * pointer to start of block 0R NULL if failed
 arr == NULL means fail
*/


/* talloc: make a tnode */
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

 /* addtree: add a node with w, at or below p */
 /* keeps going left or right until it finds either the word or an empty spot */
struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;
    if(p == NULL) // empty slot found means new word detected
    {
        p = talloc(); // create new node
        p -> word = my_strdup(w); // copy w to struct tnode word
        p -> count = 1; // set the count as 1
        p -> left = p -> right = NULL; // set its child to NULL means empty
    }
    else if((cond = strcmp(w, p -> word)) == 0) // repeated word found
    {
        p -> count ++;
    }
    else if(cond < 0) // the word is before the current node alphabetically so go left
    {
        p -> left = addtree(p -> left, w);
    }
    else // > 0 means word is after the current node
    {
        p -> right = addtree(p -> right, w);
    }
    return p;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
    if(p != NULL)
    {
        treeprint(p -> left); // print everything smaller first
        printf("%4d %s\n", p->count, p->word); // print current node
        treeprint(p -> right); // print everything larger after
    }
}

int main()
{
    struct tnode *root;
    char word[MAXWORD];
    root = NULL; // start with empty tree

    while(getword(word, MAXWORD) != EOF)
    {
        if(isalpha(word[0])) // start with alphabet
        {
            root = addtree(root, word); // update root 
        }
    }
    treeprint(root); // print results in order
    return 0;
}