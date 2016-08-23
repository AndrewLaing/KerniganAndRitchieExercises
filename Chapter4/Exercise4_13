#include <stdio.h>
#include <string.h>

void reverse(char s[]);

int main()
{
    int i, c;
    char s[255];
    
    printf("Enter a string >");
    
    i=0;
    
    while((c=getchar())!='\n') {
        s[i]=c;
        ++i;
    }                       
    s[i]='\0';

    reverse(s);
    for(i=0; i<strlen(s); i++)
        printf("%c",s[i]);
        
    puts(" ");
    
    return(0);
}


void reverse(char s[])
{
    static int i=0;
    char temp[2];

    int SLEN = strlen(s);
    int first=i;
    int last=SLEN-i-1;
    
    if(last<=first)
        return;

    temp[0] = s[first];
    s[first] = s[last];
    s[last] = temp[0];
    i++;
    reverse(s);
    s[SLEN] = '\0';
}
