/*
 * Yonk Intent Test
 *
 * Copyright (c) 2022-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <yonk/intent.h>

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a)  (sizeof (a) / sizeof ((a)[0]))
#endif

int main (int argc, char *argv[])
{
	char *cmd[] = { "interfaces", "ethernet", "eth1", "mtu", "1400" };
	struct yonk_intent *o;
	FILE *db;

	if ((o = yonk_intent_alloc ('+', ARRAY_SIZE (cmd), cmd)) == NULL) {
		perror ("E: intent alloc");
		return 1;
	}

	yonk_intent_show (o, stdout, 0);
	yonk_intent_show (o, stdout, 1); putchar ('\n');

	if ((db = fopen ("yonk-intent-test.db", "wb")) == NULL) {
		perror ("E: open database");
		yonk_intent_free (o);
		return 1;
	}

	if (!yonk_intent_write (o, db)) {
		perror ("E: intent write");
		fclose (db);
		yonk_intent_free (o);
		return 1;
	}

	fclose (db);
	yonk_intent_free (o);

	if ((db = fopen ("yonk-intent-test.db", "rb")) == NULL) {
		perror ("E: open database");
		return 1;
	}

	if ((o = yonk_intent_read (db)) == NULL) {
		perror ("E: intent read");
		fclose (db);
		return 1;
	}

	fclose (db);
	yonk_intent_show (o, stdout, 0);
	yonk_intent_show (o, stdout, 1); putchar ('\n');
	yonk_intent_free (o);
	return 0;
}
