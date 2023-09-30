/*
 * Yonk Intent Reader
 *
 * Copyright (c) 2022-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <string.h>

#include <yonk/intent.h>

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

static int show_json (struct yonk_intent *o, FILE *to)
{
	int i;

	if (fprintf (to, "[\"%c\"", o->action) < 0)
		return 0;

	for (i = 0; i < o->argc; ++i)
		if (fputc (',', to) == EOF || !show_escaped (o->argv[i], to))
			return 0;

	return fputc (']', to) != EOF;
}

static int show_plain (struct yonk_intent *o, FILE *to)
{
	int i;

	if (fputc (o->action, to) == EOF)
		return 0;

	for (i = 0; i < o->argc; ++i)
		if (o->argv[i][strcspn (o->argv[i], " \"\\")] == '\0') {
			if (fprintf (to, " %s", o->argv[i]) < 0)
				return 0;
		}
		else {
			if (fputc (' ', to) == EOF ||
			    !show_escaped (o->argv[i], to))
				return 0;
		}

	return fputc ('\n', to) != EOF;
}

int yonk_intent_show (struct yonk_intent *o, FILE *to, int json)
{
	return json ? show_json (o, to) : show_plain (o, to);
}
