/*
 * Yonk Intent Matcher
 *
 * Copyright (c) 2022-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <string.h>

#include <yonk/intent.h>

int yonk_intent_match (struct yonk_intent *o, int argc, char *argv[])
{
	int i;

	if (o->argc < argc)
		return 0;

	for (i = 0; i < argc; ++i)
		if (strcmp (o->argv[i], argv[i]) != 0)
			return 0;

	return 1;
}
