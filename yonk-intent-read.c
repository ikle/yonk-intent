/*
 * Yonk Intent Reader
 *
 * Copyright (c) 2022-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <errno.h>
#include <stdlib.h>

#include <yonk/intent.h>

struct yonk_intent *yonk_intent_read (FILE *from)
{
	struct yonk_intent *o;
	int action, argc, i, len;

	errno = EPROTO;

	if ((action = fgetc (from)) == EOF || (argc = fgetc (from)) == EOF)
		return NULL;

	if ((o = malloc (sizeof (*o))) == NULL)
		return o;

	if ((o->argv = malloc (sizeof (o->argv[0]) * argc)) == NULL)
		goto no_argv;

	for (i = 0; i < argc; ++i) {
		if ((len = fgetc (from)) == EOF ||
		    (o->argv[i] = malloc (len + 1)) == NULL)
			goto no_arg;

		if (fread (o->argv[i], len, 1, from) != 1)
			goto no_read;

		o->argv[i][len] = '\0';
	}

	o->next   = NULL;
	o->action = action;
	o->argc   = argc;
	return o;
no_read:
	free (o->argv[i]);
no_arg:
	for (--i; i >= 0; --i)
		free (o->argv[i]);

	free (o->argv);
no_argv:
	free (o);
	return NULL;
}
