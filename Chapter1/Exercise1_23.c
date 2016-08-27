#include <stdio.h>


int main()
{
    int c, lc;                /* lc = letter count */
    unsigned char text[2000];
    int CMT, NAC, EOC;        /* comment, not a comment, end of comment */

    lc = CMT = NAC = EOC = 0;
    
    while((c=getchar())!=EOF) 
    {
        if(c=='/' && CMT==0) CMT=1;
        else if(c!='*' && CMT==1) {
            CMT=0;
            NAC=1;
        }
        else if(c=='*' && CMT==1) ++CMT;       /* CMT 2 means is a comment */
        else if(c=='*' && CMT==2) ++CMT;
        else if(c!='/' && CMT==3) --CMT;
        else if(c=='/' && CMT==3) {
            CMT=0;       /* CMT 0 means no comment */
            EOC=1;       /* EOC 1 means don't print final '/' */
        }
        if(NAC==1) {
            text[lc]='/';
            NAC=0;
            ++lc;
        }
        if(CMT==0 && EOC!=1) {
            text[lc]=c;
            ++lc;
        }
        EOC=0;
    }
    printf("\n-------------------------------------------------------\n");
    for(c=0; c<lc; ++c)
        printf("%c",text[c]);
    printf("\n");
    return(0);
}
