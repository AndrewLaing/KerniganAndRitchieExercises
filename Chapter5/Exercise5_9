#include <stdio.h>
#include <stdlib.h>

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

static int nonleap[]  = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static int leapyear[] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
char *month_name(int n);

int main()
{
    char temp[4];
    int yearday, year, month, day;
    int res=-1;
    int *pmonth;
    int *pday;

    char *pm; 

    while(res==-1) 
    {
        printf("Enter year >");
        gets(temp);
        year=atoi(temp);
    
        printf("Enter month >");
        gets(temp);
        month=atoi(temp);
    
        printf("Enter day >");
        gets(temp);
        day=atoi(temp);
    
        res = day_of_year(year, month, day);
    
        if(res==-1)
            printf("You entered %d/%d/%d...\nTry again.\n",year,month,day);
    }
    
    printf("Day %d of the year.\n",res);

    day = 99;
    pmonth = &month;
    pday = &day;

    while(day==99) 
    {
        printf("Enter year >");
        gets(temp);
        year=atoi(temp);
    
        printf("Enter yearday >");
        gets(temp);
        yearday=atoi(temp);
    
        month_day(year, yearday, pmonth, pday);
    
        if(day==99)
            printf("You entered %d/%d...\nTry again.\n",year,yearday);
    }
    
    printf("result: %d/%d/%d\n",year,month,day);
    
    pm = month_name(month);
    printf("The month is called %s\n",pm);
    
    return 0;
}


/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
    int i, leap;
    static int *p1[2];
    
    p1[0] = nonleap;
    p1[1] = leapyear;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    
    for(i = 1; i < month; i++)
        day += *(++p1[leap]);
    
    return day;
}


/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;
    static int *p1[2];
    
    p1[0] = nonleap;
    p1[1] = leapyear;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    
    for(i=1; yearday>*(++p1[leap]); i++)
        yearday -= *(p1[leap]);
    
    *pmonth = i;
    *pday = yearday;
}


/* month_name: return name of n-th month */
char *month_name(int n)
{
    static char *name[] = {
        "Illegal month",
        "January", "February", "March",
        "April", "May", "June",
        "July", "August", "September",
        "October", "November", "December"
    };
    
    printf("month = %s\n",name[n]);
    
    return(n < 1 || n > 12) ? name[0] : name[n];
}
