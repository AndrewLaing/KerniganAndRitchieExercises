/* Rewrite the postfix calculator of Chapter 4 to use scanf() and/or sscanf() to
 * do the input and number conversion */
 
#include <stdio.h>
#define MAXCHAR 100

int do_math(char c);

int stackpos;
float stack[MAXCHAR];


main()
{
    int i;
    char token[MAXCHAR];

    while((i = scanf("%s",token)) != EOF && i!=0) 
    {
        if(sscanf(token, "%f", &stack[stackpos]) == 1) // the args to sscanf
            stackpos++;
        else 
        {
            if(stackpos==0) {
                printf("error<%c>: Stack is empty\n",token[0]);
                break;
            } 
            
            i = do_math(token[0]);
            if(i==-1) break;
        }
    } 
    puts("--- End of Program ---");
    return 0;
}

int do_math(char c)
{
    double temp=0, temp1=0;

    stackpos--;
    switch(c) 
    {
        case '+':
            if(stackpos==0) {
                printf("error<%c>: Only one item in stack\n%0.3f\n",c, stack[stackpos]);
                return -1;
            } 
            
            temp  = stack[stackpos--];
            temp1 = stack[stackpos];
            stack[stackpos++] = temp1 + temp;
            break;
        case '-':
            if(stackpos==0) {
                printf("error<%c>: Only one item in stack\n%0.3f\n",c, stack[stackpos]);
                return -1;
            } 
            
            temp  = stack[stackpos--];
            temp1 = stack[stackpos];
            stack[stackpos++] = temp1 - temp;
            break;
        case '*':
            if(stackpos==0) {
                printf("error<%c>: Only one item in stack\n%0.3f\n",c, stack[stackpos]);
                return -1;
            } 
            
            temp  = stack[stackpos--];
            temp1 = stack[stackpos];
            stack[stackpos++] = temp1*temp;
            break;
        case '/':
            if(stackpos==0) {
                printf("error<%c>: Only one item in stack\n%0.3f\n",c, stack[stackpos]);
                return -1;
            } 
            
            temp  = stack[stackpos--];
            
            if(temp==0) {
                puts("error: division by zero");
                return -1;
            } 
            
            temp1 = stack[stackpos];
            stack[stackpos++] = temp1/temp;
            break;
        case '\%':
            if(stackpos==0) {
                printf("error<%c>: Only one item in stack\n%0.3f\n",c, stack[stackpos]);
                return -1;
            } 
            
            temp  = stack[stackpos--];
            temp1 = stack[stackpos];
            
            if(temp!=0.0) 
            { 
                if(temp1>0 && temp>0) {
                    while(temp1-temp>=0)
                        temp1 = temp1 - temp;
                }
                else if(temp1<0 && temp>0) {
                    temp1 = temp1-temp1-temp1;
                    while(temp1-temp>=0)
                        temp1 = temp1 - temp;
                }
                else if(temp1<0 && temp<0) {
                    temp1 = temp1-temp1-temp1;
                    temp = temp-temp-temp;
                    while(temp1-temp>=0)
                        temp1 = temp1 - temp;
                    temp1 = temp1-temp1-temp1;
                }
                else if(temp1>0 && temp<0) {
                    temp = temp-temp-temp;
                    while(temp1-temp>=0)
                        temp1 = temp1 - temp;   
                    temp1 = temp1-temp1-temp1;
                }
                stack[stackpos++]=temp1;
            }
            else {
                printf("error<\%>: division by zero\n",c);
                return -1;
            } 
            break;
        case '=':
            printf("result = %0.3f\n",stack[stackpos]);
            return -1;
            break;
        default:
            printf("error<%c>: invalid character\n",c);
            return -1;
            break;
    }
    printf("\t%0.3f\n",stack[stackpos-1]);
    return 1;
}
