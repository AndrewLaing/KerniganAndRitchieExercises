/* 
 * Write a version of scanf analogous to minprintf() from the previous section
 */

#include <stdio.h>
#include <stdarg.h>  /* va_list and args */

#define MAXCHAR 100    /* maximum number of chars in char foobar[] */
#define NUMBER 0 

int minscanf(char *fmt, ...);

main()
{
    int i, res;
    float j;
    char k[MAXCHAR];
    char k1[MAXCHAR];
    int m;

    res = minscanf("%4[0-9]%f%s", k, &j, k1); /* going over string width returns error
                                                  or overflows into the next formatting */
    if(res!=0) {
        printf("k  = %s\n",k);
        printf("j  = %f\n",j);
        printf("k1 = %s\n",k1);    
    } else puts("Error received from minscanf()"); 
    return 0;
} 


int minscanf(char *fmt, ...)
{
    int i, res, type, wasnum=0, numarg=0, mrclean=0;
    char *p;
    char *temp;
    char temp1[MAXCHAR];
    char formstr[MAXCHAR];
    int *ival;
    float *dval;
    char *sval;

    /* i is an iterator
     * res is the return value from scanf()
     * type is the current char in *p
     * wasnum is a flag for if a NUMBER has just been parsed
     * numarg is a store for the lhs of the decimal point in the formatting string
     * mrclean is a flag for resetting the variables instead of after each case
     * *p is the pointer to fmt
     * temp is for the formatting string
     * temp1 is for the %[XXX] formatting strings contents
     * ival, dval, sval are pointers to the ... args
     * fmt is the formatting string sent from main()                                 */


    va_list ap;                 /* initialize */
    va_start(ap, fmt);          /* pass the variables after char *j */

    printf("formatting string =  %s\n",fmt);
    for(p = fmt; *p; *p++) 
    { 
        if(*p != '%' && !wasnum) return 0;
            /* '*p' because we are dereferencing 'p' for its contents
             * No errors if string being parsed properly
             * the outer for loop increments after the switch loop finishes   */
        type = *++p; /* Increment to the next item from the formatting string */
        if(type>='0' && type<='9')
            type=NUMBER;
        switch(type) 
        {
            case NUMBER:/* parses one number at a time */
                numarg = (numarg * 10) + ((*p)-'0');
                wasnum = 1;
                *--p;  /* This is to balance the 'type = *++p;' after the forloops '*p++' */
                break;
            case 'd':  
                ival = va_arg(ap, int *); /* ival now points to ap */
                                          /* forgetting anything it used to point to */
                if(wasnum) {
                    char *temp = formstr;
                    sprintf(temp,"%%%d%c",numarg,type);
                    res = scanf(temp,ival);
                } 
                else res = scanf("%d", ival);
                
                if(res==0)  return 0;
                mrclean = 1;
                break;
            case 'f':
                dval = va_arg(ap, float *);
                if(wasnum) 
                {
                    char *temp = formstr;
                    sprintf(temp,"%%%d%c",numarg,type);
                    res = scanf(temp,dval);
                } 
                else res = scanf("%f", dval);
                
                if(res==0) return 0;
                mrclean = 1;
                break;
            case 's':
                sval = va_arg(ap, char *);
                if(wasnum) 
                {
                    char *temp = formstr;
                    sprintf(temp,"%%%d%c",numarg,type);
                    res = scanf(temp, sval);
                } 
                else res = scanf("%s", sval);
                
                if(res==0)  return 0;
                mrclean = 1;
                break;
            case '[':
                sval = va_arg(ap, char *); 
                char *temp = formstr;
                for(i=0; *p!=']'; *++p, i++)
                    temp1[i] = *p;
                temp1[i] = *p;
                temp1[i+1] = '\0';
                if(wasnum) 
                {
                    sprintf(temp,"%%%d%s%c",numarg,temp1,type);
                    res = scanf(temp, sval);
                } 
                else {
                    sprintf(temp,"%%%s%c",temp1,type);
                    res = scanf(temp, sval);
                }
                mrclean = 1;
                break;
            default:
                puts("was none of the above");
                return 0;
        }
        
        if(mrclean) {
            wasnum = 0;     /* reset number flag */
            numarg = 0;     /* and number stores */
            mrclean = 0;
        }
    }
    va_end(ap);             /* end the va_list routine */
    return res;
}
