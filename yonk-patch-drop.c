/*
 * Yonk Patch Drop
 *
 * Copyright (c) 2022-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <string.h>

#include <yonk/patch.h>

static int match_prefix (struct yonk_intent *o, int argc, char *argv[])
{
	int i;

	if (o->argc < argc)
		return 0;

	for (i = 0; i < argc; ++i)
		if (strcmp (o->argv[i], argv[i]) != 0)
			return 0;

	return 1;
}

int yonk_patch_drop (struct yonk_patch *o, int argc, char *argv[])
{
	struct yonk_intent_seq s;
	struct yonk_intent *e;

	yonk_intent_seq_init (&s);

	while ((e = yonk_intent_seq_dequeue (&o->seq)) != NULL)
		if (match_prefix (e, argc, argv))
			yonk_intent_free (e);
		else
			yonk_intent_seq_enqueue (&s, e);

	yonk_intent_seq_move (&s, &o->seq);
	return 1;
}
