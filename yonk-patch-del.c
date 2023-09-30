/*
 * Yonk Patch Del
 *
 * Copyright (c) 2022-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <yonk/patch.h>

int yonk_patch_del (struct yonk_patch *o, int argc, char *argv[])
{
	struct yonk_intent *e;

	if (!yonk_patch_drop (o, argc, argv))
		return 0;

	if ((e = yonk_intent_alloc ('-', argc, argv)) == NULL)
		return 0;

	yonk_intent_seq_enqueue (&o->seq, e);
	return 1;
}
