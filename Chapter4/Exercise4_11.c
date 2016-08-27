#include <stdio.h>
#include <stdlib.h> 
#include <ctype.h>

#define MAXOP   100 
#define MAXVAL  100 
#define NUMBER  '0' 
#define MAXLINE 1000 

int getop(char s[]);
void push(double f);
double pop(void);
void getline(char s[], int lim);

int sp = 0;
double val[MAXVAL];


/* Reverse Polish calculator */
main()
{
    int type;
    double op2;
    char s[MAXOP];

    while((type = getop(s)) != EOF) 
    {
        switch(type) {
          case NUMBER:
              push(atof(s));
              break;
          case '+':
              push(pop() + pop());
              break;
          case '*':
              push(pop() * pop());
              break;
          case '-':
              op2 = pop();
              push(pop() - op2);
              break;
          case '/':
              op2 = pop();
              if(op2!=0.0)
                  push(pop()/op2);
              else
                  printf("error: zero divisor\n");
              break;
          case '\n':
              printf("\t%.8g\n", pop());
              break;
          default:
              printf("error: unknown command %s\n", s);
              break;
        }
    }
    return 0;
}

/* push: push f onto value stack */
void push(double f)
{
    if(sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, cant push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
    if(sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

/* getop: get next character or numeric operand */
int getop(char s[])
{
    int i, c;
    static int charstore = 0;

    if(charstore==0)     /* if no char in charstore getchar()  */
        c = getchar();   /* note 0 would be '0' not 0, ascii.. */
    else {
        c = charstore;   /* else add it to c and reinitialize it */
        charstore = 0;  
    }
    
    while((s[0] = c ) == ' ' || c == '\t')
        c = getchar();
    s[1] = '\0';
    
    if(!isdigit(c) && c != '.')
        return c; 
    
    i = 0;
    
    if(isdigit(c))
        while(isdigit(s[++i] = c = getchar()))
            ;
    
    if(c == '.')
        while(isdigit(s[++i] = c = getchar()))
            ;
    s[i] = '\0';
    
    if(c != EOF)        /* if c has got an extra char add it to charstore */
        charstore = c;
    
    return NUMBER;
}


/* getline: read a line into s, return length */
void getline(char s[], int lim)
{
    int c, i;

    for(i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
        s[i]=c;
        
    if(c=='\n') 
        s[i++]=c;
    s[i]='\0';
}
