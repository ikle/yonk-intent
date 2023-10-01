/*
 * Yonk Patch Del
 *
 * Copyright (c) 2022-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <yonk/patch.h>

static int parent_deleted (struct yonk_intent *o, struct yonk_intent *list)
{
	for (; list != NULL; list = list->next)
		if (list->action == '-' &&
		    yonk_intent_match (o, list->argc, list->argv))
			return 1;
	return 0;
}

int yonk_patch_del (struct yonk_patch *o, int argc, char *argv[])
{
	struct yonk_intent *e;

	if (!yonk_patch_drop (o, argc, argv))
		return 0;

	if ((e = yonk_intent_alloc ('-', argc, argv)) == NULL)
		return 0;

	if (parent_deleted (e, o->seq.head))
		yonk_intent_free (e);
	else
		yonk_intent_seq_enqueue (&o->seq, e);

	return 1;
}
