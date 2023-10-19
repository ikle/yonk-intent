/*
 * Yonk Ossa Reader
 *
 * Copyright (c) 2022-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "yonk-ossa-int.h"

static int read_le32 (FILE *from, long *to)
{
	unsigned char s[4];

	if (fread (s, sizeof (s), 1, from) != 1)
		return 0;

	*to = (s[0] << 0) | (s[1] << 8) | (s[2] << 16) | (s[3] << 24);
	return 1;
}

static int check_le32 (long a, long b)
{
	return a == b ? 1 : (errno = EPROTO, 0);
}

static int yonk_ossa_pull_childs (struct yonk_ossa *o, FILE *from);

static int yonk_ossa_pull (struct yonk_ossa *o, FILE *from, long pos)
{
	int len, kind, single;
	char name[256];
	struct yonk_ossa_node *n;

	if (fseek (from, pos, SEEK_SET) != 0)
		return 0;

	for (;;) {
		if ((len = fgetc (from)) == EOF)  /* assume UCHAR_MAX < 256 */
			return 0;

		if (len == 0)
			break;

		if (fread (name, len, 1, from) != 1 ||
		    (kind   = fgetc (from)) == EOF ||
		    (single = fgetc (from)) == EOF)
			return 0;

		name[len] = '\0';

		if ((n = yonk_ossa_node_tree_insert (&o->set, name)) == NULL ||
		    !read_le32 (from, &n->offset))
			return 0;

		n->data.kind   = kind;
		n->data.single = single;
	}

	return yonk_ossa_pull_childs (o, from);
}

struct ctx {
	int ok;
	FILE *from;
};

static void yonk_ossa_node_pull_childs (struct yonk_ossa_node *o, void *cookie)
{
	struct ctx *c = cookie;

	if (o->offset != 0)
		c->ok = yonk_ossa_pull (&o->childs, c->from, o->offset);
}

TREE_DECLARE_WALK (yonk_ossa_node, pull_childs)

static int yonk_ossa_pull_childs (struct yonk_ossa *o, FILE *from)
{
	struct ctx c = { 1, from };

	yonk_ossa_node_tree_pull_childs (&o->set, &c);

	return c.ok;
}

struct yonk_ossa *yonk_ossa_read (const char *path)
{
	struct yonk_ossa *o;
	FILE *from;
	long x;

	if ((from = fopen (path, "rb")) == NULL)
		return NULL;

	if ((o = yonk_ossa_alloc ()) == NULL)
		goto no_ossa;

	if (!read_le32 (from, &x) || !check_le32 (x, 0x6173736f))
		goto no_read;

	if (fseek (from, -4, SEEK_END) != 0 || !read_le32 (from, &x) ||
	    !yonk_ossa_pull (o, from, x))
		goto no_read;

	fclose (from);
	return o;
no_read:
	yonk_ossa_free (o);
no_ossa:
	fclose (from);
	return NULL;
}
