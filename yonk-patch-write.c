/*
 * Yonk Patch Writer
 *
 * Copyright (c) 2022-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <yonk/patch.h>

int yonk_patch_write (struct yonk_patch *o, const char *path)
{
	struct yonk_intent *e;
	FILE *to;

	if ((to = fopen (path, "wb")) == NULL)
		return 0;

	for (e = o->seq.head; e != NULL; e = e->next)
		if (!yonk_intent_write (e, to)) {
			fclose (to);
			goto error;
		}

	if (fclose (to) == 0)
		return 1;
error:
	(void) remove (path);
	return 0;
}
