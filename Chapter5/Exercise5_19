/* Modify undcl so that it does not add redundant parenthese to declarations. */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
#define BUFSIZE 100

enum {NAME, PARENS, BRACKETS}; /* NAME is 0, PARENS has val 1, BRACKETS 2 */

char out[1000];
char token[MAXTOKEN];    /* last token string */
int tokentype;           /* type of last token */

char tmpstore[MAXTOKEN];

int flag=0;              /* whether to add parens or not */
int pos = 0;             /* whether '*' comes before or after '[]()' */

char buf[BUFSIZE];
int bufp = 0;            /* next free position in buffer    */

int getnext(void);
int gettoken(void);
int getch(void);
void ungetch(int c);


/* undcl: convert word descriptions to declarations */
main()
{
    int type, i=0;
    char temp[MAXTOKEN];

    while(gettoken()!=EOF) 
    {
        strcpy(out,token);
        
        while((type=gettoken())!='\n') 
        {
            if(type=='*') 
            {
                if(flag)
                    sprintf(temp, "*%s", out);
                else {
                    sprintf(tmpstore,"*%s",out);
                    i = getnext();
                    sprintf(temp, "%s", tmpstore);
                }
                
                if(!pos) {
                    pos=1;
                }
                
                strcpy(out, temp);
            } 
            else if(type == PARENS || type == BRACKETS) {
                strcat(out,token);
            } 
            else if(type==NAME) 
            {
                if(!pos) {
                    pos=1;
                    flag=1;
                }
                
                sprintf(temp, "%s %s", token, out);
                strcpy(out, temp);
            } 
            else 
            {
                printf("invalid input at %s\n",token);
                break;
            }
        }
        
        printf("%s\n\n",temp);
        flag = 0;
        pos = 0;
    }
    return 0;
}


int getnext(void)
{
    char temp[MAXTOKEN];
    int i, c, type;
    strcpy(temp, tmpstore);
    
    while((type=gettoken())!='\n')
    {
        if(type=='*') {
            sprintf(tmpstore,"*%s",temp);
            sprintf(temp, "%s", tmpstore);
        }
        else if(type == NAME) {
            pos=1;
            flag=1;
            sprintf(tmpstore,"%s %s",token,temp);
            return 1;
        }
        else {
            sprintf(tmpstore,"(%s)",temp);
            strcat(tmpstore,token);
            return 0;
        }
    }
}


int gettoken(void)  /* return next token */
{
    int c;     /* Note the function prototype getch*/
    char *p = token;

    while((c=getch())==' ' || c == '\t')
        ;
        
    if(c == '(') 
    {
        if((c = getch()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } 
        else {
            ungetch(c);
            return tokentype = '(';
        }
    } 
    else if(c == '[') 
    {
        for(*p++ =c; (*p++ = getch()) != ']'; )
            ;
        *p = '\0';
        
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
        return tokentype = c;
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
