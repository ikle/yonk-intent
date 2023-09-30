/*
 * Yonk Intent Constructor
 *
 * Copyright (c) 2022-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <yonk/intent.h>

struct yonk_intent *yonk_intent_alloc (int action, int argc, char *argv[])
{
	struct yonk_intent *o;
	int i;

	if (argc < 0 || argc > 255) {
		errno = EINVAL;
		return NULL;
	}

	if ((o = malloc (sizeof (*o))) == NULL)
		return o;

	if ((o->argv = malloc (sizeof (o->argv[0]) * argc)) == NULL)
		goto no_argv;

	for (i = 0; i < argc; ++i)
		if ((o->argv[i] = strdup (argv[i])) == NULL)
			goto no_copy;

	o->next   = NULL;
	o->action = action;
	o->argc   = argc;
	return o;
no_copy:
	for (--i; i >= 0; --i)
		free (o->argv[i]);

	free (o->argv);
no_argv:
	free (o);
	return NULL;
}
