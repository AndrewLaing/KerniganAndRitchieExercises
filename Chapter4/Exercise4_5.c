#include <stdio.h>
#include <stdlib.h>    /*for atof() */
#include <ctype.h>
#include <math.h>

#define MAXOP   100    /* max size of operand or operator */
#define MAXVAL  100    /* maximum depth of val stack      */
#define NUMBER  '0'    /* signal that a number was found  */
#define BUFSIZE 100    /* buffer for ungetch              */

/* Main functions */
int    getop(char s[]);
void   push(double f);
double pop(void);
int    getch(void);
void   ungetch(int);

/* Command functions */
void clearstack(void);     /* Command 'cs' Clear current stack   */
void cleardupl(void);      /* Command 'cd' Clear duplicate stack */
void stackprint(void);     /* Command 'ps' Print current stack   */
void dsprint(void);        /* Command 'pd' Print duplicate stack*/
void duplstack(void);      /* Command 'du' Duplicate stack print */
void swaptop(void);        /* Command 'sw' Swap top two elements of stack */
void help(void);           /* Command 'help' Print 'help screen' */

/* External variables */
int sp = 0;                /* Next free stack position        */
double val[MAXVAL];        /* value stack                     */
char buf[BUFSIZE];
int bufp = 0;              /* next free position in buffer    */

double dupval[MAXVAL];     /* saved stack duplicate        */
int dss = 0;               /* duplicate stack size for printing out dupval */

int NOPOP = 0;             /* try not to pop stack after typing in help */

/* main program:  A Reverse Polish calculator. */
main()
{
    int type;
    double op2;
    double mod;
    char s[MAXOP];

    while((type = getop(s)) != EOF) {
        switch(type) {
          case NUMBER:
              NOPOP=0;
              push(atof(s));         /* Add number to stack   */
              break;
          case '+':
              NOPOP=0;
              push(pop() + pop());   // pop last number from stack and add to previous 
              break;                 // number from stack then add to stack as last item
          case '*':
              NOPOP=0;
              push(pop() * pop());   // as above with *
              break;
          case '-':                  // pop last number from stack save as op2
              NOPOP=0;
              op2 = pop();           // pop previous number from stack
              push(pop() - op2);     // otherwise would produce op2 - pop()
              break;                 // and push to stack replacing them
          case '/':
              NOPOP=0;
              op2 = pop();           // as for '-' but with an errorcheck for
              if(op2!=0.0)           // division by zero
                  push(pop()/op2);
              else
                  printf("error: zero divisor\n");
              break;
          case '\%':
              NOPOP=0;
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
          case '\n':                                   // if end of equation pop last item from stack
              if(NOPOP==0) printf("\t%.8g\n", pop());  // aka the answer
              NOPOP=0;
              break;
          default:
              NOPOP=0;
              printf("error: unknown command %s\n", s);  // None of the above
              break;                                     // You dun goofed
        }
    }
    return 0;
}


/* ////////////// MAIN FUNCTIONS ////////////// */

