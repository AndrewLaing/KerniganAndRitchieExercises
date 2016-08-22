#include <stdio.h>

#define IN  1
#define OUT 0

int main()
{
    int c, state;

    state=IN;
    while((c=getchar()) != EOF) 
    {
       if(c=='\t'  && state==IN || c==' ' && state==IN) { 
           putchar('\n');
           state=OUT;              
       }
       else if(c!='\t' && c!=' ') {
           putchar(c);
           state=IN;
       } 
    }
    printf("That was fun.\n");
    return(0);
}
