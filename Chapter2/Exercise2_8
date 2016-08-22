/* Write a function rightrot(x,n) that returns the value of the integer x
   rotated to the right by n positions */

#include <stdio.h>

unsigned rightrot(unsigned x, int n);

int main()
{
    unsigned x, res;
    int p, n;

    printf("Enter x > ");
    scanf("%u",&x);
    
    printf("Enter n > ");
    scanf("%d",&n);
    
    res = rightrot(x,n);
    
    printf("\nHere's the result %u\n",res);
    
    return(0);
}


/* rightrotate x and add bits snipped off to left-hand side*/
unsigned rightrot(unsigned x, int n)
{
    int i, j; 
    unsigned lx, rx, rspx;                  //rspx = >> part of x
    // lx,rx are left and right sides of x (rx being right n bits)

    rspx = x >> n;
    lx = rspx << n; 
    rx = (x-lx) >> n;
    rx = (x-lx)^(rx<<n);     

    i=256;
    j=0;
    
    while(x>=i) 
    {
        i = i*2;
        ++j;
    }
    rx = rx << (8-n)+j;
    
    return (rx+rspx);
}
