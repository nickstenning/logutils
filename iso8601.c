#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include "iso8601.h"

void timestamp (char s[]) {
  struct timeval tv;
  struct tm* tm;

  gettimeofday(&tv, NULL);
  tm = localtime(&tv.tv_sec);
  if (tm != NULL) {
    /* This currently uses nanosecond precision with usecond accuracy. TODO:
     * implement portable nanosecond accuracy.
     */
    strftime(s, TIMESTAMP - 9, "%Y-%m-%dT%H:%M:%S.", tm);
    snprintf(&s[TIMESTAMP - 10], 9, "%06u000", tv.tv_usec);
  }
}

