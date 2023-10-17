/*
 * Yonk Ossa Write
 *
 * Copyright (c) 2022-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <errno.h>
#include <string.h>

#include "yonk-ossa-int.h"

static int write_string (const char *s, FILE *to)
{
	size_t len;

	if ((len = strlen (s)) > 255 || len <= 0) {
		errno = EPROTO;
		return 0;
	}

	return	fputc (len, to) != EOF && fputs (s, to) != EOF;
}

static int write_le32 (long x, FILE *to)
{
	unsigned char a = (x >>  0) & 0xff, b = (x >>  8) & 0xff;
	unsigned char c = (x >> 16) & 0xff, d = (x >> 24) & 0xff;

	return	fputc (a, to) != EOF && fputc (b, to) != EOF &&
		fputc (c, to) != EOF && fputc (d, to) != EOF;
}

struct ctx {
	int ok;
	FILE *to;
};

static long yonk_ossa_push (struct yonk_ossa *o, struct ctx *c);

static void yonk_ossa_node_push_childs (struct yonk_ossa_node *o, void *cookie)
{
	struct ctx *c = cookie;

	o->offset = yonk_ossa_push (&o->childs, c);
}

static void yonk_ossa_node_push (struct yonk_ossa_node *o, void *cookie)
{
	struct ctx *c = cookie;

	c->ok =	c->ok && write_string (o->data.name, c->to) &&
		fputc (o->data.kind, c->to) != EOF &&
		fputc (o->data.single, c->to) != EOF &&
		write_le32 (o->offset, c->to);
}

TREE_DECLARE_WALK (yonk_ossa_node, push_childs)
TREE_DECLARE_WALK (yonk_ossa_node, push)

static long yonk_ossa_push (struct yonk_ossa *o, struct ctx *c)
{
	long head;

	if (yonk_ossa_node_tree_is_empty (&o->set))
		return 0;

	yonk_ossa_node_tree_push_childs (&o->set, c);

	head = ftell (c->to);
	yonk_ossa_node_tree_push (&o->set, c);
	c->ok = c->ok && fputc (0, c->to) != EOF;

	return head;
}

int yonk_ossa_write (struct yonk_ossa *o, const char *path)
{
	struct ctx c = { 1 };
	long root;

	if ((c.to = fopen (path, "wb")) == NULL)
		return 0;

	c.ok = fwrite ("ossa", 4, 1, c.to) == 1;
	root = yonk_ossa_push (o, &c);
	c.ok = c.ok && write_le32 (root, c.to) != EOF;

	if (fclose (c.to) == 0 && c.ok)
		return 1;

	(void) remove (path);
	return 0;
}
