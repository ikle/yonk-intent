/*
 * Yonk Patch Constructor
 *
 * Copyright (c) 2022-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdlib.h>

#include <yonk/patch.h>

struct yonk_patch *yonk_patch_alloc (void)
{
	struct yonk_patch *o;

	if ((o = malloc (sizeof (*o))) == NULL)
		return o;

	yonk_intent_seq_init (&o->seq);
	return o;
}

void yonk_patch_free (struct yonk_patch *o)
{
	if (o == NULL)
		return;

	yonk_intent_seq_fini (&o->seq);
	free (o);
}
