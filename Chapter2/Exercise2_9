#include <stdio.h>

int bitcount(unsigned x);

int main()
{
    unsigned x;
    int res;

    printf("Enter x > ");
    scanf("%u",&x);
    
    res = bitcount(x);
    
    printf("\n1 bits in %u = %u\n",x, res);
    
    return(0);
}


/* bitcount count 1 bits in x */
int bitcount(unsigned x)
{
    int b=0;
    if(x==0) return 0;       // Idiot test.
    
    while(x&=(x-1))
        ++b;

    return b+1;
}
