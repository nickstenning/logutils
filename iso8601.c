#include <sys/time.h>
#include <stdio.h>
#include "iso8601.h"

void timestamp (char s[TIMESTAMP]) {
  char fmt[TIMESTAMP];
  struct timeval tv;
  struct tm* tm;

  gettimeofday(&tv, NULL);
  tm = localtime(&tv.tv_sec);
  if (tm != NULL) {
    // This currently uses nanosecond precision with usecond accuracy. TODO:
    // implement portable nanosecond accuracy.
    strftime(fmt, sizeof fmt, "%Y-%m-%dT%H:%M:%S.%%06u000", tm);
    snprintf(s, TIMESTAMP, fmt, tv.tv_usec);
  }
}