/* getop: get next character or numeric operand */
int getop(char s[])
{
    int i, c;
    double l, op2;  /* Used to keep answer passed to push() compatible */

    do {
      while((s[0] = c = getch()) == ' ' || c == '\t')
          ;
      
      if(c=='c') 
      {
          s[0] = c = getch();
          if(c =='s') clearstack();       /* cs - Clear current stack    */
          else if(c=='d') cleardupl();    /* cd - Clear duplicate stack   */
          else if(c=='o') {
              s[0] = c = getch();
              if(c=='s') {                /* cos - cos(x) function */
                  l = cos(pop()); 
                  NOPOP=0;
                  push(l);                /* push to stack here */
              }
          }
          while((s[0] = c = getch()) == ' ' || c == '\t')
              ;
      }
      else if(c=='d') 
      {
          s[0] = c = getch();
          if(c =='u') duplstack();        /* du - Make duplicate of current stack */
          while((s[0] = c = getch()) == ' ' || c == '\t')
              ;
      }
      else if(c=='e') 
      {
          s[0] = c = getch();
          if(c=='x') 
          {
              s[0] = c = getch();
              if(c=='p') {                /* exp - exp(x) function */
                  l = exp(pop()); 
                  NOPOP=0;
                  push(l);                /* push to stack here */
              }
          }
          while((s[0] = c = getch()) == ' ' || c == '\t')
              ;
      }
      else if(c=='h') 
      {
          s[0] = c = getch();
          if(c =='e') {          /* help - Print 'Help screen' */
              s[0] = c = getch();
              if(c =='l') {
                  s[0] = c = getch();
                  if(c =='p') {
                      help();
                  }
              }
          }
          while((s[0] = c = getch()) == ' ' || c == '\t')
              ;
      }
      else if(c=='p') 
      {
          s[0] = c = getch();
          if(c =='s') stackprint();       /* ps - Print current stack   */
          else if(c=='d') dsprint();      /* pd - Print duplicate stack   */
          else if(c=='o') {
              s[0] = c = getch();
              if(c=='w') {                /* pow - pow(x,y) function */
                  op2 = pop();
                  l = pow(pop(),op2);           //    pow(x,y)   x**y
                  NOPOP=0;
                  push(l);                /* push to stack here */
              }
          }
          while((s[0] = c = getch()) == ' ' || c == '\t') // Skip spaces and tabs
              ;
      }
      else if(c=='s') 
      {
          s[0] = c = getch();
          if(c =='w') swaptop();          /* sw - Swap top two elements in current stack */
          else if(c=='i') {
              s[0] = c = getch();
              if(c=='n') {                /* sin - sin(x) function */
                  l = sin(pop()); 
                  NOPOP=0;
                  push(l);                /* push to stack here */
              }
          }
          else if(c=='q') 
          {
              s[0] = c = getch();
              if(c=='r') {                /* sqrt - sqrt(x) function */
                  s[0] = c = getch();
                  if(c=='t') {
                      l = sqrt(pop()); 
                      NOPOP=0;
                      push(l);                /* push to stack here */
                  }
              }
          }
          while((s[0] = c = getch()) == ' ' || c == '\t')
              ;
      }
    }  /* End of do while*/
    
    while(isalpha(c))
        ;
    
    s[0] = c;
    s[1] = '\0';
    
    if(!isdigit(c) && c != '.' && c != '-')
        return c;      /* Not a number          */
    
    i = 0;
    
    if(c == '-'){      /* collect fraction part */
        NOPOP=0;
        if(!isdigit(s[++i] = c = getch())) {
            
            if(c != EOF)     // if an extra char and not a digit 
                ungetch(c);  // put into buffer (eg 4 4 * help
            return '-';
        }
    }

    if(isdigit(c))    /* collect integer part  */
        while(isdigit(s[++i] = c = getch()))
            ;
    
    if(c == '.')      /* collect fraction part */
        while(isdigit(s[++i] = c = getch()))
            ;
    
    s[i] = '\0';
    
    if(c != EOF)
        ungetch(c);
    
    return NUMBER;
}


/* push: push f onto value stack    */
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
    if(sp > 0) {
        if(NOPOP==0) return val[--sp];   // return last item in stack first decrementing sp
        else NOPOP=0;
    }
    else {
        if(NOPOP==0) {
            printf("error: stack empty\n");
            return 0.0;
        }
        else NOPOP=0;
    }
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


/* ////////////// COMMAND FUNCTIONS ////////////// */

/* clearstack: Clear current stack  */
void clearstack(void)
{
    sp=0;
    puts("Stack cleared");
    NOPOP=1;
}


/* cleardupl: Clear duplicate stack */
void cleardupl(void)
{
    dss=0;
    puts("Duplicate stack cleared");
    NOPOP=1;
}

/* stackprint: print out current stack */
void stackprint(void)
{
    int spp = sp;

    if(spp<=0) printf("error: stack empty\n");
    else 
    {
        printf("--Top of current stack--\n");
        while(spp>sp-2)                    // Note > 0 to print full stack
            printf("%9g\n", val[--spp]);   // print last item in stack
        printf("-------------\n");
    }
    NOPOP=1;
}

/* dsprint: print out the duplicate stack top down */
void dsprint(void)
{
    int spp = dss;

    if(spp<=0) printf("error: duplicate stack empty\n");
    else 
    {
        printf("--duplicate stack--\n");
        while(spp>0)                    // Note > 0 to print full stack
            printf("%9g\n", val[--spp]);   // print last item in stack
        printf("--end of duplicate stack --\n");
    }
    NOPOP=1;
}


/* duplstack: make duplicate of the current stack */
void duplstack(void)
{
    dss=0;

    if(sp<=0) printf("error: can't duplicate, stack is empty\n");
    else 
    {
        while(dss<sp) 
        {
            dupval[dss] = val[dss];  
            dss++;
        }
        puts("Duplicate stack created");
    }
    NOPOP=1;
}


/* swaptop: Swap top two elements of stack */
void swaptop(void)
{
    double temp;

    if(sp<=0) printf("error: stack empty\n");
    else if(sp==1) printf("error: \n");
    else 
    {
        temp = val[sp-1];
        val[sp-1]=val[sp-2];
        val[sp-2]=temp;
        puts("Top two elements of stack swapped");
    }
    NOPOP=1;
}


/* help: Print out help on available commands */
void help(void)
{
    puts("------------------------------");
    puts("Help: Commands");
    puts("cs   - Clear current stack");
    puts("cd   - Clear duplicate stack");
    puts("ps   - Print current stack");
    puts("pd   - Print duplicate stack");
    puts("sw   - Swap top two elements in current stack");
    puts("du   - Make duplicate of current stack");
    puts("help - Print this 'Help screen'");
    puts("------------------------------");
    puts("Help: Functions");
    puts("x cos");
    puts("x exp");
    puts("x y pow");
    puts("x sin");
    puts("x sqrt");
    puts("------------------------------");
    NOPOP=1;
}
