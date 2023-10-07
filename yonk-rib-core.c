/*
 * Yonk Rib Core
 *
 * Copyright (c) 2022-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdlib.h>

#include <yonk/rib.h>

struct yonk_rib *yonk_rib_alloc (const char *name)
{
	struct yonk_rib *o;

	if ((o = malloc (sizeof (*o))) == NULL)
		return o;

	if ((o->name = strdup (name)) == NULL) {
		free (o);
		return NULL;
	}

	o->parent = NULL;
	o->kind = YONK_GROUP;
	o->mark = ' ';
	yonk_rib_tree_init (&o->childs);
	return o;
}

void yonk_rib_free (struct yonk_rib *o)
{
	if (o == NULL)
		return;

	yonk_rib_tree_fini (&o->childs);
	free (o->name);
	free (o);
}
