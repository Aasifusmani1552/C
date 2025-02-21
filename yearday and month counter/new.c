#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30,
     31}};  // two dimensional array for non-leap and leap years
int day_of_year(int year,
                int month,
                int day) {  // funtion to tell the day of year
    int i, leap;
    leap =
        year % 4 == 0 && year % 100 != 0 ||
        year % 400 == 0;  // conditions to check if a year is a leap year or not
    if (month > 12 || day > 31) {
        printf("error: invalid month or day entered!\n");  // if invalid month
                                                           // or day is entered
        return 0;
    }
    if (leap == 0 && month == 2) {  // checking for february month in leap year
        if (day > 28) {
            printf("error: %d is not a leap year\n", year);
        }
    }
    for (i = 1; i < month; i++) {
        day += daytab[leap][i];  // leap will show year and i will iterate to
                                 // months, day entered by user will be added to
                                 // it to show the day of year
    }
    return day;
}
void month_day(int  year,
               int  yearday,
               int* pmonth,
               int* pday) {  // to show month and day of a yearday, taking
                             // pointers to store month and day
    int i, leap;
    leap = year % 4 == 0 && year % 100 != 0 ||
           year % 400 == 0;  // conditions to check for a leap year
    if (yearday > 366) {
        printf(
            "error: invalid number of days in year\n");  // condition to check
                                                         // valid number of days
                                                         // in year
        return;
    }
    if (yearday == 366 && leap == 0) {
        printf(
            "error: invalid number of days in a non-leap year\n");  // condition
                                                                    // to check
                                                                    // valid
                                                                    // number of
                                                                    // days in a
                                                                    // non-leap
                                                                    // year
        return;
    }
    for (i = 1; yearday > daytab[leap][i];
         i++) {  // looping until yearday is less than or equal to leap i that
                 // is days of month of a year
        yearday -=
            daytab[leap]
                  [i];  // subtracting days of month from yearday until it comes
                        // equal to a valid number of days in a month
    }
    *pmonth = i;
    *pday   = yearday;
}

int main() {
    int res = day_of_year(2023, 5, 31);
    int day, month;
    month_day(2023, 367, &month, &day);
    printf("%d\n", res);
    printf("%d and %d", month, day);
    return 0;
}