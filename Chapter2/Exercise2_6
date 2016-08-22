#include <stdio.h>

unsigned getbits(unsigned x, int n, int p, unsigned y);

int main()
{
    unsigned x, y, res;
    int p, n;

    printf("Enter x > ");
    scanf("%u",&x);
    
    printf("Enter y > ");
    scanf("%u",&y);
    
    printf("Enter n > ");
    scanf("%d",&n);
    
    printf("Enter p > ");
    scanf("%d",&p);

    res = getbits(x,n,p,y);
    printf("\nHere's the answer > %u\n",res);

    return(0);
}


/* find two parts of x and insert one part of y */
unsigned getbits(unsigned x, int n, int p, unsigned y)
{
    unsigned rmby;    // rightmost n bits of y << p
    unsigned lmbx;    // leftmost bits of x before p
    unsigned rmbx;    // rightmost bits of x, n bits after p

    lmbx = (x >> p+1);       // wipe off p to 0
    lmbx = (lmbx << p+1);    // returns num b4 p

    rmbx = (x-lmbx) >> p-n+1;        // get rightmost bits of x after pn
    rmbx = (x-lmbx)^(rmbx<<p-n+1);   // first removing leftmost bits
    
    rmby = y >> n;           // wipe off rightmost n bits
    rmby = y^(rmby<<n);      // this gets rightmost n bits by comparing rmby
                             // with rmby - rightmost n bits
    rmby = rmby << (p-n+1);  // this leftshifts them to position p

    return (lmbx+rmbx+rmby); // Put them together.
}
