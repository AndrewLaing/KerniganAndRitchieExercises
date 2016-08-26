/* Write a program that prints the distinct word in its input sorted into
 * decreasing order of occurrence. prints each word by its count */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define BUFSIZE 100
#define MAXWORD 100

struct tnode {            /* the tree node:       */
    char *word;           /* points to the text   */
    int count;            /* nunber of occurances */
    struct tnode *left;   /* left child           */
    struct tnode *right;  /* right child          */
};

struct tnode *addtree(struct tnode *, char *);
void treeindex(struct tnode *);
int getword(char *, int);

int getch(void);
void ungetch(int c);

struct tnode *structindex[MAXWORD];
int nstructs = 0;

void qsort1(struct tnode *v[], int left, int right);
void swap(struct tnode *v[], int i, int j);
void writelines(void);


char buf[BUFSIZE];
int bufp = 0;


/* word frequency count */
main()
{
    struct tnode *root;
    char word[MAXWORD];

    root = NULL; /* pointer to NULL */
    
    while(getword(word, MAXWORD) != EOF)
    {
        if(isalpha(word[0]))
            root = addtree(root, word);
    }
    
    treeindex(root);
    qsort1(structindex, 0, nstructs-1);
    writelines();
    
    return 0;
}


struct tnode *talloc(void);
char *strdup1(char *);


/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;

    if(p == NULL) {    /* a new word has arrived */
       p=talloc();     /* make a new node        */
       p->word  = strdup1(w);
       p->count = 1;
       p->left  = p->right = NULL;
    } 
    else if ((cond = strcmp(w, p->word)) == 0)
        p->count++;    /* repeated word */
    else if(cond < 0)  /* less than into left subtree */
        p->left  = addtree(p->left, w);
    else               /* greater than into right subtree */
        p->right = addtree(p->right, w);
    
    return p;
}


/* getword: get nextword or character from input */
int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while(isspace(c=getch()))
        ;
        
    if(c!=EOF)
        *w++ = c;
    
    if(!isalpha(c) && c!='-') 
    {
        *w = '\0';
        return c;
    }
    
    for( ; --lim > 0; w++)
    {
        if(!isalnum(*w=getch()) && *w!='_' && *w!='"') {   /* This adds to word and breaks on non-alnum*/
            ungetch(*w);              /* so continue with underscores */
            break;
        }
    }
    *w = '\0';
    
    return word[0];
}


/* get a (possibly pushed-back) character */
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar(); 
}


/* push character back on input */
void ungetch(int c)
{
    if(bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}


/* treeindex: make an array of pointers to the tree nodes */
void treeindex(struct tnode *p)
{
    if(p!=NULL) 
    {
        treeindex(p->left);
        structindex[nstructs++] = p;
        treeindex(p->right);
    }
}


/* talloc: make a tnode */
struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}


char *strdup1(char *s) /* make a duplicate of s */
{
    char *p;

    p=(char *) malloc(strlen(s)+1); /* +1 for '\0' */
    
    if(p!=NULL)
        strcpy(p, s);
    
    return p;
}


/*qsort1: sort v[left]...v[right] into increasing order */
void qsort1(struct tnode *v[], int left, int right)
{
    int i, last;
    void swap(struct tnode *v[], int i, int j);    

    if(left>=right)
        return;
    
    swap(v, left, (left + right)/2);
    last = left;
    
    for(i = left+1; i <= right; i++) 
    {
        if(v[i]->count < v[left]->count)
            swap(v,++last,i);
    }
    
    swap(v,left,last);
    qsort1(v, left, last-1);
    qsort1(v, left+1, right);
}


/* swap: interchange v[i] and v[j] */
void swap(struct tnode *v[], int i, int j)
{
    struct tnode *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/* writelines: write output lines */
void writelines(void)
{
    int i;
    puts("\n---- Sorted words ----\n");
    
    while(nstructs-- > 0)
        printf("%4d  %s\n",structindex[nstructs]->count,structindex[nstructs]->word);
}
