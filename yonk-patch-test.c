/*
 * Yonk Patch Test
 *
 * Copyright (c) 2022-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <yonk/patch.h>

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a)  (sizeof (a) / sizeof ((a)[0]))
#endif

static int test_error (struct yonk_patch *o, const char *prefix)
{
	perror (prefix);
	yonk_patch_free (o);
	return 1;
}

static int test_add (struct yonk_patch *o)
{
	char *s1[] = { "system", "host-name", "test-m" };
	char *a1[] = { "interfaces", "ethernet", "eth1", "address", "10.0.26.2/24" };
	char *a2[] = { "interfaces", "ethernet", "eth1", "address", "10.0.27.2/24" };
	char *m1[] = { "interfaces", "ethernet", "eth1", "mtu", "1300" };
	char *m2[] = { "interfaces", "ethernet", "eth1", "mtu", "1400" };

	return	yonk_patch_add (o, ARRAY_SIZE (s1), s1, 1) &&
		yonk_patch_add (o, ARRAY_SIZE (a1), a1, 0) &&
		yonk_patch_add (o, ARRAY_SIZE (a2), a2, 0) &&
		yonk_patch_add (o, ARRAY_SIZE (m1), m1, 1) &&
		yonk_patch_add (o, ARRAY_SIZE (m2), m2, 1);
}

static int test_show (struct yonk_patch *o)
{
	return	yonk_patch_show (o, stdout, 0) &&
		yonk_patch_show (o, stdout, 1) && putchar ('\n') != EOF;
}

static int test_del (struct yonk_patch *o)
{
	char *d1[] = { "interfaces", "ethernet", "eth1" };
	char *d2[] = { "interfaces", "ethernet", "eth1", "address" };

	return	yonk_patch_del (o, ARRAY_SIZE (d1), d1) && test_show (o) &&
		yonk_patch_del (o, ARRAY_SIZE (d2), d2) && test_show (o);
}

int main (int argc, char *argv[])
{
	struct yonk_patch *o;

	if ((o = yonk_patch_alloc ()) == NULL) {
		perror ("E: patch alloc");
		return 1;
	}

	if (!test_add (o))
		return test_error (o, "E: patch add");

	if (!test_show (o))
		return test_error (o, "E: patch show");

	if (!yonk_patch_write (o, "yonk-patch-test.db"))
		return test_error (o, "E: patch write");

	if (!test_del (o))
		return test_error (o, "E: patch del");

	yonk_patch_free (o);

	if ((o = yonk_patch_read ("yonk-patch-test.db")) == NULL ||
	    !test_show (o))
		return test_error (o, "E: patch read");

	yonk_patch_free (o);
	return 0;
}
