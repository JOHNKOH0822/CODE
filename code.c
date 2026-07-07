#include <stdio.h>
// 1 is leap 0 is non-leap
static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year : set day of year from month & day */
int day_of_year(int year, int month, int day)
{
    int i, leap;
    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0; // leap = 1 (TRUE) if conditions are true
    if (month < 1 || month > 12 || day < 1 || day > daytab[leap][month] || year < 0)
    {
        printf("Error : invalid date");
        return -1;
    }
    else
    {
        for (i = 1; i < month; i++)
        {
            day += daytab[leap][i];
        }
        return day;
    }
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;
    int total_yearday [2] = {365 , 366};
    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    if (yearday < 1 || yearday > total_yearday[leap] || year < 1)
    {
        printf("Error : invalid year_day or year");
    }
    else
    {
        for (i = 1; yearday > daytab[leap][i]; i++)
        {
            yearday -= daytab[leap][i];
        }
        *pmonth = i; // how many times the loop runs → which month
        *pday = yearday; // leftover after subtracting → which day of that month
    } 
}
/* month_name: return name of n-th month */
 char *month_name(int n)
{
    // without static, the array destroyed when it returns
    // with static, the name[] lives entire program lifetime
    static char *name[] = { "Illegal month", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
    return (n < 1 || n > 12) ? name[0] : name[n];
}

int main()
{

}
