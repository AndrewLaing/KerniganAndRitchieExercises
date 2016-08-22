#include <stdio.h>

#define UPPER 300
#define LOWER 0
#define STEP  20

float celstofahr(int cels);

int main()
{
    int celsius;

    printf("%3s%6s\n", "Cels", "Fahr");
    
    for(celsius=UPPER;celsius>=LOWER;celsius=celsius-STEP)
        printf("%3d %6.1f\n", celsius, celstofahr(celsius));
    
    return(0);
}

float celstofahr(int cels)
{
    return((((cels*9.0)/5.0))+32.0);
}
