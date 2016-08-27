#include <stdio.h>

int main()
{
    int c;
    int PIN, POUT, BIN, BOUT, BRIN, BROUT, SQ, DQ;

    PIN = POUT = BIN = BOUT = BRIN = BROUT = SQ = DQ = 0;
    
    while((c=getchar())!=EOF) 
    {
        if(c=='(') ++PIN;
        if(c==')') ++POUT;
        if(c=='[') ++BIN;
        if(c==']') ++BOUT;
        if(c=='{') ++BRIN;
        if(c=='}') ++BROUT;
        if(c=='"') ++DQ;
        if(c=='\'') ++SQ;

        printf("%c",c);
    }
    
    if(PIN>POUT)   printf("\n Missing %d ')'s ",PIN-POUT);
    if(POUT>PIN)   printf("\n Missing %d '('s ",POUT-PIN);
    if(BIN>BOUT)   printf("\n Missing %d ']'s ",BIN-BOUT);
    if(BIN<BOUT)   printf("\n Missing %d '['s ",BOUT-BIN);
    if(BRIN>BROUT) printf("\n Missing %d '}'s ",BRIN-BROUT);
    if(BRIN<BROUT) printf("\n Missing %d '{'s ",BROUT-BRIN);
    if(DQ%2!=0)    printf("\n Missing '\"'s ");
    if(SQ%2!=0)    printf("\n Missing \"'\"s ");
    puts(" ");

    return(0);
}
