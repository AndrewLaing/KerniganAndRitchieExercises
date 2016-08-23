#include <stdio.h>
#include <string.h>

void itoa(int n, char s[]);
void reverse(char s[]);

int main()
{
    int i, n;
    char s[]="0";
    
    printf("Enter the integer :");
    scanf("%d",&n);

    itoa(n,s);

    puts("Has rezuhlt...");
    
    for(i=0; i<strlen(s); i++)
        printf("%c",s[i]);
    
    puts(" ");
    
    return(0);
}


/* Convert an integer into a character string using recursion */
void itoa(int n, char s[])
{
    static int i=0; /* use static variable for keeping count of position in string
                     * this keeps its value through recursive calls to the function */
    if(n<0) 
    {
        n = -n;
        s[i++]='-';
    }
    
    if(n/10)
        itoa(n/10,s);
    s[i++] = (n % 10 + '0');
    s[i]   = '\0';
}
