#include <stdio.h>

void strcat1(char *s, char *t);

int main()
{
    char n[300]="cute little ";
    char m[]="froggy";
    char o[300]="Another ";

    strcat1(&n[0],&m[0]);
    printf("%s",n);
    puts(" ");

    strcat1(&o[0],&n[0]);
    printf("%s",o);
    puts(" ");
    return(0);
}


/* strcat1: concatenate t to the end of s, s must be big enough */
void strcat1(char *s, char *t)
{
    int i=0;
    int j=0;

    while(s[i]!='\0')      /*find end of s */
        i++;
        
    while(s[i++] = t[j++]) /* copy t */
        ;
}
