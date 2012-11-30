#include <stdio.h>
#include "iso8601.h"

char stamp[TIMESTAMP];

int main()
{
  timestamp(stamp);
  puts(stamp);
  return 0;
}
