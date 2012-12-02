#include <yajl/yajl_gen.h>

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "iso8601.h"

#define MAXLINE 4097

void chk(yajl_gen_status stat)
{
	assert(stat == yajl_gen_status_ok);
}

void writejson(FILE * out, char *stamp, char *line, size_t len, int fragment)
{
	yajl_gen g;

	const unsigned char *buf;
	size_t buflen;

	g = yajl_gen_alloc(NULL);

	yajl_gen_config(g, yajl_gen_beautify, 0);
	yajl_gen_config(g, yajl_gen_validate_utf8, 1);

	chk(yajl_gen_map_open(g));

	chk(yajl_gen_string(g, (const unsigned char *)"timestamp", 9));
	chk(yajl_gen_string(g, (const unsigned char *)stamp, TIMESTAMP));

	chk(yajl_gen_string(g, (const unsigned char *)"message", 7));
	chk(yajl_gen_string(g, (const unsigned char *)line, len));

	if (fragment >= 0) {
		char fragmentStr[30];

		snprintf(fragmentStr, 30, "%d", fragment);

		chk(yajl_gen_string(g, (const unsigned char *)"fragmentId", 10));
		chk(yajl_gen_number(g, fragmentStr, strlen(fragmentStr)));
	}

	chk(yajl_gen_map_close(g));

	yajl_gen_get_buf(g, &buf, &buflen);
	fwrite(buf, 1, buflen, out);
	yajl_gen_clear(g);
	yajl_gen_free(g);

	putc('\n', out);
}

int main()
{
	int c;
	int frag;
	char stamp[TIMESTAMP];
	char line[MAXLINE];
	size_t len;

	frag = -1;

	for (;;) {
		c = getc(stdin);

		if (feof(stdin)) {
			break;
		}

		timestamp(stamp);
		ungetc(c, stdin);

		while (fgets(line, MAXLINE, stdin) != NULL) {
			if (ferror(stdin)) {
				fputs(stamp, stderr);
				fputs(" ERROR: error encountered while reading line.\n",
				      stderr);
				return 5;
			}

			len = strlen(line);

			if (line[len - 1] != '\n' || frag >= 0) {
				frag++;
			}

			writejson(stdout, stamp, line, len, frag);

			if (line[len - 1] == '\n') {
				frag = -1;
				break;
			}
		}

		if (ferror(stdout)) {
			fputs(stamp, stderr);
			fputs(" ERROR: error encountered while writing line.\n",
			      stderr);
			return 5;
		}

		if (feof(stdin)) {
			break;
		}
	}

	return 0;
}
