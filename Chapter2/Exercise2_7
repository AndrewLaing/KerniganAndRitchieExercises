#include <stdio.h>

unsigned invert(unsigned x, int p, int n);

int main()
{
    unsigned x, res;
    int p, n;

    printf("Enter x > ");
    scanf("%u",&x);
    
    printf("Enter p > ");
    scanf("%d",&p);
    
    printf("Enter n > ");
    scanf("%d",&n);
    
    res = invert(x,p,n);
    printf("\nHere's the result %u\n",res);
    
    return(0);
}


/* Invert n bits from position p and leave the rest of x unchanged */
unsigned invert(unsigned x, int p, int n)
{
    unsigned lmbx, j, k, rmbx;

    lmbx = (x >> p+1) << p+1;             // get the leftmost bits before p

    rmbx = (x-lmbx) >> p-n+1;             // get rightmost bits of x after pn
    rmbx = (x-lmbx)^(rmbx<<p-n+1);     

    x = ((x-lmbx) >> (p-n+1)) << (p-n+1); // so only gets pn
    j = (255 >> (7-n+1)) << (p-n+1);      // get 1's at pn
    k = ~((~j)+x);                        // pn inverted

    return (k+rmbx+lmbx);                 // Add back the bits from either side of pn
}
