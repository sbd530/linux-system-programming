#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <signal.h>

#if 0
struct tm {
    int tm_sec;    /* Seconds (0-60) */
    int tm_min;    /* Minutes (0-59) */
    int tm_hour;   /* Hours (0-23) */
    int tm_mday;   /* Day of the month (1-31) */
    int tm_mon;    /* Month (0-11) */
    int tm_year;   /* Year - 1900 */
    int tm_wday;   /* Day of the week (0-6, Sunday = 0) */
    int tm_yday;   /* Day in the year (0-365, 1 Jan = 0) */
    int tm_isdst;  /* Daylight saving time */
};
#endif

static void print_cur_time(void)
{
    time_t now;
    struct tm *now_tm;

    now = time(NULL);
    printf("current : %ld, ", now);

    now_tm = localtime(&now);

    if (!now_tm)
    {
        printf("localtime() fail\n");
        return;
    }
    printf("%d/%d/%d %d-%d-%d\n",
           now_tm->tm_year + 1900,
           now_tm->tm_mon + 1,
           now_tm->tm_mday,
           now_tm->tm_hour,
           now_tm->tm_min,
           now_tm->tm_sec);
}

static void sigalarm_handler(int signum)
{
    printf("got SIGALRM\n");
    print_cur_time();
}

int main(int argc, char **argv)
{
    struct itimerval ival;
    signal(SIGALRM, sigalarm_handler);

    print_cur_time();
    alarm(5);

#if 0
#include <sys/time.h>
int getitimer(int which, struct itimerval *curr_value);
int setitimer(int which, const struct itimerval *new_value,
              struct itimerval *old_value);
struct itimerval {
    struct timeval it_interval; /* Interval for periodic timer */
    struct timeval it_value;    /* Time until next expiration */
};
struct timeval {
    time_t      tv_sec;         /* seconds */
    suseconds_t tv_usec;        /* microseconds */
};
#endif
    ival.it_value.tv_sec = 5;
    ival.it_value.tv_usec = 0;
    ival.it_interval.tv_sec = 1;
    ival.it_interval.tv_usec = 0;
    if (setitimer(ITIMER_REAL, &ival, NULL))
    {
        printf("setitimer() error\n");
        return -1;
    }

    while (1)
    {
        sleep(1);
    }

    return 0;
}