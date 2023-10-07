/*
 * Yonk Rib: Low-Level State and Configuration Node
 *
 * Copyright (c) 2022-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef YONK_RIB_H
#define YONK_RIB_H  1

#include <stdio.h>
#include <string.h>

#include <capsa/tree.h>

enum yonk_kind {
	YONK_GROUP = 0,
	YONK_NODE,
	YONK_TAG,
	YONK_ATTR,
	YONK_VALUE,
};

TREE_DECLARE_TYPE (yonk_rib)

struct yonk_rib {
	struct yonk_rib *parent;
	struct avl node;
	char kind, mark;
	char *name;
	struct yonk_rib_tree childs;
};

struct yonk_rib *yonk_rib_alloc (const char *name);
void yonk_rib_free (struct yonk_rib *o);

static inline int yonk_rib_order (const char *key, const struct yonk_rib *o)
{
	return strcmp (key, o->name);
}

TREE_DECLARE_CORE (yonk_rib)

void yonk_rib_show (struct yonk_rib *o, FILE *to);

static inline
struct yonk_rib *yonk_rib_lookup (struct yonk_rib *o, const char *name)
{
	return yonk_rib_tree_lookup (&o->childs, name);
}

static inline
struct yonk_rib *yonk_rib_insert (struct yonk_rib *o, int kind, const char *name)
{
	struct yonk_rib *n;

	if ((n = yonk_rib_tree_insert (&o->childs, name)) == NULL)
		return n;

	n->parent = o;
	n->kind = kind;
	return n;
}

static inline void yonk_rib_remove (struct yonk_rib *o, const char *name)
{
	yonk_rib_free (yonk_rib_tree_remove (&o->childs, name));
}

#endif  /* YONK_RIB_H */
