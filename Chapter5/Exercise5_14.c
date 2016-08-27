/* Modify the sorting program to handle an -r flag, which indicates sorting in
 * reverse (decreasing) order. Be sure that -r works with -n.
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

/* renamed because qsort() in stdlib.h */
void qsort1(void *lineptr[], int left, int right, int reverse,
           int (*comp)(void *, void*));      /* a pointer to a function that returns
                                                an integer and two pointers as args. */
int numcmp(char *, char *);

/* renamed because strcmp() in stdlib.h */
int strcmp1(char *s, char *t);
void swap(void *v[], int, int);


/* sort input lines */
main(int argc, char *argv[])
{
    int nlines;       /* number of input lines read */
    int numeric = 0;  /* 1 if numeric sort */
    int reverse = 0;  /* 1 if reverse sort */

    if(argc > 1 && strcmp1(argv[1], "-n") == 0) 
        numeric = 1;
    else if(argc > 1 && strcmp1(argv[1], "-r") == 0)
        reverse = 1;
        
    if(argc > 2 && strcmp1(argv[2], "-n") == 0)
        numeric = 1;
    else if(argc > 2 && strcmp1(argv[2], "-r") == 0)
        reverse = 1;
        
    if((nlines = readlines(lineptr, MAXLINES)) >= 0) 
    {
        qsort1((void**) lineptr, 0, nlines-1, reverse,
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
    if(allocbuf + ALLOCSIZE - allocp >= n) 
    {
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
void qsort1(void *v[], int left, int right, int reverse,
           int (*comp)(void *, void *))
{
    int i, last;
    
    if(reverse==0) 
    {
        if(left >= right)  /* do nothing if array contains */
            return;        /* fewer than two elements */
        
        swap(v, left, (left + right)/2);
        last = left;
        
        for(i=left+1; i<=right; i++)
            if((*comp)(v[i], v[left])<0)    /* pointer to function and args */
                swap(v, ++last, i);
        
        swap(v,left,last);
        qsort1(v, left, last-1, reverse, comp);
        qsort1(v, last+1, right, reverse, comp);
    }
    
    if(reverse==1) 
    {
        if(left >= right)  /* do nothing if array contains */
            return;        /* fewer than two elements */
            
        swap(v, left, (left + right)/2);
        last = left;
        
        for(i=left+1; i<=right; i++)
            if((*comp)(v[i], v[left])>0)    /* pointer to function and args */
                swap(v, ++last, i);
        
        swap(v,left,last);
        qsort1(v, left, last-1, reverse, comp);
        qsort1(v, last+1, right, reverse, comp);
    }
}


/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2)
{
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);
    
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
    int i;

    for(i=0; s[i] == t[i]; i++)    /* iterate until a difference found */
        if(s[i]=='\0')             /* no differences found */
            return 0;
    
    return s[i] - t[i];            /* Ascii arithmetic l-r==-6 */
}


void swap(void *v[], int i, int j)
{
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
