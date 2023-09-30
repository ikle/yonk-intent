/*
 * Yonk Intent Destructor
 *
 * Copyright (c) 2022-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdlib.h>

#include <yonk/intent.h>

void yonk_intent_free (struct yonk_intent *o)
{
	int i;

	if (o == NULL)
		return;

	for (i = 0; i < o->argc; ++i)
		free (o->argv[i]);

	free (o->argv);
	free (o);
}
