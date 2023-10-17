/*
 * Yonk Ossa Insert
 *
 * Copyright (c) 2022-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "yonk-ossa-int.h"

struct yonk_ossis *
yonk_ossa_insert (struct yonk_ossa *o, const char *name, int kind, int single)
{
	struct yonk_ossa_node *n;

	if ((n = yonk_ossa_node_tree_insert (&o->set, name)) == NULL)
		return NULL;

	n->data.kind   = kind;
	n->data.single = single;

	return &n->data;
}
