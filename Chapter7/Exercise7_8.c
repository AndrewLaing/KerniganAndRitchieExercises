/* Write a program to print a set of files, starting each new one on a new page,
 * with a title and a running page count for each file *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 100
#define MAXCHAR 100

void printpageheader(char *line, FILE *iop);
char *fgets1(char *s, int n, FILE *iop);
int fputs1(char *s, FILE *iop);

main(int argc, char *argv[]) /* argv[n] doesnt overflow */
{
    char line[MAXLINE];
    char *prog = argv[0];
    char *filename;
    FILE *fp;
    FILE *fp1;
    int c, screen = 0, pagenumber = 0, filewrite = 0, linenum = 5;
    /* screen is to print to stdout */
    while(--argc > 0 && (*++argv)[0] == '-')
    {
        while(c = *++argv[0])
        {
            switch(c) 
            {
              case 's':
                  screen = 1;
                  break;
              case 'w':
                  filewrite = 1;
                  break;
              case 'h':
                  puts("Usage   : fileutil1 -s|w|h file1 file2 ...\n");
                  puts("Examples: fileutil1 -w Output.txt Input1.txt Input2.txt");
                  puts("          fileutil1 -s Input1.txt Input2.txt");
                  puts("Options :");
                  puts("      -s  print files to stdout");
                  puts("      -w  print files to outputfile");
                  puts("      -h  print this help menu\n");
                  puts("Report bugs to <lolamontes69@gmail.com>.");
                  exit(0);
              default:
                  printf("fileutil1: illegal option %c\n", c);
                  argc = 0;
                  break;
            }
        }
    }
    
    if(argc < 1 || (!filewrite && !screen)) 
    {
        puts("Usage: fileutil1 -s|w|h file1 file2 ...\n");
        exit(0);
    } 
    else if(argc==1) 
    {
            if(screen) 
            {
                if((fp = fopen(*argv, "r")) == NULL) {   /* first open the FILE object */
                    fprintf(stderr, "%s: can't open %s\n", prog, *argv);
                    exit(1);
                } 
                else fp1 = stdout;
            } 
            else 
            {
                fp = stdin;
                fp1 = fopen(*argv, "w");
            }
            
            filename = *argv;
            pagenumber += 1;
            sprintf(line,"## File: %-60spage %3d ##\n",filename,pagenumber);
            printpageheader(line, fp1);
            
            while(fgets1(line, MAXCHAR, fp)) 
            {
                fputs1(line, fp1);
                linenum +=1;
                if(linenum==24) 
                {
                    pagenumber+=1;
                    sprintf(line,"## File: %-60spage %3d ##\n",filename,pagenumber);
                    printpageheader(line, fp1);
                    linenum=0;
                }
            }
            puts(" ");
            exit(0); 
        
    } 
    else if(argc>1) 
    {
        if(screen)
            fp1 = stdout;
        else 
        {
            fp1 = fopen(*argv++, "w");
            argc--;
        }
        
        for( ; argc>0; argc--) 
        {
            linenum = 5;
            pagenumber += 1;
            
            if((fp = fopen(*argv, "r")) == NULL) 
            {  
                fprintf(stderr, "%s: can't open %s\n", prog, *argv);
                exit(1);
            } 
            else 
            {
                filename = *argv;
                sprintf(line,"## File: %-60spage %3d ##\n",filename,pagenumber);
                printpageheader(line, fp1);
                
                while(fgets1(line, MAXCHAR, fp)) 
                {
                    fputs1(line, fp1);
                    linenum +=1;
                    if(linenum==30) 
                    {
                        pagenumber+=1;
                        sprintf(line,"## File: %-60spage %3d ##\n",filename,pagenumber);
                        printpageheader(line, fp1);
                        linenum=5;
                    }
                }
            }
            for( ; linenum<=30; linenum++)
                fputs1("\n", fp1);
            *argv++;
        }
        fclose(fp1);
    }
    puts(" ");
    exit(0);
}


/* printpageheader: print title and page number at top of each page */
void printpageheader(char *line, FILE *iop)
{
    fputs1("################################################################################\n",iop);
    fputs1(line,iop);
    fputs1("################################################################################\n\n",iop);
}

/* fgets1: get at most n chars from iop */
char *fgets1(char *s, int n, FILE *iop)
{
    register int c;
    register char *cs;

    cs = s;
    while(--n > 0 && (c = getc(iop)) != EOF)
    {
        if((*cs++ = c) == '\n')
            break;
    }
    *cs = '\0';
    
    return (c == EOF && cs == s) ? NULL : s; 
}


/* fputs1: put string s on file iop */
int fputs1(char *s, FILE *iop)
{
    int c;

    while(c = *s++)
        putc(c, iop);
        
    return ferror(iop) ? EOF : 0;
}
