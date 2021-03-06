/* Add a field-searching capability, so sorting may be done on fields within
 * lines, each field sorted according to an independent set of options. (The
 * index for this book was sorted with -df for the index category and -n for
 * the page numbers.)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINES 5000            /* max #lines to be sorted */
#define MAXLEN 1000
#define ALLOCSIZE 10000          /* size of available space */

static char allocbuf[ALLOCSIZE]; /* storage of alloc   */
static char *allocp = allocbuf;  /* next free position */

char *lineptr[MAXLINES];         /* pointers to text lines */

char *alloc(int n);
int readlines(char *lineptr[], int nlines);
int getline(char *s, int lim);
void writelines(char *lineptr[], int nlines);

/* qsort() renamed because qsort() in stdlib.h */
void qsort1(void *lineptr[], int left, int right,
           int (*comp)(void *, void*));      /* a pointer to a function that returns
                                                an integer and two pointers as args. */

double atodouble(char *s1);
double atodouble1(char *s1);
int numcmp(char *, char *);
int strcmp1(char *s, char *t);               /* renamed because strcmp() in stdlib.h */
void swap(void *v[], int, int);
void errormessage(void);

static int numeric = 0;  /* 1 if numeric sort */
static int reverse = 0;  /* 1 if reverse sort */
static int fold = 0;
static int dirorder = 0;
static int search = 0;
static int searchint = 0;

/* sort input lines */
main(int argc, char *argv[])
{
    int nlines, c, count=0;       /* number of input lines read */
    while(--argc>0) 
    {
        if((*++argv)[0] == '-') 
        {
            c = *++argv[0];
            while(c = *argv[0]) 
            {
                switch(c) {
                  case 'n':
                      numeric++;
                      break;
                  case 'r':
                      reverse++;
                      break;
                  case 'f':
                      fold++;
                      break;
                  case 'd':
                      dirorder++;
                      break;
                  case 's':
                      search++;
                      break;
                  default:
                      errormessage();
                      return 0;
                }
                
                c = *++argv[0];
            }
        }
        
        c = *++argv[0];
        
        if(isdigit(c)) 
        {
            if(search) 
            {
                while(isdigit(**argv)) 
                {
                    searchint = (searchint*10)+(**argv-'0');
                    (argv[0]++);
                }
            }
        }
    }
    
    if((nlines = readlines(lineptr, MAXLINES)) >= 0) 
    {
        qsort1((void**) lineptr, 0, nlines-1,
          (int (*)(void *,void *))(numeric ? numcmp : strcmp1)); /* pointer to function that returns
                                                                  an integer with two pointers as args */ 
        writelines(lineptr,nlines);
        
        return 0;
    }
    else 
    {
        printf("input too big to sort\n");
        return 1;
    }
}


/* alloc: return pointer to n characters */
char *alloc(int n)
{
    if(allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return allocp - n;
    }
    else return 0;
}


/* readline: read input lines */
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    
    while((len=getline(line, MAXLEN))>0)
    {
        if(nlines >= maxlines || (p = alloc(len+1)) == NULL)  /* len+1 to allocate next free */
            return -1;                                        /* space after '\0' */
        else 
        {
            line[len]='\0'; /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }

    return nlines;
}


/* getline: get a line of input into an array */
int getline(char *s, int lim)
{
    int c, i;

    for(i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
        s[i]=c;
    s[i]='\0';

    return i;
}


/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
    int i;
    
    puts("---- Sorted words ----");
    while(nlines-- > 0)
        printf("%s\n", *lineptr++);
}


/* qsort: sort v[left]...v[right] into increasing order */
void qsort1(void *v[], int left, int right,
           int (*comp)(void *, void *))
{
    int i, last;
    if(!reverse) 
    {
        if(left >= right)  /* do nothing if array contains */
            return;        /* fewer than two elements */
            
        swap(v, left, (left + right)/2);
        last = left;
        
        for(i=left+1; i<=right; i++)
            if((*comp)(v[i], v[left])<0)    /* pointer to function and args */
                swap(v, ++last, i);
        
        swap(v,left,last);
        qsort1(v, left, last-1, comp);
        qsort1(v, last+1, right, comp);
    }
    else 
    {
        if(left >= right)  /* do nothing if array contains */
            return;        /* fewer than two elements */
        
        swap(v, left, (left + right)/2);
        last = left;
        
        for(i=left+1; i<=right; i++)
            if((*comp)(v[i], v[left])>0)    /* pointer to function and args */
                swap(v, ++last, i);
        
        swap(v,left,last);
        qsort1(v, left, last-1, comp);
        qsort1(v, last+1, right, comp);
    }
}


/* atodouble: convert ascii to double */
double atodouble(char *s1)
{
    int i=0;
    double v1=0; /* always initialize counting variables to 0 */
    
    while(isdigit(s1[i]))
        v1 = (v1*10)+(s1[i++]-'0');
    
    return v1;
}


/* atodouble1: convert ascii to double after skipping n tabs */ 
double atodouble1(char *s1)
{
    int i=0, scount=0;
    double v1=0;

    while(scount<searchint) 
    {
        for(; s1[i]!='\t' && isdigit(s1[i]); i++)
            if(s1[i]=='\0') errormessage();
        
        if(s1[i]=='\t') 
            i++;
        
        scount++;
    }
    
    if(!isdigit(s1[i])) 
        errormessage();
    
    while(isdigit(s1[i]))
        v1 = (v1*10)+(s1[i++]-'0');
    
    return v1;
}


/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2)
{
    double v1, v2;

    if(search) 
    {
        v1 = atodouble1(s1);
        v2 = atodouble1(s2);
    }
    else 
    {
        v1 = atodouble(s1);
        v2 = atodouble(s2);
    }
    
    if(v1<v2)
        return -1;
    else if(v1>v2)
        return 1;
    else
        return 0;
}


/* strcmp: return <0 if s<t, O if s==t, >0 if s>t */
int strcmp1(char *s, char *t)
{
    int i=0, j=0, scount=0, tcount=0, tabcount=0;

    /* run the search subroutine */
    if(search) 
    {
        while(scount<searchint) 
        {
            for(; s[i]!='\t'; i++)
                if(s[i]=='\0') 
                    errormessage();
            
            if(s[i]=='\t') 
                i++;
            
            scount++;
        }
        
        while(tcount<searchint) 
        {
            for(; t[j]!='\t'; j++)
                if(t[j]=='\0') errormessage();
            
            if(t[j]=='\t') 
                j++;
            
            tcount++;
        }
    }

    for(; ; i++, j++) {     /* iterate until a difference found */
        if(s[i]=='\0') 
            return 0;
        
        if(dirorder) 
        {
            while(1) 
            {
                if(isalnum(s[i]) || s[i]==' ') 
                    break;
                
                i++;
                
                if(s[i]=='\0') 
                    return 0;
            }
            while(1) 
            {
                if(isalnum(t[j]) || t[j]==' ') 
                    break;
                
                j++;
                
                if(t[j]=='\0') 
                    return 0;
            }
        }
        
        if(!fold) 
        {
            if(s[i]!=t[j])
                return s[i] - t[j];
        }
        else 
        {
            if(tolower(s[i]) != tolower(t[j]))
                return tolower(s[i]) - tolower(t[j]);
        }
    }
}


void swap(void *v[], int i, int j)
{
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}


/* errormessage: print an error message */ 
void errormessage(void)
{
    puts("Usage: sorted [-n :numeric][-r :reverse][-f :fold][-d :directory_order][-s int :search]");
    exit(-1);
}
