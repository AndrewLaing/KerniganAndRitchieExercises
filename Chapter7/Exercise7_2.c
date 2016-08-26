/* Write a program that will print arbitrary input in a sensible way. As a minimum,
 * it should print non-graphic characters in octal or hexdecimal according to
 * local custom, and break long text lines.
 *
 * ./exercise7_2 < someText.txt
 * */

#include <stdio.h>

#define MAXCHAR 80
#define MAXTEMP 21  /* Maximum characters to store in temp */

void charprinter(int i, int j);

int cc;

main()  /* convert declaration to words */
{
    int c, d, st=0, i;
    char temp[MAXTEMP];

    cc = 0;
    while((c = getchar()) != EOF) {
        if(cc<MAXCHAR-20) {
            charprinter(c, 0);
        }
        else if(cc>=MAXCHAR-20 && c==' ' && st>0) 
        {
            for(i=0; i<st; i++) {
                d = temp[i];
                charprinter(d, 1);
            }
            putchar(c);
            cc++;
            st=0;
        }
        else 
        {
            temp[st++] = c;
            cc++;
            if(cc>=MAXCHAR) 
            {
                printf("\n");
                cc=0;
                for(i=0; i<st; i++) {
                    d = temp[i];
                    charprinter(d, 1);
                }
                st=0;
            }
        }
    }
    puts(" ");
    return 0;
}


/* charprinter: to avoid repetition */
void charprinter(int i, int j)
{
    if(i==10) 
    {
        if(!j) {
            printf("\n"); /* print '\n' as normal */
            cc=-1;
        }
        else if(j) {
            printf(" ");
            cc++;
        }
    }
    else if(i<32) 
    {
        printf("[0x%x]",i);
        cc+=6;
    }
    else 
    {
        putchar(i);
        cc++;
    }
}
