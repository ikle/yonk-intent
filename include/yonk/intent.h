/*
 * Yonk Intents and Patches
 *
 * Copyright (c) 2022-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef YONK_INTENT_H
#define YONK_INTENT_H  1

#include <stdio.h>

struct yonk_intent {
	struct yonk_intent *next;
	int action;
	int argc;
	char **argv;
};

struct yonk_intent *yonk_intent_alloc (int action, int argc, char *argv[]);
struct yonk_intent *yonk_intent_read (FILE *from);

void yonk_intent_free (struct yonk_intent *o);

int yonk_intent_match (struct yonk_intent *o, int argc, char *argv[]);
int yonk_intent_write (struct yonk_intent *o, FILE *to);
int yonk_intent_show  (struct yonk_intent *o, FILE *to, int json);

#endif  /* YONK_INTENT_H */
