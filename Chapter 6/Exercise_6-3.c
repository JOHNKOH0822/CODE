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

// change to not skip newlines
int getword_ver(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()) && c != '\n' )
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

char *noise[] = {
    "a", "about", "all", "am", "an",
    "and", "any", "are", "as", "at",
    "be", "been", "but", "by", "can",
    "do", "for", "from", "has", "have",
    "he", "her", "him", "his", "i",
    "if", "in", "into", "is", "it",
    "its", "me", "my", "no", "not",
    "of", "on", "or", "our", "she",
    "that", "the", "their", "them", "then",
    "there", "this", "to", "was", "with"
};

#define NNOISE (sizeof(noise) / sizeof(noise[0]))

int is_noise(char *w) 
{
    for(int i = 0; i < NNOISE; i++)
        if(strcmp(w, noise[i]) == 0)
            return 1;
    return 0;
}

struct linelist {
    int linenum;
    struct linelist *next;
};

struct tnode {              
    char *word;             
    struct linelist *lines;              
    struct tnode *left;     
    struct tnode *right;    
} ;

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

/*
at first linenum = 1 and next = NULL
then create a new linelist node call new
then store the current linenum at new -> linenum  
point to old list [linenum=1, next=NULL] to connect the new linelist and old one 
after that return new node
*/

struct linelist *addline(struct linelist *p, int linenum)
{
    struct linelist *new = (struct linelist *) malloc(sizeof(struct linelist));
    new -> linenum = linenum;
    new -> next = p;
    return new;
}


struct tnode *addtree(struct tnode *p, char *w, int linenum)
{
    int cond;
    struct linelist *lp;
    if(p == NULL) 
    {
        p = talloc();
        p->word = my_strdup(w);
        p->lines = NULL;
        p->left = p->right = NULL;
        p->lines = addline(p->lines, linenum);
    }
    else if((cond = strcmp(w, p -> word)) == 0) 
    {
        for(lp = p->lines; lp != NULL; lp = lp->next)
        {
            if(lp->linenum == linenum)
            {
                break;
            }
        }
        if(lp == NULL)
        {
            p -> lines = addline(p->lines, linenum);
        }
    }
    else if(cond < 0) 
    {
        p -> left = addtree(p -> left, w, linenum);
    }
    else 
    {
        p -> right = addtree(p -> right, w, linenum);
    }
    return p;
}

// SINCE THE LINENUM is in opposite order and I do not want to change the addline function
// printlines :  printline in reverse order
/*
printlines(5→3→1→NULL)
    printlines(3→1→NULL)
        printlines(1→NULL)
            printlines(NULL) → return
            print 1
        print 3
    print 5
*/
void printlines(struct linelist *p)
{
    if(p != NULL)
    {
        printlines(p->next);
        printf("%d ", p->linenum);
   }
}


void treeprint(struct tnode *p)
{
    if(p != NULL)
    {
        treeprint(p->left);
        printf("%s: ", p->word);
        printlines(p->lines);
        printf("\n");
        treeprint(p->right);
    }
}

int main()
{
    struct tnode *root;
    char word[MAXWORD];
    root = NULL; 
    int linenum = 1;

    while(getword_ver(word, MAXWORD) != EOF)
    {
        if(word[0] == '\n')
        {
            linenum++;
        }
    
        else if(isalpha(word[0]))
        {
            for(int i = 0; word[i]; i++)
            {
                word[i] = tolower(word[i]);
            }
            if(!is_noise(word))
            {
                root = addtree(root, word, linenum);
            }
        }
    }
    treeprint(root); 
    return 0;
}