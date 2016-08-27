/* Make dcl recover from input errors
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
#define BUFSIZE 100  

enum {NAME, PARENS, BRACKETS}; /* NAME is 0, PARENS has val 1, BRACKETS 2 */

void dcl(void);
void dirdcl(void);
void clearbuffs(void);

int gettoken(void);
int tokentype;           /* type of last token */
int lastchar;

char token[MAXTOKEN];    /* last token string */
char name[MAXTOKEN];     /* identifier name */
char datatype[MAXTOKEN]; /* data type = char, int, etc. */
char out[1000];

char buf[BUFSIZE];
int bufp = 0;            /* next free position in buffer    */


main()  /* convert declaration to words */
{
    int c;
    while(gettoken() != EOF) {     /* 1st token on line */
        strcpy(datatype, token);   /* is the datatype   */
        out[0] = '\0';
        
        if(!isalpha(datatype[0])) {
            for( ; (c = getch()) !='\n'; )
                ;
            puts("error: invalid datatype");
            clearbuffs();
        }
        else if(tokentype==NAME || tokentype==PARENS || tokentype==BRACKETS || \
           tokentype=='*') {
            dcl();                     /* parse rest of line if valid */
        }
        else if(tokentype!='\n') {
            for( ; (c = getch()) !='\n'; )
            printf("syntax error\n");
            clearbuffs();
        }
        
        if(tokentype=='\n') {
            if(lastchar=='[' || lastchar=='(') printf("error: unclosed %c\n",lastchar);
            else printf("%s: %s %s\n", name, out, datatype);
            clearbuffs();
        }
    }
    return 0;
}

int gettoken(void)        /* return next token */
{
    int c, getch(void);   /* Note the function prototype getch*/
    void ungetch(int);
    char *p = token;

    while((c=getch())==' ' || c == '\t')
        ;
        
    if(c == '(') 
    {
        if((c = getch()) == ')') {
            lastchar=0;
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            lastchar = '(';
            ungetch(c);
            return tokentype = '(';
        }
    } 
    else if(c == '[') 
    {
        for(*p++ =c; (*p++ = (c=getch())) != ']'; ) {
            if(!isalnum(c)) {
                lastchar = '[';
                return tokentype=c;
            }
        } *p = '\0';
        lastchar=']';
        return tokentype = BRACKETS;
    } 
    else if(isalpha(c)) 
    {
        for(*p++ = c; isalnum(c = getch()); )
            *p++ = c;
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    } 
    else 
    {
        if(c==')' || c==']')
            lastchar=c;
        return tokentype = c;
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
        buf[bufp++] = c;
}


/* dcl: parse a declarator */
void dcl(void)
{
    int ns;

    for(ns=0; gettoken() == '*'; ) /* count *'s */
        ns++;
    dirdcl();
    
    while(ns-- > 0)
        strcat(out, " pointer to");
}


/* dirdcl: parse a direct declarator */
void dirdcl(void)
{
    int type;

    if(tokentype=='(') {         /* ( dcl ) */
        dcl();
        if(tokentype!=')')
            printf("error: missing )\n");
    } 
    else if(tokentype == NAME) /* variable name */
        strcpy(name, token);
    else
        printf("error: expected name or (dcl)\n");
    
    while((type=gettoken())==PARENS || type == BRACKETS) 
    {
        if(type==PARENS)
            strcat(out, " function returning");
        else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
    }
}


void clearbuffs(void)
{
    int i;
    lastchar=0;
    for(i=0; name[i]!='\0'; )
        name[i++] = '\0';
        
    for(i=0; token[i]!='\0'; )
        token[i++] = '\0';
    
    for(i=0; datatype[i]!='\0'; )
        datatype[i++] = '\0';
    
    for(i=0; out[i]!='\0'; )
        out[i++] = '\0';
    
    while(bufp>0)
        buf[bufp--]='\0';
    tokentype='\n';
}
