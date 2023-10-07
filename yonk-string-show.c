/*
 * Yonk String Show
 *
 * Copyright (c) 2022-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <string.h>

#include <yonk/string.h>

static int show_escaped (const char *s, FILE *to)
{
	if (fputc ('"', to) == EOF)
		return 0;

	for (; *s != '\0'; ++s)
		switch (*s) {
		case '"': case '\\':
			if (fputc ('\\', to) == EOF)
				return 0;
		default:
			if (fputc (*s, to) == EOF)
				return 0;
		}

	return fputc ('"', to) != EOF;
}

int yonk_string_show (const char *prefix, const char *s, int human, FILE *to)
{
	if (human && s[strcspn (s, " \"\\")] == '\0')
		return fprintf (to, "%s%s", prefix, s) > 0;

	return fputs (prefix, to) != EOF && show_escaped (s, to);
}
