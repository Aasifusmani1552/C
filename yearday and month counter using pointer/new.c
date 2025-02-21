#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

int day_of_year(int* year, int* month, int* day) {
    int   leap, oday = 0;
    char* daytabp;
    leap = (*year % 4 == 0 && *year % 100 != 0) || (*year % 400 == 0);
    if (*day > 31 || *month > 12) {
        printf("error: invalid day or month entered!!\n");
    }
    if (leap == 0 && *month == 2) {
        if (*day > 28) {
            printf("invalid number of days in february");
        }
    }

    daytabp = daytab[leap];
    while (--*month) {
        oday += *++daytabp;
    }
    oday += *day;
    return oday;
}

void month_day(int* yearday, int* year, int* pmonth, int* pday) {
    int        leap;
    char*      daytabpt;
    static int months = 1;
    leap       = (*year % 4 == 0 && *year % 100 != 0) || (*year % 400 == 0);
    daytabpt   = daytab[leap];
    char* temp = daytabpt;
    if (*yearday > 366) {
        printf("error: invalid number of days for a year!!\n");
    }
    if (*yearday == 366 && leap == 0) {
        printf("error: invalid days, given year is a non-leap year!!\n");
    }

    while (*yearday > *(temp + 1)) {
        *yearday -= daytabpt[1];
        temp++;
        daytabpt++;
        months++;
    }
    *pmonth = months;
    *pday   = *yearday;
}
int main() {
    int year = 2023;
    int month;
    int day;
    int yearday = 366;
    month_day(&yearday, &year, &month, &day);
    printf("the month is %d and the day is %d\n", month, day);

    return 0;
}