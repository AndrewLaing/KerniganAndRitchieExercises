/* Our version of getword does not properly handle underscores, string constants,
 * comments, or preprocessor control lines. Write a better version.
 * */
#include <stdio.h>
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

#define NKEYS (sizeof keytab / sizeof(keytab[0])) /* space req between NKEYS ()*/
char buf[BUFSIZE];
int bufp = 0;

int getword(char *, int);
int binsearch(char *, struct key *, int);
int escapecom(char *w);


/* count C keywords */
main()
{
    int n;
    char word[MAXWORD];

    while(getword(word,MAXWORD)!=EOF)
    {
        if(isalpha(word[0]) || word[0]=='#')
            if((n=binsearch(word,keytab,NKEYS))>=0)
                keytab[n].count++;
    }
    
    for(n=0; n<NKEYS; n++)
    {
        if(keytab[n].count > 0)
            printf("%4d %s\n",
                keytab[n].count, keytab[n].word);
    }
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
    
    if(!isalpha(c) && c!='"' && c!='\'' && c!='_' && c!='/' && c!='#') 
    {
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
        if(!isalnum(*w=getch()) && *w!='_') {
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
