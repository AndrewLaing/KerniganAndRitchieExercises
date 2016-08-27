#include <stdio.h>

void squeeze(char s1[], char s2[]);

int main()
{
    int c, i, n;
    char s1[255];
    char s2[255];
    
    printf("Enter a string >");
    i=0;
    
    while((c=getchar())!=EOF && c!='\n') 
    {
        s1[i]=c;
        ++i;
    }
    
    s1[i]='\0';

    n=0;
    printf("Enter char to exclude >");
    
    while((c=getchar())!=EOF && c!='\n') 
    {
        s2[n]=c;
        ++n;
    }                       
    
    s2[n]='\0';
    if(i==0) printf("\n<<<Try using data>>>\n");
    else squeeze(s1, s2);
    
    return(0);
}

void squeeze(char s1[], char s2[])
{
    int a;    // outer loop
    int i, j; // inner loop

    for(a = 0; s2[a] != '\0'; a++) 
    {
        for(i = j = 0; s1[i] != '\0'; i++) 
        {
            if(s1[i] != s2[a])
                s1[j++] = s1[i];
        }
        s1[j] = '\0';
    }
    
    for(i = j = 0; s1[i] != '\0'; i++)
        printf("%c",s1[i]);
    
    puts("\nValidated");
}
