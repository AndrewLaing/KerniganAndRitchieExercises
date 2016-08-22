#include <stdio.h>

#define TABSTOP 8

int main()
{
    int c, sc, pos;

    sc = pos = 0;
    while((c=getchar())!=EOF) 
    {
        ++pos;
        if(c==' ') {
            ++sc;
            if(pos-1%TABSTOP==0) {      // last space b4 tabstop
                printf("\t");
                sc=0;
                pos=TABSTOP;
            }
        }
        else if(sc!=0) {
            for( ; sc>0; --sc)
                putchar(' ');
                ++pos;
            putchar(c);
        }
        else if(c=='\t') {
            sc=0;
            pos=TABSTOP;
            putchar(c);
        }
        else putchar(c);
    }
    return(0);
}
