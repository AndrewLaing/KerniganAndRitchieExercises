#include <stdio.h>

int strlen(char *s);
int strend(char s[], char t[]);

int main()
{
    int i;
    
    char s[300]="cute froggy";
    char t[]="froggy";
    i = strend(s, t);
    
    if(i == 1)
        printf("'%s' appears at the end of '%s'",t,s);
    else
        printf("'%s' doesnt appear at the end of '%s'",t,s);
        
    puts(" ");
    
    return(0);
}


/* strlen: return length of the char array that '*s' points to */
int strlen(char *s)
{
    char *p = s;

    while(*p != '\0')
        p++;
        
    return p-s; 
}


/* strcmp: compare the arrays that *s and *t point to
 * return 1 if they match and 0 if they don't */
int strcmp(char *s, char *t)
{
    int i;

    for( ; *s == *t; s++, t++)
        if(*s =='\0')
            return 1;

    return 0;
}


/* strend: return 1 if "char t" is at the end of "char s" 0 if not */
int strend(char s[], char t[])
{
    int i, j;
    
    i = strlen(&s[0]);
    j = strlen(&t[0]);
    i = i-j;
    j = strcmp(&s[i],&t[0]);
    
    return j;
}
