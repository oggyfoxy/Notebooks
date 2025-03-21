/*

TODO: There is no error checking in day_of_year or month_day. Remedy this defect. 
---
ex 5-8

works kinda, some bugs perhaps ><
*/

#include <stdio.h>


// Define the days in each month, accounting for leap years
static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day) {
    int i, leap;

    leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if (month < 1 || month > 12)
      return -1;
    if (day < 1 || day > daytab[leap][month]) 
      return -1;
    for (i = 1; i < month; i++)
      day += daytab[leap][i];
    return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday) {
    int i, leap;

    if (year < 1) {
      *pmonth = -1;
      *pday = -1;
      return;
    }
    leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0); // 2003 = leap = 0.
    for (i = 1; i <= 12 && yearday > daytab[leap][i]; i++) // leap = 1 if True or 0 if False
        yearday -= daytab[leap][i];  // ex: day 50. 50 > 31. 50 - 31 = 19. 19 < 28. 
    if (i > 12 && yearday > daytab[leap][12]) { 
      *pmonth = -1;
      *pday = -1;
      return;
    }
    else {
    *pmonth = i; // month = i = 2 = February.
    *pday = yearday; // 19th of february
    }
}

int main() {
    int year = -3;
    int yearday = 366;
    int month, day;
    

    // Convert the day of the year 60 of year 1988 to month and day
    month_day(year, yearday, &month, &day);
    printf("Date for day %d of year %d: %d-%02d-%02d\n", yearday, year, year, month, day);
    return 0;
}

