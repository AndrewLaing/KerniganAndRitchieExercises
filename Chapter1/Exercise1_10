#include <stdio.h>

int main()
{
    int c;

    while((c=getchar()) != EOF) {         // Remember curly braces
       if(c=='\t') {                      // for 'while' loops
           putchar('\\');                
           putchar('t');
       }
       else if(c=='\b') {                 // OS doesn't intercept /b
           putchar('\\');
           putchar('b');
       }
       else if(c=='\\') {
           putchar('\\');                 // putchar() puts one character
           putchar('\\');                 // at a time so do it twice
       }
       else
           putchar(c); 
    } 
    printf("That was fun.\n");
    return(0);
}
