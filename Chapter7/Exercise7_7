/* Modify the pattern finding program of Chapter 5 to take its input from a set
of named files or, if no files are named as arguements, from the standard input.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 100
#define MAXCHAR 100

int getline(char *line, int max);
char *fgets1(char *s, int n, FILE *iop);


main(int argc, char *argv[]) /* argv[n] doesnt overflow tried with a 1,000,000 char arg */
{
    char line[MAXLINE];
    char *prog = argv[0];
    char *pattern;
    FILE *fp;
    long lineno = 0;
    int c, except = 0, number = 0, found = 0, fninfo = 0;
    /* fninfo is a flag to show whether or not to print the filename  */
    /* found is the number of matches found */
    
    while(--argc > 0 && (*++argv)[0] == '-')
    {
        while(c = *++argv[0])
        {
            switch(c) 
            {
              case '-':  /* Because some people are used to '--flag' */
                  break;
              case 'x':
                  except = 1;
                  break;
              case 'n':
                  number = 1;
                  break;
              case 'i':
                  fninfo = 1;
                  break;
              case 'h':
                  puts("Usage: find [-xinh] <PATTERN> [FILE1 FILE2 ...]");
                  puts("Search for PATTERN in each FILE or standard input.");
                  puts("Example: find -inx frog frog.txt elephant.txt cheese.txt\n");
                  puts("Options:");
                  puts("       -x  lines without match");
                  puts("       -i  include filename");
                  puts("       -n  include line number");
                  puts("       -h  print this help menu\n");
                  puts("Report bugs to <lolamontes69@gmail.com>.");
                  exit(0);
              default:
                  printf("find: illegal option %c\n", c);
                  argc = 0;
                  found = -1;
                  break;
            }
        }
    }
    if(argc < 1)
        printf("Usage: find [-xinh] <pattern> [file1 file2 ...]\n");
    else if(argc == 1) 
    {
        pattern = *argv;
        while(getline1(line, MAXLINE) > 0) 
        {
            lineno++;
            if((strstr(line, pattern) != NULL) != except) 
            {
                if(number)
                    printf("%ld:",lineno);
                printf("%s",line);
                found++;
            }
        }
    }
    else 
    {
        pattern = *argv++;      /* pattern is the pattern to match */
        for( ; argc>1; argc--) 
        {
            if((fp = fopen(*argv, "r")) == NULL) {   /* first open the FILE object */
                fprintf(stderr, "%s: can't open %s\n", prog, *argv);
                exit(1);
            } 
            else 
            {
                // fprintf(stderr, "%s: Examining %s\n", prog, *argv);
                lineno=0; /* initialize for each file */
                found = 0;
                while(fgets1(line, MAXCHAR, fp)) 
                {
                    lineno++;
                    if((strstr(line, pattern) != NULL) != except) 
                    {
                        if(fninfo)
                            printf("%s: ",*argv);
                        
                        if(number)
                            printf("line %ld:",lineno);
                        
                        printf("%s",line);
                        found++;
                    }
                }
                
                fclose(fp);
                
                if(found==0 && fninfo) 
                    fprintf(stderr, "%s: No matches found\n", *argv);
            } 
            ++argv;
        }
    }
    exit(0);
}


/* getline: read a line, return length */
int getline1(char *line, int max)
{
    if(fgets1(line, max, stdin) == NULL)  /* fgets gets a line of input        */
        return 0;                         /* getline is prolly similar to gets */
    else
        return strlen(line);
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
