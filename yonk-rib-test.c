/*
 * Yonk Rib Test
 *
 * Copyright (c) 2022-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdio.h>

#include <yonk/rib.h>

static struct yonk_rib *add_group (struct yonk_rib *o, const char *name)
{
	return yonk_rib_add (o, YONK_GROUP, name);
}

static
struct yonk_rib *add_node (struct yonk_rib *o, const char *name, const char *tag)
{
	return	(o = yonk_rib_add (o, YONK_NODE, name)) == NULL ? NULL :
		yonk_rib_add (o, YONK_TAG, tag);
}

static int add_attr (struct yonk_rib *o, const char *name, const char *value)
{
	return	(o = yonk_rib_add (o, YONK_ATTR, name)) != NULL &&
		yonk_rib_add (o, YONK_VALUE, value) != NULL;
}

static int pull_iface_conf (struct yonk_rib *root)
{
	struct yonk_rib *o;

	return	(o = add_group (root, "interfaces"))   != NULL &&
		(o = add_node (o, "ethernet", "eth1")) != NULL &&
		add_attr (o, "mtu", "1400") &&
		add_attr (o, "address", "10.0.30.1/24") &&
		add_attr (o, "address", "10.0.27.1/24") &&
		add_attr (o, "address", "10.0.28.1/24");
}

int main (int argc, char *argv[])
{
	struct yonk_rib *root;

	if ((root = yonk_rib_alloc ("sample tree")) == NULL) {
		perror ("E: root allocation");
		return 1;
	}

	pull_iface_conf (root);

	yonk_rib_show (root, stdout);
	yonk_rib_free (root);
	return 0;
}
