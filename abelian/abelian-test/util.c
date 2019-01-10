#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

void bin_to_hex (const unsigned char *in, size_t in_len, char **out)
{
	static char digits[] = "0123456789abcdef";
	size_t i;
	char *o = (char *) malloc(sizeof(char) * (in_len * 2 + 1));
	if (o == NULL) {
		*out = NULL;
		return;
	}
	for (i = 0; i < in_len; i++) {
		o[i * 2] = digits[(in[i] >> 4) & 0xF];
		o[i * 2 + 1] = digits[in[i] & 0xF];
	}
	o[in_len * 2] = '\0';
	*out = o;
}
