#include <stdio.h>

int main()
{
    char c;
    int i, j;

    int hist[256];         // to store ascii character count
    
    for(i=0; i<256; ++i)   // initialize to 0's
        hist[i]=0;
        
    while((c = getchar()) != EOF) 
        hist[c]++;         // Add 1 to char count in hist[ascii value of c]
  
    puts("\n   -------- HISTOGRAM --------\n");

    for(i=32; i<126; ++i) 
    {
        printf("%c : ",i);
        
        for(j=0; j<hist[i]; ++j)
            printf("#");
            
        printf("\n");
    }
    return(0);
}
