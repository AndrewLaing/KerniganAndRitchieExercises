/* Write the program tail, which prints the last n lines of its input. By default,
 * n is set to 10, let us say, but it can be changed by an optional arguement
 * so that
 *     tail -n
 * prints the last n lines. The program should behave rationally no matter how
 * unreasonable the input or the value of n. Write the program so that is makes
 * the best use of available storage; lines should be stored as in the sorting
 * program of section 5.6, not in a two-dimensional array of fixed size.
 */

#include <stdio.h>
#include <string.h>

#define MAXTAIL 100
#define MAXLINES 1000
#define MAXLEN 1000               /* max length of any input line */
#define TAB 8
#define ALLOCSIZE 10000           /* size of available space */

static char allocbuf[ALLOCSIZE];  /* storage of alloc   */
static char *allocp = allocbuf;   /* next free position */
char *lineptr[MAXLINES];          /* pointers to textlines */

void errormessage(void);
int readlines(char *lineptr[], int maxlines, int tailsize);
int getline(char *s, int lim);
char *alloc(int n);
void tailprint(int nlines, int tailsize);

main(int argc, char *argv[])
{
    int c, j=0, origargc=argc;
    int nflagged=0;
    int tailsize=10;

    if(argc>3 || argc==2) 
    {
        errormessage();
        return 0;
    }
    
    while(--argc>0) 
    {
        if((*++argv)[0] == '-') 
        {
          while(c = *++argv[0])
          {
            switch(c) 
            {
              case 'n':
                nflagged++;
                break;
              default:
                errormessage();
                return 0;
            }
            c = *++argv[0];
            
            if(nflagged==1) 
            {
              if(isdigit(**argv)) 
              {
                while(isdigit(**argv)) 
                {
                  j = (j*10)+(**argv-'0');
                  (argv[0]++);
                }
                
                c = *argv[0];
                
                if(c!=0) 
                {
                  errormessage();
                  return 0;
                }
              }
              else 
              {
                errormessage();
                return 0;
              }
            }
            else if(isdigit(**argv)) 
            {
              errormessage();
              return 0;
            }
            
            if(nflagged==1) 
            {
              nflagged++;
              tailsize=j;
            }

            j=0;
        }
    }
    
    if(tailsize>MAXTAIL) 
    {
      printf("Maximum value of n is %d\n",MAXTAIL);
      return 0;
    }
    else
      j = readlines(lineptr,MAXLINES,tailsize);
        
    if(j==-1) 
    {
      puts("Maximum number of lines exceeded"); /* or just print last n lines */
      tailprint(j,tailsize);
    }
    else 
      tailprint(j,tailsize);
    
    return 0;
}


/* alloc: return pointer to n characters */
char *alloc(int n)
{
    if(allocbuf + ALLOCSIZE - allocp >= n) 
    {
        allocp += n;
        return allocp - n;
    }
    else 
      return 0;
}


int readlines(char *lineptr[], int maxlines, int tailsize)
{
    int len, nlines, i;
    char *p, line[MAXLEN];   // atm not pointing to anything
    
    nlines = 0;
    while((len=getline(line,MAXLEN))>0) 
    {
        if(nlines >= maxlines || (p = alloc(len+1)) == NULL)
            return -1;
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

    for(i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i) {
        s[i]=c;
    }
    s[i]='\0';
    
    return i;
}


/* errormessage: print an error message */ 
void errormessage(void)
{
    puts("Usage: tail [-n lines_to_print]");
}


/* tailprint: print the last tailsize lines entered */
void tailprint(int nlines, int tailsize)
{
    int i;

    printf("-------- Last %d lines --------\n",tailsize);
    
    if(tailsize>=nlines)
    {
        for(i=0; i<nlines; i++)
            printf("%s\n",lineptr[i]);
    }
    else
    {
        for(i=nlines-tailsize; i<nlines; i++)
            printf("%s\n",lineptr[i]);
    }
}
