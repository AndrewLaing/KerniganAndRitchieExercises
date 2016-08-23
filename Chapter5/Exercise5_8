#include <stdio.h>
#include <stdlib.h>

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int main()
{
    char temp[4];
    int yearday, year, month, day;
    int res=-1;
    int *pmonth;
    int *pday;

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

    return 0;
}


/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
    int i, leap;

    if(year<1 || month<1 || day<1 || month>12)
        return -1;
        
    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    
    if(day>daytab[leap][month])
        return -1;
    
    for(i = 1; i < month; i++)
        day += daytab[leap][i];
    
    return day;
}


/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    
    if(year<1 || yearday<1 || (leap && yearday>366) || (!leap && yearday>365))
        *pday = 99; 
    else 
    {
        for(i=1; yearday>daytab[leap][i]; i++)
            yearday -= daytab[leap][i];

        *pmonth = i;
        *pday = yearday;
    }
}
