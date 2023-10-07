/*
 * Yonk Rib Show
 *
 * Copyright (c) 2022-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <yonk/rib.h>

struct ctx {
	FILE *to;
	int level;
};

static void indent (struct yonk_rib *o, struct ctx *c)
{
	int i;

	fprintf (c->to, "%c ", o->mark);

	for (i = c->level; i > 0; --i)
		fputs ("    ", c->to);
}

static void yonk_rib_tree_emit (struct yonk_rib_tree *o, void *cookie);

static void yonk_rib_emit_attr (struct yonk_rib *o, void *cookie)
{
	struct ctx *c = cookie;

	indent (o, c); fprintf (c->to, "%s = %s\n", o->parent->name, o->name);
}

static void yonk_rib_emit_node (struct yonk_rib *o, void *cookie)
{
	struct ctx *c = cookie, next = { c->to, c->level + 1 };

	indent (o, c); fprintf (c->to, "%s %s {\n", o->parent->name, o->name);
	yonk_rib_tree_emit (&o->childs, &next);
	indent (o, c); fprintf (c->to, "}\n");
}

static void yonk_rib_emit_group (struct yonk_rib *o, void *cookie)
{
	struct ctx *c = cookie, next = { c->to, c->level + 1 };

	indent (o, c); fprintf (c->to, "%s {\n", o->name);
	yonk_rib_tree_emit (&o->childs, &next);
	indent (o, c); fprintf (c->to, "}\n");
}

TREE_DECLARE_WALK (yonk_rib, emit_attr)
TREE_DECLARE_WALK (yonk_rib, emit_node)

static void yonk_rib_emit (struct yonk_rib *o, void *cookie)
{
	switch (o->kind) {
	case YONK_GROUP:
		yonk_rib_emit_group (o, cookie);
		break;
	case YONK_NODE:
		yonk_rib_tree_emit_node (&o->childs, cookie);
		break;
	case YONK_ATTR:
		yonk_rib_tree_emit_attr (&o->childs, cookie);
		break;
	}
}

TREE_DECLARE_WALK (yonk_rib, emit)

void yonk_rib_show (struct yonk_rib *o, FILE *to)
{
	struct ctx next = { to, 0 };

	yonk_rib_tree_emit (&o->childs, &next);
}
