/* Write a program that converts upper-case to lower or lower-case to upper,
 * depending upon the name it is invoked with, as found in argv[0]
*/

#include <stdio.h>
#include <ctype.h>   /* for tolower() toupper() */
#include <string.h>  /* for strcmp() */

void errormessage(void);
void utol(void);
void ltou(void);


main(int argc, char *argv[])
{
    if(argc > 1 && argc < 3) 
    {
        if(strcmp(argv[1], "upper") == 0)
            ltou();
        else if(strcmp(argv[1], "lower") == 0)
            utol();
        else
            errormessage();
    } 
    else
        errormessage();
}


/* errormessage: print usage message */
void errormessage(void)
{
    puts("usage: exercise7_1 [ upper | lower ]");
}


/* utol: uppercase to lowercase */
void utol(void)
{
    int c;

    while((c = getchar()) != EOF)
        putchar(tolower(c));
}


/* ltou: lowercase to uppercase */
void ltou(void)
{
    int c;

    while((c = getchar()) != EOF)
        putchar(toupper(c));
}
