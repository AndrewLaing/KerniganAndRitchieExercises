/* Write a program that read a C program and prints in alphabetical order
each group of variable names that are identical in the first 6 characters,
but different somewhere thereafter. Don't count words within strings and
comments. Make 6 a parameter that can be set from the command line

A group can contain 1 item.
The request doesn't ask for all groups of more than one item.
Note skips included filenames too.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define BUFSIZE 100

struct key {
    char *word;
    int count;
} keytab[] = {
    "#define",0,
    "#elif",0,
    "#else",0,
    "#endif",0,
    "#error",0,
    "#if",0,
    "#ifdef",0,
    "#ifndef",0,
    "#include",0,
    "#line",0,
    "#pragma",0,
    "#undef",0,
    "auto",0,
    "break",0,
    "case",0,
    "char",0,
    "const",0,
    "continue",0,
    "default",0,
    "do",0,
    "double",0,
    "else",0,
    "enum",0,
    "extern",0,
    "float",0,
    "for",0,
    "goto",0,
    "if",0,
    "int",0,
    "long",0,
    "register",0,
    "return",0,
    "short",0,
    "signed",0,
    "sizeof",0,
    "static",0,
    "struct",0,
    "switch",0,
    "typedef",0,
    "union",0,
    "unsigned",0,
    "void",0,
    "volatile",0,
    "while",0
};

struct tnode {            /* the tree node:       */
    char *word;           /* points to the text   */
    int count;            /* nunber of occurances */
    struct tnode *left;   /* left child           */
    struct tnode *right;  /* right child          */
};


#define NKEYS (sizeof keytab / sizeof(keytab[0])) /* space req between NKEYS ()*/
char buf[BUFSIZE];
int bufp = 0;
int incflag=1;             /* used to skip included filenames */

char incheck[]="#include"; /* used to skip included filenames */


struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);

int getword(char *, int);
int binsearch(char *, struct key *, int);
int escapecom(char *w);

int strlen1(char *s);

/* count C keywords */
main(int argc, char *argv[])
{
    int n, c, type=0, j=6;
    char word[MAXWORD];
    struct tnode *root;

    while(--argc>0 && (*++argv)[0] == '-') 
    {
        while(c = *++argv[0])
        {
            type=c;
            switch(type) 
            {
              case 'c':
                  break;
              default:
                  puts("error: invalid flag");
                  return -1;
            }
            
            c = *++argv[0];
            j=0;
            
            while(isdigit(**argv)) 
            {
                j = (j*10)+(**argv-'0');
                (argv[0]++);
            }
        }
    }
    
    root = NULL; /* pointer to NULL */
    
    while(getword(word,MAXWORD)!=EOF)
    {
        if(isalpha(word[0]) || word[0]=='#') {
            n=binsearch(word,keytab,NKEYS);
            if(n<0 && !incflag) {
                if(strlen1(word)>=j)
                    root = addtree(root, word);
            }
            else if(incflag && n>=0) {
                if(strcmp(incheck, word)!=0) /* used to skip included filenames */
                    incflag=0;
            }
        }
    }
    
    treeprint(root);
    
    return 0;
}


/* binsearch: find word in tab[0]...tab[n-1] */
int binsearch(char *word, struct key tab[], int n)
{
    int cond;
    int low, high, mid;

    low  = 0;
    high = n-1;
    while(low <= high) 
    {
        mid = (low+high)/2;
        
        if((cond=strcmp(word,tab[mid].word)) < 0)  /* do a binary search amongst keywords */
            high = mid-1;                          /* to see if word is amongst them      */
        else if(cond>0)                            /* if so it returns its index          */
            low=mid+1;
        else
            return mid;
    }
    return -1;
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
    
    if(!isalpha(c) && c!='\'' && c!='"' && c!='_' && c!='/' && c!='#') {
        *w = '\0';
        return c;
    }
    
    if(c=='#') {
        while((c=getch())==' ') /* skip any spaces between '#' and keyword */
            ;
        *w++=c;
    }
    
    if(c=='"')
    {
        while((c=getch()) != '"' && c!='\n' && c!=EOF)
            ;
    }
    else if(c=='\'')
    {
        while((c=getch()) != '\'' && c!='\n' && c!=EOF)
            ;
    }
    else if(c=='/') escapecom(w);
    
    for( ; --lim > 0; w++)
    {
        if(!isalnum(*w=getch()) && *w!='_') 
        {
                                      /* This adds to word and breaks on non-alnum*/
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


/* escapecom: see if a comment if so escape commented data */
int escapecom(char *w)
{
    char c;
    
    c = getch();
    if(c!='*') 
    {
        *w--; 
        while(c==' ')
            c=getch(); /* skip spaces then */
        *w++=c;        /* add char to word */
        return 0;
    }
    while(1) 
    {
        while((c=getch())!='*' && c!=EOF) /* skip chars until valid end of comment */
            ;
    
        if((c=getch())=='/' || c==EOF)
            return 0;
    }
}


/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
    if(p!=NULL) 
    {
        treeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
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


int strlen1(char *s)
{
    int i;
    i=0;

    while(s[i] != '\0') 
        ++i;
    
    return i;
}
