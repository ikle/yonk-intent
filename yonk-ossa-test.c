/*
 * Yonk Ossa Test
 *
 * Copyright (c) 2022-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdio.h>
#include <yonk/ossa.h>

static int die (struct yonk_ossa *o, const char *prefix)
{
	perror (prefix);
	yonk_ossa_free (o);
	return 1;
}

static int test_add (struct yonk_ossa *o)
{
	struct yonk_ossis *n;

#define ADD  yonk_ossa_insert
	return	(n = ADD (o, "interfaces", YONK_GROUP, 0))	!= NULL &&
		(n = ADD (n->childs, "ethernet", YONK_NODE, 0))	!= NULL &&
		ADD (n->childs, "description", YONK_ATTR, 1)	!= NULL &&
		ADD (n->childs, "address", YONK_ATTR, 0)	!= NULL &&
		ADD (n->childs, "mtu", YONK_ATTR, 1)		!= NULL &&
		(n = ADD (o, "system", YONK_GROUP, 0))		!= NULL &&
		ADD (n->childs, "host-name", YONK_ATTR, 1)	!= NULL;
#undef ADD
}

int main (int argc, char *argv[])
{
	struct yonk_ossa *o;

	if ((o = yonk_ossa_alloc ()) == NULL)
		return die (o, "E: ossa alloc");

	if (!test_add (o))
		return die (o, "E: ossa insert");

	yonk_ossa_show (o, stdout);

	if (!yonk_ossa_write (o, "yonk-ossa-test.db"))
		return die (o, "E: ossa write");

	yonk_ossa_free (o);
	return 0;
}
