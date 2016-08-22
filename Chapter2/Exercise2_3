#include <stdio.h>
#include <ctype.h>

int htoi(char s[]);

int main()
{
    int i, n, c;
    char s[10];     // A very large number in hex :D

    i=0;

    printf("Enter a hexstring >");

    while((c=getchar())!=EOF && c!='\n') 
    {
        s[i]=c;
        ++i;
    }
    
    s[i]='\0';      // doesn't automatically add '\0'
    n = htoi(s);
    
    if(i==0) puts("\n<<<Try using data>>>");
    else if(n==-1) puts("<<<Not a hexstring>>>");
    else printf("Converted value = %d\n",n);

    return(0);
}

int htoi(char s[])
{
    int i, n;
    int HEX;      /* Used to determine cases where hex is preceeded by 0x or 0X */

    i = n = 0;
    HEX=2;

    while(s[i] != '\0') 
    {
        if((isxdigit(s[i])) || (s[i]=='x' && i==1) || (s[i]=='X' && i==1)) 
        {
            if(s[i]=='0' && i==0)
                HEX=0;
            else if((s[i]=='x' && i==1) || (s[i]=='X' && i==1))
                HEX=1;
            else if(HEX==0 || HEX==1)               // (Valid 0x,0X or 0 intro)
                HEX=2;
                
            if(HEX==2) 
            {
                if(s[i] >= 'A' && s[i] <= 'F')
                    n = 16*n + (s[i]-'7');          // for base 16; 128 64 32 16 0
                else if(s[i] >= 'a' && s[i] <= 'f')
                    n = 16*n + (s[i]-'W'); 
                else
                    n = 16*n + (s[i]-'0');
            }
        }
        else return(-1);
            
        ++i;
    }
    
    return(n);
}
