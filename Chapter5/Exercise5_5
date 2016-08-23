#include <stdio.h>

char *strncpy(char s[],char ct[],int n);
char *strncat(char s[], char ct[], int n);
int strncmp(char cs[], char ct[], int n);

int main()
{
    int i;
    
    char s[300]="cute froggy";
    char ct[]="froggy";
    char *sp;
    sp = &s[0];

    *sp = *(strncpy(s,ct,4));

    printf("What a %s",s);
    puts(" ");

    *sp = *(strncat(s,ct,3));

    printf("What a %s",s);
    puts(" ");

    i = strncmp(s,ct,4);
    printf("strcmp returned %d",i);
    puts(" ");
    
    return(0);
}


/* strncpy:  copy n characters of string ct to s and fill the rest with '\0's */
char *strncpy(char s[],char ct[],int n)
{
    int i;
    
    for(i=0; s[i]!='\0'; i++) {
        if(i>=n)
            s[i]='\0';
        else
            s[i]=ct[i];
    }
    
    return &s[0];
}


/* strncat: concatenate n chars of ct to the end of s, s must be big enough */
char *strncat(char s[], char ct[], int n)
{
    int i=0;
    int j;

    while(s[i]!='\0')      /*find end of s */
        i++;
        
    for(j=0 ; j<n ; i++, j++)
        s[i]=ct[j];
    s[i]= '\0';
    
    return &s[0];
}


/* strncmp: compare n chars at the beginning of ct with n at the beginning of cs
 * return 0 if cs<ct, 0 if cs==ct or >0 if cs>ct */
int strncmp(char cs[], char ct[], int n)
{
    int i;

    for(i=0; cs[i] == ct[i]; i++)   
        if(i==n-1)        /* n-1 because count starts at zero */  
            return 0;
            
    return cs[i] - ct[i];
}
