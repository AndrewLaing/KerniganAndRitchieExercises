#include <stdio.h>

int any(char s1[], char s2[]);

int main()
{
    int c, i, n;
    char s1[255];
    char s2[255];
    
    printf("Enter a string >");
    i=0;
    
    while((c=getchar())!=EOF && c!='\n') {
        s1[i]=c;
        ++i;
    }                       
    s1[i]='\0';      // doesn't automatically add '\0'

    n=0;
    printf("Enter characters to find in string >");
    
    while((c=getchar())!=EOF && c!='\n') {
        s2[n]=c;
        ++n;
    }                       
    s2[n]='\0';

    if(i==0) 
        printf("\n<<<Try using data>>>\n");
    else 
    {
        i=any(s1, s2);
        if(i==-1) puts("\nNo search results");
        else printf("any(s1,s2) returned index %d\n",i);
    }
    return(0);
}

int any(char s1[], char s2[])
{
    int a, i;  // outer loop, inner loop
    int best;  // the first location in the string where character encountered

    best = -1;
    for(a = 0; s2[a] != '\0'; a++) 
    {
        for(i = 0; s1[i] != '\0'; i++) 
        {
            if(s1[i] == s2[a]) 
            {
                if(best==-1)
                    best=i;
                else if(i<best) 
                    best=i;
            }
        }
    }
    return best;
}
