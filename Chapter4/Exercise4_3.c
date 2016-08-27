#include <stdio.h>
#include <stdlib.h> /*for atof() */
#include <ctype.h>

#define MAXOP   100     /* max size of operand or operator */
#define MAXVAL  100     /* maximum depth of val stack      */
#define NUMBER  '0'     /* signal that a number was found  */
#define BUFSIZE 100     /* buffer for ungetch              */

int getop(char s[]);
void push(double f);
double pop(void);
int getch(void);
void ungetch(int);


int sp = 0;             /* Next free stack position        */
double val[MAXVAL];     /* value stack                     */
char buf[BUFSIZE];
int bufp = 0;           /* next free position in buffer    */


/* Reverse Polish calculator */
main()
{
    int type;
    double op2;
    double mod;
    char s[MAXOP];

    while((type = getop(s)) != EOF) 
    {
        switch(type) {
          case NUMBER:
              push(atof(s));         // Add number to stack
              break;
          case '+':
              push(pop() + pop());   // pop last number from stack and add to previous 
              break;                 // number from stack then add to stack as last item
          case '*':
              push(pop() * pop());   // as above with *
              break;
          case '-':                  // pop last number from stack save as op2
              op2 = pop();           // pop previous number from stack
              push(pop() - op2);     // otherwise would produce op2 - pop()
              break;                 // and push to stack replacing them
          case '/':
              op2 = pop();           // as for '-' but with an errorcheck for
              if(op2!=0.0)           // division by zero
                  push(pop()/op2);
              else
                  printf("error: zero divisor\n");
              break;
          case '\%':
              op2 = pop();            // as for '-' but with an errorcheck for
              mod = pop();            // % cannot be applied to float or double
              if(op2!=0.0) {          // so do the math here instead.
                  if(mod>0 && op2>0) {
                      while(mod-op2>=0)
                          mod = mod - op2;
                  }
                  else if(mod<0 && op2>0) {
                      mod = mod-mod-mod;
                      while(mod-op2>=0)
                          mod = mod - op2;
                  }
                  else if(mod<0 && op2<0) {
                      mod = mod-mod-mod;
                      op2 = op2-op2-op2;
                      while(mod-op2>=0)
                          mod = mod - op2;
                      mod = mod-mod-mod;
                  }
                  else if(mod>0 && op2<0) {
                      op2 = op2-op2-op2;
                      while(mod-op2>=0)
                          mod = mod - op2;   
                      mod = mod-mod-mod;
                  }
                  push(mod);
              }
              else
                  printf("error: zero divisor\n");
              break;
          case '\n':                      // if end of equation pop last item from stack
              printf("\t%.8g\n", pop());  // aka the answer
              break;
          default:
              printf("error: unknown command %s\n", s);  // None of the above
              break;                                     // You dun goofed
        }
    }
    return 0;
}

/* push: push f onto value stack */
void push(double f)
{
    if(sp < MAXVAL)
        val[sp++] = f;     // Add item as stack[sp] then increment sp
    else
        printf("error: stack full, cant push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
    if(sp > 0)
        return val[--sp];   // return last item in stack first decrementing sp
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

/* getop: get next character or numeric operand */
int getop(char s[])
{
    int i, c;

    while((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    
    s[1] = '\0';
    
    if(!isdigit(c) && c != '.' && c != '-')
        return c;     /* Not a number          */
    
    i = 0;
    
    /* collect fraction part */
    if(c == '-')
    {      
        if(!isdigit(s[++i] = c = getch())) {
            if(c != EOF)
                ungetch(c);
            return '-';
        }
    }

    /* collect integer part  */
    if(isdigit(c))   
        while(isdigit(s[++i] = c = getch()))
            ;
    
    /* collect fraction part */ 
    if(c == '.')      
        while(isdigit(s[++i] = c = getch()))
            ;
            
    s[i] = '\0';
    
    if(c != EOF)
        ungetch(c);
    
    return NUMBER;
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
        buf[bufp++] = c;  // Add character to buffer and increment bufp
}
