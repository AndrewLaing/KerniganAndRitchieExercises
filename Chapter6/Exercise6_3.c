/* Write a cross-referencer that prints a list of all words in a document, and for
   each word, a list of the line numbers on which it occurs. Remove noise words
   like 'the,' 'and,' and so on.  

TODO:

    1: Tokenizing  
    2: Case-sensitivity of string checking routine.


1: A decent tokenizer to deal with apostrophed and hyphenated words
   urls and emails.

2: lower-case all words using the lower function below to convert whilst
   adding the string letter by letter into a char array,just before the
   following line, so that only lowercase are getting added to the tree.

            if((n=binsearch(word,keytab,NKEYS))<0) {


lower: convert c to lower-case; ASCII only
int lower(int c)
{
    if(c>=A && c<=Z)
        return c + 'a' - 'A';
    else
        return c;
}
*/


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define BUFSIZE 1000
#define MAXWORD 1000
#define MAXLINES 1000

static char *keytab[] = { "a","about","above","after","again","all","also","am","an",
                  "and","any","are","aren't","as","at","be","because","been",
                  "before","being","below","between","both","but","by",
                  "can't","cannot","could","couldn't","did","didn't","do",
                  "does","doesn't","doing","don't","down","during","each",
                  "even","every","few","for","from","further","had","hadn't",
                  "has","hasn't","have","haven't","having","he","he'd","he'll",
                  "he's","her","here","here's","hers","herself","him","himself",
                  "his","how","how's","i","i'd","i'll","i'm","i've","if","in",
                  "into","is","isn't","it","it's","its","itself","let's","me",
                  "more","most","mustn't","my","myself","no","nor","not",
                  "of","off","on","once","only","or","other","ought","our","ours",
                  "out","over","own","said","same","say","says","shan't",
                  "she","she'd","she'll","she's","should","shouldn't","so",
                  "some","still","such","than","that","that's","the","their",
                  "theirs","them","then","there","there's","these","they",
                  "they'd","they'll","they're","they've","this","those",
                  "through","to","too","under","until","up","very","was",
                  "wasn't","we","we'd","we'll","we're","we've","were","weren't",
                  "what","what's","when","when's","where","where's","which",
                  "while","who","who's","whom","why","why's","will","with",
                  "won't","would","wouldn't","you","you'd","you'll","you're",
                  "you've","your","yours","yourself"
};

#define NKEYS 178 /* space req between NKEYS ()*/

struct tnode {            /* the tree node:       */
    char *word;           /* points to the text   */
    int lines[MAXLINES];
    int count;            /* number of occurences */
    struct tnode *left;   /* left child           */
    struct tnode *right;  /* right child          */
};

void titleline(void);
int binsearch(char *word, char *tab[], int n);
struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);

int getch(void);
void ungetch(int c);

char buf[BUFSIZE];
int bufp = 0;
int linenum = 0;
int lineflag = 0;


/* word frequency count */
main()
{
    int n;
    struct tnode *root;
    char word[MAXWORD];

    root = NULL; /* pointer to NULL */
    
    while(getword(word, MAXWORD) != EOF)
    {
        if(isalpha(word[0])) {
            if((n=binsearch(word,keytab,NKEYS))<0) {
                root = addtree(root, word);
                if(lineflag) {
                    lineflag=0;
                    linenum++;
                }
            }
            if(lineflag) {
                lineflag=0;
                linenum++;
            }
        }
    }
    
    titleline();
    treeprint(root);
    
    return 0;
}


void titleline(void)
{
    puts("----------------------------");
    printf("%-15s %s \n", "word", "line numbers");
    puts("----------------------------");
}


/* binsearch: find word in tab[0]...tab[n-1] */
int binsearch(char *word, char *tab[], int n)
{
    int cond;
    int low, high, mid;

    low  = 0;
    high = n-1;
    while(low <= high) 
    {
        mid = (low+high)/2;
    
        if((cond=strcmp(word,tab[mid])) < 0)       /* do a binary search amongst keywords */
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

    if(p == NULL) {      /* a new word has arrived */
        p=talloc();      /* make a new node        */
        p->word  = strdup1(w);
        p->lines[0]=linenum;
        p->count = 0;
        p->left  = p->right = NULL;
    } 
    else if ((cond = strcmp(w, p->word)) == 0) 
    {
        if(p->lines[p->count]!=linenum) 
        {
            p->count++;
            p->lines[p->count]=linenum; 
        }
    } 
    else if(cond < 0)  /* less than into left subtree */
        p->left  = addtree(p->left, w);
    else                 /* greater than into right subtree */
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
    
    if(!isalpha(c)) 
    {
        if(c=='\n')
            linenum++;
        *w = '\0';
        return c;
    }
    
    for( ; --lim > 0; w++)
    {
        if(!isalnum(*w=getch())) 
        {
            if(*w=='\n') lineflag=1;
            ungetch(*w);             
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


/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
    int i;

    if(p!=NULL) 
    {
        treeprint(p->left);
        p->count--;
        printf("%-15s", p->word);
    
        for(i=0 ; i <= p->count+1; i++)
            printf(" %3d",p->lines[i]);
    
        printf("\n");
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
