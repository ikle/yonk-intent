/*
 * Yonk Patch Drop
 *
 * Copyright (c) 2022-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "yonk-patch-int.h"

int yonk_patch_drop (struct yonk_patch *o, int argc, char *argv[])
{
	struct yonk_intent_seq s;
	struct yonk_intent *e;

	yonk_intent_seq_init (&s);

	while ((e = yonk_intent_seq_dequeue (&o->seq)) != NULL)
		if (yonk_intent_match (e, argc, argv))
			yonk_intent_free (e);
		else
			yonk_intent_seq_enqueue (&s, e);

	yonk_intent_seq_move (&s, &o->seq);
	return 1;
}
