/*
 * Yonk Ossa Core
 *
 * Copyright (c) 2022-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdlib.h>

#include "yonk-ossa-int.h"

struct yonk_ossa_node *yonk_ossa_node_alloc (const char *name)
{
	struct yonk_ossa_node *o;

	if ((o = malloc (sizeof (*o))) == NULL)
		return o;

	if ((o->data.name = strdup (name)) == NULL) {
		free (o);
		return NULL;
	}

	yonk_ossa_node_tree_init (&o->childs.set);
	o->data.childs = &o->childs;
	o->offset = 0;
	return o;
}

void yonk_ossa_node_free (struct yonk_ossa_node *o)
{
	if (o == NULL)
		return;

	yonk_ossa_node_tree_fini (&o->childs.set);
	free (o->data.name);
	free (o);
}
