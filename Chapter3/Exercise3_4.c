#include <stdio.h>
#include <string.h>

void itoa(int n, char s[]);
void reverse(char s[]);

int main()
{
    int n;
    char s[244];
    
    printf("Enter the integer :");
    scanf("%d",&n);

    itoa(n,s);
    
    return(0);
}


/* Convert an integer into a character string (reversed eg 987 == '789') */
void itoa(int n, char s[])
{
    int i, sign;    
    int LNN = 0;  /* Largest negative number or less */

    if((sign=n)<0)
        n = -n;
        
    if(n<0) 
    {
        n = -(n+1); /* otherwise is larger than largest positive number */
        LNN=1;
    }
    
    i=0;
    do { 
        if(LNN && i==0) s[i++] = n % 10 + '0' + 1;  /* correct if LNN */
        else s[i++] = n % 10 + '0';  
    } while((n/=10)>0);
    
    if(sign<0)
        s[i++]='-';
    
    s[i] = '\0';

    reverse(s);
}


/* reverse: reverse string s in place */
void reverse(char s[])
{
    int c, i, j;

    for(i=0, j = strlen(s)-1; i<j; i++, j--) 
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
    
    puts("\nReversed");
    
    for(i=0; i<strlen(s); i++)
        printf("%c",s[i]);
    
    puts(" ");
}
