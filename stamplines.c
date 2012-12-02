#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "iso8601.h"

#define LINEBUF 2048

static char stamp[TIMESTAMP];

void printstamp (FILE* f) {
  timestamp(stamp);
  fputs(stamp, f);
  putc(' ', f);
}

void pipe_until_eol (FILE* in, FILE* out) {
  char line[LINEBUF];

  while (fgets(line, LINEBUF, in) != NULL) {
    fputs(line, out);

    if (line[strlen(line) - 1] == '\n') {
      break;
    }
  }
}

int main()
{
  int c;

  for (;;) {
    /* We get the first character of each line separately, and calculate the
     * timestamp when the first character is received, rather than waiting for
     * the whole line.
     */
    c = getc(stdin);

    if (feof(stdin)) {
      break;
    }

    printstamp(stdout);
    ungetc(c, stdin);

    /* We've now printed the timestamp, a space, and the first character of
     * the line. Pipe the rest straight through.
     */
    pipe_until_eol(stdin, stdout);

    if (feof(stdin)) {
      break;
    }

  }

  return 0;
}
