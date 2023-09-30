/*
 * Yonk Patch Show
 *
 * Copyright (c) 2022-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <yonk/patch.h>

int yonk_patch_show (struct yonk_patch *o, FILE *to, int json)
{
	struct yonk_intent *e = o->seq.head;

	if (json && fputc ('[', to) == EOF)
		return 0;

	if (e != NULL) {
		if (!yonk_intent_show (e, to, json))
			return 0;

		for (e = e->next; e != NULL; e = e->next) {
			if (json && fputc (',', to) == EOF)
				return 0;

			if (!yonk_intent_show (e, to, json))
				return 0;
		}
	}

	if (json && fputc (']', to) == EOF)
		return 0;

	return 1;
}
