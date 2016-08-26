#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>  /* va_list and args */

#define MAXTOKEN 1000

int minprintf(char *fmt, ...);  /* '...' - accept all the args after fmt */
char * makeStr(char *m, char c, int ia1, int dpoi, int dpoi2, int iarg, int jarg);

#define maketh makeStr(mstr, type, ia1, dpoi, dpoi2, iarg, jarg) /* macro */

main()
{
    int i = 69;
    float j = 0.000232;
    char k[]="frog";
    char *m = &k[0];
    
    minprintf("There %   -2.1c %% %12.4f -2233 -2233- .. *** was %-10.2s at %12p\n",i,j,k,m);

    return 0;
}

/* minprintf: minimal printf with variable arguement list */
int minprintf(char *fmt, ...)
{
    va_list ap;          /* points to each unnamed arg in turn  */
    char mstr[MAXTOKEN]; /* make string in outside function     */
    char *p, *sval, *temp1;
    int ival, type, iarg=0, ia1=0, jarg=0, dpoi=0, dpoi2=0, ineg;
    double dval;
    void *pval;

    va_start(ap, fmt);   /* make ap point to the 1st unnamed arg */
    for(p=fmt; *p; p++) 
    {
        if(*p != '%') {
            putchar(*p);
            continue;
        }
        
        type = *++p;
        
        while(type==' ')  /* Default behaviour seems to be to skip spaces */
            type = *++p;  /* and match with the first chars found after   */
        
        if(type=='-') 
        {
            ineg=1;
            type = *++p;
        } 
        
        if(type=='-') 
        {
            puts("\nerror: invalid formatting '%--'");
            return -1;
        } 
        
        if(type=='.') 
        {
            if(ineg) {
                puts("\nerror: invalid formatting '-.'");
                return -1;
            }
            dpoi = 1;
            type = *++p;
        } 
        
        if(isdigit(type)) 
        {
            iarg = atoi(p);
            ia1 = 1;
            
            while(isdigit(*++p))
                ;
            
            if(ineg) {
               iarg-=(iarg*2);
               ineg = 0;
            } type = *p;
        } 
        
        if(type=='.') 
        {
            if(dpoi) {
                puts("\nerror: invalid formatting '.XX.'");
                return -1;
            }
            dpoi2 = 1;
            type = *++p;
        } 
        
        if(isdigit(type)) 
        {
            jarg = atoi(p);
            ia1 = 1;
            
            while(isdigit(*++p))
                ;
            type = *p;
        } 
        
        if(type=='.') {
            puts("\nerror: invalid formatting '.X.X.'");
            return -1;
        }
        
        switch(type) 
        {
            case '%':
                printf("%%");
                break;
            case 'd':
                ival = va_arg(ap, int);
                temp1 = maketh;
                printf(temp1,ival);
                break;
            case 'i':
                ival = va_arg(ap, int);
                temp1 = maketh;
                printf(temp1,ival);
                break;
            case 'o':
                ival = va_arg(ap, int);
                temp1 = maketh;
                printf(temp1,ival);
                break;
            case 'x':
                ival = va_arg(ap, int);
                temp1 = maketh;
                printf(temp1,ival);
                break;
            case 'X':
                ival = va_arg(ap, int);
                temp1 = maketh;
                printf(temp1,ival);
                break;
            case 'u':
                ival = va_arg(ap, int);
                temp1 = maketh;
                printf(temp1,ival);
                break;
            case 'c':
                ival = va_arg(ap, int);
                temp1 = maketh;
                printf(temp1,ival);
                break;
            case 'f':
                dval = va_arg(ap, double);
                temp1 = maketh;
                printf(temp1,dval);
                break;
            case 'e':
                dval = va_arg(ap, double);
                temp1 = maketh;
                printf(temp1,dval);
                break;
            case 'E':
                dval = va_arg(ap, double);
                temp1 = maketh;
                printf(temp1,dval);
                break;
            case 'g':
                dval = va_arg(ap, double);
                temp1 = maketh;
                printf(temp1,dval);
                break;
            case 'G':
                dval = va_arg(ap, double);
                temp1 = maketh;
                printf(temp1,dval);
                break;
            case 's':
                if(!ia1) {
                    for(sval = va_arg(ap, char *); *sval; sval++)
                        putchar(*sval);
                    break;
                }
                else {
                    sval = va_arg(ap, char *);
                    temp1 = maketh;
                    printf(temp1,sval);
                    for( ; *sval; sval++) /* pass the rest of the string away */
                        ;
                    break;
                }
            case 'p':
                pval = va_arg(ap, void *);
                temp1 = maketh;
                printf(temp1,pval);
                break;
            default:
                putchar(*p);
                break;
          }
          ia1   = 0;  /* flag that num args are being used    */
          iarg  = 0;
          jarg  = 0;
          dpoi  = 0;  /* flags that decimal point is included */
          dpoi2 = 0;  /*   "    "     "       "    "    "     */
      }
      va_end(ap);     /* clean up when done                   */
}


/* makeStr: create and return the formatting string */
char * makeStr(char *m, char c, int ia1, int dpoi, int dpoi2, int iarg, int jarg)
{
    int i=0;
    char res[MAXTOKEN];

    if(!ia1) 
    {
        char f[] = "%%c", c;            /* e.g., %f     */
        sprintf(m,f,c);
    } 
    else 
    {
        if(!dpoi && !dpoi2) {           /* e.g., %3f    */
            char f[] = "%%%c";
            sprintf(m,f,c);
        } else if(dpoi){
            char f[] = "%%%%.%%d%c";    /* e.g., %.3f   */
            sprintf(res,f,c);
            sprintf(m,res,iarg);
        } else {
            char f[] = "%%%%%%d.%%d%c"; /* e.g., %62.3f */
            sprintf(res,f,c);
            sprintf(m,res,iarg,jarg);
        }
    }
    return m;
}
