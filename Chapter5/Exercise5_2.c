#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100

int getfloat(float *pn);
int getch(void);
void ungetch(int);

char buf[BUFSIZE];
int bufp = 0;

main()
{
    float i = 29;
    int j;
    float *pn;
    
    pn = &i;
    printf("Original i = %f\n",i);

    j = getfloat(pn);
    
    if(j!=0)
        printf("i is now   = %f\n",i);
    
    /* Verify putting into buf */
    i = getch();
    
    if(bufp>0) 
    {
        puts("Print contents of buffer");
    
        while(bufp >= 0) 
        {
            i = buf[bufp--];
            printf("i = %c\n",i);
        }
    }
    return(0);
}


/* getint: get next integer from input into *pn */
int getfloat(float *pn)
{
    int c, sign;
    float f;
    
    while(isspace(c = getch()))
        ;
        
    if(!isdigit(c) && c != EOF && c!='+' && c!= '-') 
    {
        ungetch(c);
        return 0;
    }
    sign = (c == '-') ? -1 : 1;
    
    if(c=='+' || c=='-')
        c = getch();
        
    if(!isdigit(c)) 
    {
        (sign < 0) ? ungetch('-'): ungetch('+');
        ungetch(c);
        return 0;
    }
    
    for(*pn = 0; isdigit(c); c=getch())
        *pn = 10 * *pn + (c-'0');
    *pn *= sign;
    
    /* Add the float part to the number */
    if(c=='.') 
    {
        c=getch();  
        for(f = 10.0; isdigit(c); c=getch()) 
        {
            *pn += (c-'0')/f;
            f*=10;
        }
    }
    
    if(c!=EOF)
        ungetch(c);
        
    return c;
}


/* get a (possibly pushed-back) character */
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();   
}


/* push character back on input */
void ungetch(int c)
{
    if(bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c; 
}
