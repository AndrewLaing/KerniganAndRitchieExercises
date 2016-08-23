#include <stdio.h>
#include <ctype.h>

#define MAXLINE 1000

int getline(char line[], int max);
double atof(char s[]);

/* find all lines matching a pattern */
main()
{
    char line[MAXLINE];            
    double res;

    while(getline(line, MAXLINE) > 0) {
        res = atof(line);
        printf("atof returns %g\n",res);
    }
    
    return (0);
}


/* getline: get line into s, return length */
int getline(char s[], int lim)
{
    int c, i;
    i=0;
    
    while(--lim > 0 && (c=getchar())!=EOF && c!='\n')
        s[i++] = c;
    
    if(c=='\n')
        ;
    
    s[i]='\0';
    
    return i;
}


/* atof: convert string to double */
double atof(char s[])
{
    double val, power, res;
    int i, sign, sign2, expo;

    for(i=0; isspace(s[i]); i++) /* skip whitespace */
        ;

    sign = (s[i] == '-') ? -1 : 1;
    
    if(s[i] == '+' || s[i] == '-')
        i++;
    
    for(val=0.0; isdigit(s[i]); i++){
        val=(10.0*val)+(s[i]-'0');
    }
    
    if(s[i]=='.')
        i++;
    
    for(power=1.0; isdigit(s[i]); i++) {
        val=(10.0*val)+(s[i]-'0');
        power*=10;
    }
    
    if(s[i]=='e' || s[i]=='E') 
    {
        i++;
        /* see if its signed else assume it's positive */
        sign2 = 0;
        if(s[i]=='-') {
            sign2=1;
            i++;
        }
        else if(s[i]=='+')
            i++;

        for(expo=0; isdigit(s[i]); i++){
            expo=(10*expo)+(s[i]-'0');
        }
        
        res = sign*val/power;
        
        if(sign2==1) {
            for(i=0; i<expo; i++)   // 1.000000e-07 = 0.0000001
                res = res/10.0;
            return res;
        }
        else {
            for(i=0; i<expo; i++)   // a = 1000000  = 1.000000e+06
                res = res*10.0;
            return res;
        }                             
    }
    return sign*val/power;
}
