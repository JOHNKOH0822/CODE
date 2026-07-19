#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXVAL 100  
#define BUFFSIZE 100 

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


// Start here
#define IN 1
#define HASHSIZE 101

struct nlist {          /* table entry: */
    struct nlist *next; /* next entry in chain */
    char *name;         /* defined name */
    char *defn;         /* replacement text */
};

// an array of 101 pointers to nlist
static struct nlist *hashtab[HASHSIZE]; /* pointer table */


/* hash: form hash value for string s */
unsigned hash(char *s)
{
    unsigned hashval;

    for(hashval = 0; *s != '\0'; s++)
    {
        hashval = *s + 31 * hashval; // multiplying by 31 before adding the next character ensures different strings produce different values
    }
    return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s)
{
    struct nlist *np;
    // hashtab[hash(s)] is a pointer to nlist which is the first entry in that hash bucket 
    for(np = hashtab[hash(s)]; np != NULL; np = np -> next)
    {
        if(strcmp(s, np -> name) == 0)
            return np;
        
    }
    return NULL;
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

/* install: put (name, defn) in hashtab */
struct nlist *install (char *name,  char *defn)
{
    struct nlist *np;
    unsigned hashval;
    
    if((np = lookup(name)) == NULL) /* not found */
    {
        np = (struct nlist *) malloc(sizeof (*np)); // allocate memory for a new nlist node
        if(np == NULL || (np -> name = my_strdup(name)) == NULL) // fail to allocate or fail to copy
            return NULL;
        
        hashval = hash(name); // get hash position
        np -> next = hashtab[hashval]; // link new node to existing chain
        hashtab[hashval] = np; // put new node at front of chain
    }
    else
    {
        free((void *) np->defn); // free old definition
    }
    if((np->defn = my_strdup(defn)) == NULL) // replace with new definition if fail return NULL
        return NULL;
    return np;
}

// Exercise 6-5

void undef(char *name)
{
    struct nlist *prev = NULL;
    struct nlist *np;
    unsigned hashval = hash(name);

    for(np = hashtab[hashval]; np != NULL; prev = np, np = np->next)
    {
        if(strcmp(name, np -> name) == 0)
        {
            if(prev == NULL) // is first node so prev = 0
            {
                hashtab[hashval] = np->next;
            }
            else // not first
            {
                prev->next = np -> next; // link prev node to next node
            }
            free((void *) np->name);
            free((void *) np->defn);
            free((void *) np);
            return;
        }
    }
}

int main()
{
    struct nlist *np;
    
    install("MAX", "100");
    install("PI", "3.14159");
    install("NAME", "John");
    
    np = lookup("MAX");
    if(np != NULL)
        printf("%s = %s\n", np->name, np->defn);
    
    np = lookup("PI");
    if(np != NULL)
        printf("%s = %s\n", np->name, np->defn);
    
    // test update
    install("MAX", "200");
    np = lookup("MAX");
    if(np != NULL)
        printf("updated: %s = %s\n", np->name, np->defn);
    
    // test undef
    undef("PI");
    np = lookup("PI");
    if(np == NULL)
        printf("PI successfully removed\n");
    
    // test undef first node
    undef("MAX");
    np = lookup("MAX");
    if(np == NULL)
        printf("MAX successfully removed\n");
    
    // test not found
    np = lookup("NOTEXIST");
    if(np == NULL)
        printf("NOTEXIST not found\n");
    
    return 0;
}
