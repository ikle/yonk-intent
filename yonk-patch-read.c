/*
 * Yonk Patch Reader
 *
 * Copyright (c) 2022-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "yonk-patch-int.h"

struct yonk_patch *yonk_patch_read (const char *path)
{
	struct yonk_patch *o;
	struct yonk_intent *e;
	FILE *from;

	if ((from = fopen (path, "rb")) == NULL)
		return 0;

	if ((o = yonk_patch_alloc ()) == NULL)
		goto no_patch;

	while ((e = yonk_intent_read (from)) != NULL)
		yonk_intent_seq_enqueue (&o->seq, e);

	if (ferror (from))
		goto no_read;

	fclose (from);
	return o;
no_read:
	yonk_patch_free (o);
no_patch:
	fclose (from);
	return NULL;
}
