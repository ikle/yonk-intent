/*
 * Yonk Ossa: Tree Database Skeleton
 *
 * Copyright (c) 2022-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef YONK_OSSA_INT_H
#define YONK_OSSA_INT_H  1

#include <string.h>

#include <capsa/tree.h>
#include <yonk/ossa.h>

TREE_DECLARE_TYPE (yonk_ossa_node)

struct yonk_ossa {
	struct yonk_ossa_node_tree set;
};

struct yonk_ossa_node {
	struct avl node;
	struct yonk_ossis data;
	struct yonk_ossa childs;
	long offset;  			/* in-file ossis sequence address */
};

struct yonk_ossa_node *yonk_ossa_node_alloc (const char *name);
void yonk_ossa_node_free (struct yonk_ossa_node *o);

static inline
int yonk_ossa_node_order (const char *key, const struct yonk_ossa_node *o)
{
	return strcmp (key, o->data.name);
}

TREE_DECLARE_CORE (yonk_ossa_node)

#endif  /* YONK_OSSA_INT_H */
