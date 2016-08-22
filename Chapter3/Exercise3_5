#include <stdio.h>
#include <string.h>

void itob(int n, char s[], int b);
void reverse(char s[]);

int main()
{
    int n, b;
    char s[255];

    printf("Enter the integer     :");
    scanf("%d",&n);
    
    printf("Enter the base number :");
    scanf("%d",&b);
    
    if(b>36) puts("I can only do up to base 36");
    else itob(n,s,b);
    
    return(0);
}


void itob(int n, char s[], int b)
{
    int index, remainder;
    char nstr[] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f','g',
                   'h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x',
                   'y','z'};

    remainder = 0;
    index     = 0 ;
    
    while ( n != 0 )
    {
        remainder = n % b ;  // assume K > 1
        n         = n / b ;  // integer division
        s[index] = nstr[remainder];
        index ++ ;
    }
    s[index] = '\0';
    
    reverse(s);
}


void reverse(char s[])
{
    int c, i, j;

    for(i=0, j = strlen(s)-1; i<j; i++, j--) 
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
    
    puts("\nReversed i.e., 'correct way round'");
    
    for(i=0; i<strlen(s); i++)
        printf("%c",s[i]);
    
    puts(" ");
}
