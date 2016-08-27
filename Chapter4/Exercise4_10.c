#include <stdio.h>
#include <stdlib.h>  /* for atof() */

#define MAXVAL  100  /* maximum depth of val stack */
#define MAXLINE 1000
#define NUMBER 0
#define LOWER 1

int getline(char s[], int lim); 
void push(double f);
double pop(void);

void skipchars(char s[]);
void coms(char s[]);
void help(void);         /* command: help - print help screen */
void clearstack(void);   /* command: cs - clear current stack */
void cleardupl(void);    /* command: cd - clear duplicate stack */
void stackprint(void);   /* command: ps - print current stack */
void dsprint(void);      /* command: pd - print duplicate stack */
void swaptop(void);      /* command: sw - swap top 2 in current stack */
void duplstack(void);    /* command: du - create duplicate of current stack */

int isnegative(char s[]);/* decides if '-' is an operand or for a negative number */


char line[MAXLINE];

int sp = 0;              /* Next free stack position        */
double val[MAXVAL];      /* value stack                     */
int STRPOS=0;            /* current position in the string being parsed */
double dupval[MAXVAL];   /* saved stack duplicate        */
int dss = 0;             /* duplicate stack size for printing out dupval */

/* Print the input line */
int main()
{
    int i, j;
    double op2;
    double op3;
    double mod;
    char type[MAXLINE];
    char line[MAXLINE];

    j=1;
    i = getline(line, MAXLINE);
    
    while(STRPOS<i) 
    {
        type[0] = line[STRPOS];
        
        if(isdigit(type[0])) type[0]=NUMBER;
        else if(islower(type[0])) type[0]=LOWER;
        
        switch(type[0]) 
        {
          case NUMBER:
              op3 = 0;
              while(isdigit(line[STRPOS])) {
                  op3 = (op3*10)+(line[STRPOS++]-'0');
              }
              push(op3);             // Add number to stack
              break;
          case LOWER:
              coms(line);
              break;
          case ' ':
              break;
          case '\t':
              break;
          case '+':
              push(pop() + pop());   // pop last number from stack and add to previous 
              break;                 // number from stack then add to stack as last item
          case '*':
              push(pop() * pop());   // as above with *
              break;
          case '-':                  // pop last number from stack save as op2
              j = isnegative(line);
              if(j==1)
              {
                  op2 = pop();           // pop previous number from stack
                  push(pop() - op2);     // otherwise would produce op2 - pop()
              }
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
                  if(mod>0 && op2>0) 
                  {
                      while(mod-op2>=0)
                          mod = mod - op2;
                  }
                  else if(mod<0 && op2>0) 
                  {
                      mod = mod-mod-mod;
                      while(mod-op2>=0)
                          mod = mod - op2;
                  }
                  else if(mod<0 && op2<0) 
                  {
                      mod = mod-mod-mod;
                      op2 = op2-op2-op2;
                      while(mod-op2>=0)
                          mod = mod - op2;
                      mod = mod-mod-mod;
                  }
                  else if(mod>0 && op2<0) 
                  {
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
              printf("error: unknown command %c\n", line[STRPOS]);  
              break;
        }
        STRPOS+=1;
    }
    return(0);
}


/* getline: read a line into s, return length */
int getline(char s[], int lim)
{
    int c, i;

    for(i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
        s[i]=c;
        
    if(c=='\n') {
        s[i]=c;
        ++i;
    }
    s[i]='\0';
    
    return i;
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
    else 
    {
        printf("error: stack empty\n");
        return 0.0;
    }
}


/* skipchars: skip lowercase non keywords */
void skipchars(char s[])
{
    while(islower(s[++STRPOS]))
        ;
        
    --STRPOS;
}


/* coms: filter commands from the string */
void coms(char s[])
{
    if(s[STRPOS++]=='h') 
    {
        if(s[STRPOS]=='e') 
        {
            if(s[++STRPOS]=='l') 
            {
                if(s[++STRPOS]=='p') help();
                else {
                    STRPOS++;
                    skipchars(s);
                }
            }
            else {
                STRPOS++;
                skipchars(s);
            }
        }
        else 
        {
            STRPOS++;
            skipchars(s);
        }
    }
    else if(s[--STRPOS]=='c') 
    {
        if(s[++STRPOS]=='s') clearstack();
        else if(s[STRPOS]=='d') cleardupl();
        else 
        {
            STRPOS++;
            skipchars(s);
        }
    }
    else if(s[STRPOS]=='d') 
    {
        if(s[++STRPOS]=='u') duplstack();
        else {
            STRPOS++;
            skipchars(s);
        }
    }
    else if(s[STRPOS]=='p')  
    {
        if(s[++STRPOS]=='s') stackprint();
        else if(s[STRPOS]=='d') dsprint();
        else {
            STRPOS++;
            skipchars(s);
        }
    }
    else if(s[STRPOS]=='s')  
    {
        if(s[++STRPOS]=='w') swaptop();
        else {
            STRPOS++;
            skipchars(s);
        }
    }
    else 
    {
        STRPOS++;
        skipchars(s);
    }
}


/* help: Print out help on available commands */
void help(void)
{
    puts("------------------------------");
    puts("Help: Commands (you wish, lol.)");
    puts("cs   - Clear current stack");
    puts("cd   - Clear duplicate stack");
    puts("ps   - Print current stack");
    puts("pd   - Print duplicate stack");
    puts("sw   - Swap top two elements in current stack");
    puts("du   - Make duplicate of current stack");
    puts("help - Print this 'Help screen'");
    puts("------------------------------");
    puts("Help: Functions");
    puts("pi - add the value of pi to the input line");
    puts("x cos");
    puts("x exp");
    puts("x y pow");
    puts("x sin");
    puts("x sqrt");
    puts("------------------------------");
}


/* clearstack: Clear current stack  */
void clearstack(void)
{
    sp=0;
    puts("Stack cleared");
}


/* cleardupl: Clear duplicate stack */
void cleardupl(void)
{
    dss=0;
    puts("Duplicate stack cleared");
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
            printf("%9g\n", dupval[--spp]);   // print last item in stack
        printf("--end of duplicate stack --\n");
    }
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
}


int isnegative(char s[])
{
    double op3 = 0;
    
    if(isdigit(s[++STRPOS])) 
    {
        while(isdigit(s[STRPOS])) {
            op3 = (op3*10)+(s[STRPOS++]-'0');
        }
        op3 = op3-op3-op3;
        push(op3);
        return 0;
    }
    else 
    {
        --STRPOS;
        return 1;
    }
}
