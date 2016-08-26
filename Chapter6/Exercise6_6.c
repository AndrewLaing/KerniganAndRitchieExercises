/* Implement a simple version of the #define processor (i.e., no arguements)
 * suitable for use with C programs, based on the routines of this section. You
 * may also find getch and ungetch helpful.
 *
 * Implemented including the undef() method
 *
 * */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define HASHSIZE 101
#define MAXWORD 100
#define MAXTOKEN 100
#define BUFSIZE 100


struct nlist {      /* table entry: */
    struct nlist *next;   /* next entry in chain */
    char *name;           /* defined name        */
    char *defn;           /* replacement text    */
};


static struct nlist *hashtab[HASHSIZE];  /* pointer table */

struct nlist *lookup(char *);
char *strdup1(char *);

struct nlist *install(char *name, char *defn);

int getch(void);
void ungetch(int c);

void errormessage(void);
void undef(char *name);
char temptoken[MAXTOKEN];

char buf[BUFSIZE];
int bufp = 0;
int flag = 0;


main()
{
    int i;
    char word[MAXWORD];
    char nm[MAXTOKEN];
    char dn[MAXTOKEN];
    char *name=nm;
    char *defn=dn;
    char *temp=temptoken;
    struct nlist *res;

    while((i = getword(word, MAXWORD)) != EOF) 
    {
        if(!flag) 
        {
            if(strcmp(word, "#define")==0)   /* can compare string to char array */
                flag++;
            else if(strcmp(word, "#undef")==0)
                flag=4;
        }
        else if(flag==1) 
        {
            if(isalnum(word[0])) 
            {
                temp = word;
                strcpy(name, temp);
                flag++;
            } 
            else
                errormessage();
        } 
        else if(flag==2) 
        {
            temp = word;
            strcpy(defn, temp);
            flag++;
        } 
        else if(flag==4) 
        {
            undef(word);
            flag = 0;
        }
        
        if(flag==3) 
        {
            install(name, defn);
            flag = 0;
            printf("installed name %s defn %s\n",name,defn);
        }

    }
    
    printf("query here > ");
    
    while((i = getword(word, MAXWORD)) != EOF) 
    {
        res = lookup(word);
        
        if(res==NULL) 
            printf("%s not in lookup\n",word);
        else 
            printf("defn for %s is %s\n",word,res->defn);
        
        printf("\nquery here > ");
    }

    puts(" ");
    return 0;
}

void errormessage(void)
{
    puts("error: invalid data");
    exit(0);
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
    
    if(!isalnum(c) && c!='#') 
    {
        *w = '\0';
        return c;
    }
    
    for( ; --lim > 0; w++)
    {
        if(!isalnum(*w=getch()) && *w!='#') 
        { 
            ungetch(*w);      
            break;
        }
    }
    *w = '\0';
    
    return word[0];
}


/* hash: form hash value for string s (a value between 0 and HASHSIZE) */
unsigned hash(char *s)
{
    unsigned hashval;

    for(hashval =0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;      /* whatever s points to is incremented */
    
    return hashval % HASHSIZE;            /* by (31 * hasval)  */
}


/* lookup: look for s in hashtab */
struct nlist *lookup(char *s)
{
    struct nlist *np;
                         /* iterate through hashtab to s if s is there */
                         /* np->next is the pointer to the next struct */
    for(np = hashtab[hash(s)]; np != NULL; np = np->next)
    {
        if(strcmp(s, np->name)==0)
            return np;   /* found */
    }
    return NULL;         /* not found */
}


/* install: put(name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if((np = lookup(name)) == NULL) { /* not found */
        np = (struct nlist *) malloc(sizeof(*np));
        if(np==NULL || (np->name = strdup1(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } 
    else        /* already there */
        free((void *) np->defn); /* free previous defn */
    
    if((np->defn = strdup1(defn))==NULL)
        return NULL;
    
    return np;
}


void undef(char *name)
{
    struct nlist *np;

    if((np = lookup(name)) == NULL)
        printf("undef error: %s not found in lookup\n",name);
    else 
    {
        np->name = "";
        np->defn = "";
        printf("%s uninstalled from lookup\n",name);
    }
}


/* strdup1: make a duplicate of s */
char *strdup1(char *s) 
{
    char *p;

    p=(char *) malloc(strlen(s)+1); /* +1 for '\0' */
    
    if(p!=NULL)
        strcpy(p, s);
    
    return p;
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
