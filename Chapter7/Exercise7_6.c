/* Write a program to compare two files, printing the first line where they differ
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXCHAR 100

int filecmp1(FILE *iop, FILE *iop1);
char *fgets1(char *s, int n, FILE *iop);
int fputs1(char *s, FILE *iop);
int strcmp1(char *s, char *t);

/* compare the lines of two files if a difference is found output the line and quit */
main(int argc, char *argv[])
{
    FILE *fp;
    FILE *fp1;

    char *prog = argv[0];
    int ret=0;

    if(argc <= 2) {
        fprintf(stderr, "%s: not enough args\n", prog);
        exit(2);
    } 
    else if(argc == 3) 
    {
        if((fp = fopen(*++argv, "r")) == NULL) {   /* first open the FILE object */
            fprintf(stderr, "%s: can't open %s\n", prog, *argv);
            exit(1);
        } else if((fp1 = fopen(*++argv, "r")) == NULL) { /* open the next FILE object */
            fprintf(stderr, "%s: can't open %s\n", prog, *argv);
            exit(1);
        } else {
            ret = filecmp1(fp,fp1);
        } 
    }
}


/* filecmp1: compare the lines of two files if a difference is found
 *           output the line and quit */
int filecmp1(FILE *iop, FILE *iop1)
{
    int ret=0, lineno=0;

    char lineA[MAXCHAR];
    char lineB[MAXCHAR];

    while(fgets1(lineA, MAXCHAR, iop)) 
    { 
        fgets1(lineB, MAXCHAR, iop1);
        ret = strcmp1(lineA, lineB);
        lineno+=1;
        if(ret!=0) {
            printf("line %d: %s",lineno, lineB);
            break;
        }
    } 
    
    if(ret==0) 
    {
        if(fgets1(lineB, MAXCHAR, iop1)) {
            puts("Note: file2 is longer than file1!");
        } 
        puts("The lines in file2 match those in file1");
    } 
    return ret;
}


/* fgets1: get at most n chars from iop */
char *fgets1(char *s, int n, FILE *iop)
{
    register int c;
    register char *cs;

    cs = s;
    while(--n > 0 && (c = getc(iop)) != EOF)   /* get up to n characters from one line of iop */
        if((*cs++ = c) == '\n')                /* quit at '\n' cs is at the same address as s  */
            break;
    *cs = '\0';
    
    return (c == EOF && cs == s) ? NULL : s;   /* ternary operation */
}


/* fputs1: put string s on file iop */
int fputs1(char *s, FILE *iop)
{
    int c;

    while(c = *s++)
        putc(c, iop);
        
    return ferror(iop) ? EOF : 0;
}


/* strcmp1: return <0 if s<t, O if s==t, >0 if s>t */
int strcmp1(char *s, char *t)
{
    int i;

    for( ; *s == *t; s++, t++) 
        if(*s =='\0') 
            return 0;
            
    return *s - *t;
}
