/*
 * Yonk Ossa Allocator
 *
 * Copyright (c) 2022-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdlib.h>

#include "yonk-ossa-int.h"

struct yonk_ossa *yonk_ossa_alloc (void)
{
	struct yonk_ossa *o;

	if ((o = malloc (sizeof (*o))) == NULL)
		return o;

	yonk_ossa_node_tree_init (&o->set);
	return o;
}

void yonk_ossa_free (struct yonk_ossa *o)
{
	if (o == NULL)
		return;

	yonk_ossa_node_tree_fini (&o->set);
}
