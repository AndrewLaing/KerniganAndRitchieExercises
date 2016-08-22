#include <stdio.h>

#define ACL 30
#define IN 1
#define OUT 0 
#define TAB 8

int main()
{
    int c, i, j, d, lc;           // d=wordcount, lc=letter count

    char word[ACL];

    d=0;
    lc=0;                         // Always initialize numeric variables
    while((c=getchar())!=EOF) {

        if((lc>=ACL && c==' ') || (lc>=ACL && c=='\n')) 
        {
            printf("(Exceeded Allowed Max-word-length %d)\n", ACL);
            lc=0;
            d=0;
        }

        if(d > ACL) {             // puts a new line when ACL reached
            printf("\n");         // if still in word the word keeps getting
            d=0;                  // added to word
        }

        if(c==' ' || c=='\n') {
            for(i=0; i<lc; ++i)
                printf("%c",word[i]);
            if(d<ACL)
                putchar(c);
            lc=0;
        }

        else if(c=='\t') {
            for(i=0; i<lc; ++i)
                printf("%c",word[i]);
            lc=0;
            if(d+(d%TAB)>ACL) {
                printf("\n");
                d=0;
            }
            else {
                for(j=0; j<=d%TAB; ++j) {
                    printf(" ");
                    ++d;
                }
            }
        }

        else {
            word[lc]=c;
            ++lc;
        }

        if(c=='\n') d=0;          // reset d after newline
        else if(c=='\t')          // d already calculated
            ;
        else ++d;
    }
    printf("\nlc=%d",lc);
    return(0);
}
