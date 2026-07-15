#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define MAXWORD 100
#define NKEYS (sizeof keytab / sizeof(keytab[0])) 
#define MAXVAL 100  
#define BUFFSIZE 100 
#define MAXLINE 1000
#define MAXNODES 10000
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

    while (isspace(c = getch()))
        ;
    if (c != EOF)
        *w++ = c;

    
    if (!isalpha(c)) 
    {
        *w = '\0';
        return c;
    }
    for ( ; --lim > 0; w++) {
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
    }
    *w = '\0';
    return word[0];
}

struct tnode {              
    char *word;             
    int count;              
    struct tnode *left;     
    struct tnode *right;    
} ;

struct tnode *arr[MAXNODES];
int arrsize = 0;

struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

char * my_strdup(char *s)
{
    char *p;
    p = (char *) malloc(strlen(s) + 1 );
    if(p != NULL) 
    {
        strcpy(p, s); 
    }
    return p;
}

struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;
    if(p == NULL)
    {
        p = talloc(); 
        p -> word = my_strdup(w); 
        p -> count = 1; 
        p -> left = p -> right = NULL; 
    }
    else if((cond = strcmp(w, p -> word)) == 0) 
    {
        p -> count ++;
    }
    else if(cond < 0) 
    {
        p -> left = addtree(p -> left, w);
    }
    else 
    {
        p -> right = addtree(p -> right, w);
    }
    return p;
}

void fillarr(struct tnode *p, struct tnode *arr[], int *n)
{
    if(p != NULL)
    {
        fillarr(p->left, arr, n);
        arr[(*n)++] = p;
        fillarr(p->right, arr, n);
    }
}

// comparison function
// a and b are generic pointer
int cmpcount(const void *a, const void *b)
{
    // (struct tnode **)a means pointer to pointer to tnode
    // *(struct tnode **)a is a dereference which gives what is actually tnode* storing
    // then *ta means ta is a pointer to tnode so it stores the 
    // a → points to → arr[i] → points to → tnode
    /*
    a is pointing at a slot in arr, that slot contains a struct tnode *. 
    dereferencing a (after casting) gives you that struct tnode *. 
    then ta holds it and you can do ta->count.
    */
    struct tnode *ta = *(struct tnode **)a;
    struct tnode *tb = *(struct tnode **)b;
    return tb->count - ta->count;
}

int main()
{
    int n;
    struct tnode *root;
    char word[MAXWORD];
    root = NULL; 

    while(getword(word, MAXWORD) != EOF)
    {
        if(isalpha(word[0])) 
        {
            root = addtree(root, word);
        }
    }
    fillarr(root, arr, &arrsize); // pass the address if pass arrsize it will stay 0
    qsort(arr, arrsize, sizeof(struct tnode *), cmpcount);
    for(int i = 0; i < arrsize; i++)
    {
        printf("%4d %s\n", arr[i]->count, arr[i]->word);
    }
    return 0;
}