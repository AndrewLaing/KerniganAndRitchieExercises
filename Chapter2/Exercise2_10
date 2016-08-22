#include <stdio.h>

int lower(int c); 

int main()
{
    int i, c;

    printf("Enter characters >");
    
    while((c=getchar())!=EOF && c!='\n') 
    {
        i = lower(c);
        printf("%c",i);
    }                       
    puts(" ");
    
    return(0);
}


/* lower: convert c to lower case; ASCII only */
int lower(int c)
{
    c = (c>='A' && c<='Z') ? (c+'a'-'A') : c;
    return c;
}
