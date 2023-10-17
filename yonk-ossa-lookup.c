/*
 * Yonk Ossa Lookup
 *
 * Copyright (c) 2022-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "yonk-ossa-int.h"

struct yonk_ossis *yonk_ossa_lookup (struct yonk_ossa *o, const char *name)
{
	struct yonk_ossa_node *n;

	if ((n = yonk_ossa_node_tree_lookup (&o->set, name)) == NULL)
		return NULL;

	return &n->data;
}
