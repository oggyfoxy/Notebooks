/*

TODO: Rewrite the routines day_of_year and month_day with pointers instead of
indexing. 
---
ex 5-9

*/

#include <stdio.h>

// Define the days in each month, accounting for leap years
static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day) {
    int leap;
    char *p;

    leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    p = daytab[leap];
    while (--month) 
        day += *++p;
    return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday) {
    int i, leap;
    char *p;
    
    int month = 1;


    leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    p = daytab[leap];
    while (yearday > *p) {
      month++;
      yearday -= *++p;
    }
    *pmonth = month; // or p - *(daytab + leap);
    *pday = yearday;
}

int main() {
    int year = 2024;
    int month = 3;
    int day = 15;
    int yearday;
    int calculated_month, calculated_day;

    // Convert a given date (year, month, day) to day of the year
    yearday = day_of_year(year, month, day);
    printf("Day of year for %d-%02d-%02d: %d\n", year, month, day, yearday);

    // Convert a day of the year back to month and day
    month_day(year, yearday, &calculated_month, &calculated_day);
    printf("Date for day %d of year %d: %d-%02d-%02d\n", yearday, year, year, calculated_month, calculated_day);

    return 0;
}

