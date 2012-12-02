#include <stdio.h>
#include "iso8601.h"

int main()
{
	char stamp[TIMESTAMP];

	timestamp(stamp);
	puts(stamp);
	return 0;
}
