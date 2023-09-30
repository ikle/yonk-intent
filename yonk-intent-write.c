/*
 * Yonk Intent Writer
 *
 * Copyright (c) 2022-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <errno.h>
#include <string.h>

#include <yonk/intent.h>

int yonk_intent_write (struct yonk_intent *o, FILE *to)
{
	int i;
	size_t len;

	if (fputc (o->action, to) == EOF || fputc (o->argc, to) == EOF)
		return 0;

	for (i = 0; i < o->argc; ++i) {
		if ((len = strlen (o->argv[i])) > 255) {
			errno = EPROTO;
			return 0;
		}

		if (fputc (len, to) == EOF || fputs (o->argv[i], to) == EOF)
			return 0;
	}

	return 1;
}
