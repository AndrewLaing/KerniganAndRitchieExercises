#include <stdio.h>

#define MAXLINE 1000

int getline(char line[], int maxline);

int main()
{
    int len;
    char line[MAXLINE];

    while((len = getline(line, MAXLINE)) > 0) 
    {
        if(len>80)
            printf("%d, %s\n",len, line);
        else
            printf("Too short, matey\n");
    }
    
    return(0);
}

int getline(char s[], int lim)
{
    int c, i;

    for(i=0; i<lim-2 && (c=getchar())!=EOF && c!='\n'; ++i)
        s[i]=c;
    
    if(c=='\n') {
        s[i]=c;
        ++i;
    }
    
    s[i]='\0';
    
    return i;
}
