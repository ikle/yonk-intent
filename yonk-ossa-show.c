/*
 * Yonk Ossa Show
 *
 * Copyright (c) 2022-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "yonk-ossa-int.h"

struct ctx {
	FILE *to;
	int level;
};

static void indent (struct ctx *c)
{
	int i;

	for (i = c->level; i > 0; --i)
		fputc ('\t', c->to);
}

static void yonk_ossa_node_tree_show (struct yonk_ossa_node_tree *o, void *c);

static void yonk_ossa_node_show (struct yonk_ossa_node *o, void *cookie)
{
	struct ctx *c = cookie, next = { c->to, c->level + 1 };
	const char *kind;

	switch (o->data.kind) {
	case YONK_GROUP:  kind = "group"; break;
	case YONK_NODE:   kind = o->data.single ? "node" : "nodes"; break;
	case YONK_ATTR:   kind = o->data.single ? "attr" : "attrs"; break;
	case YONK_FLAG:   kind = "flag"; break;
	}

	switch (o->data.kind) {
	case YONK_GROUP:
	case YONK_NODE:
		indent (c); fprintf (c->to, "%s %s {\n", kind, o->data.name);
		yonk_ossa_node_tree_show (&o->childs.set, &next);
		indent (c); fprintf (c->to, "}\n");
		return;
	case YONK_ATTR:
	case YONK_FLAG:
		indent (c); fprintf (c->to, "%s %s\n", kind, o->data.name);
		return;
	}
}

TREE_DECLARE_WALK (yonk_ossa_node, show)

void yonk_ossa_show (struct yonk_ossa *o, FILE *to)
{
	struct ctx next = { to, 0 };

	yonk_ossa_node_tree_show (&o->set, &next);
}
