#include <stdio.h>

#define MAXLINE 1000

int getline(char line[], int maxline);
void reverse(char line[]);

int main()
{
    int len, i;
    char line[MAXLINE];

    for(i=0; i<=MAXLINE; ++i)
        line[i]='\0';
        
    while(gets(line)) {               // EOF returns 0
        reverse(line);
        for(i=0; i<=MAXLINE; ++i)
            line[i]='\0';
    }
    return(0);
}


void reverse(char s[])
{
    int i, j;

    for(i=0; i<MAXLINE-2 && s[i]!='\0'; ++i)
        ;                             // Just count length of s

    for(j=i-1; j>=0; --j)             // Then print backwards
        printf("%c",s[j]);

    printf("\n");
}
