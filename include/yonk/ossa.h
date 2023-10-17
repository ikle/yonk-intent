/*
 * Yonk Ossa: Tree Database Skeleton
 *
 * Copyright (c) 2022-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef YONK_OSSA_H
#define YONK_OSSA_H  1

#include <stdio.h>

struct yonk_ossa *yonk_ossa_alloc (void);
void yonk_ossa_free (struct yonk_ossa *o);

struct yonk_ossa *yonk_ossa_read (const char *path);
int yonk_ossa_write (struct yonk_ossa *o, const char *path);

struct yonk_ossis *yonk_ossa_lookup (struct yonk_ossa *o, const char *name);
struct yonk_ossis *yonk_ossa_insert (struct yonk_ossa *o, const char *name,
				     int kind, int single);
void yonk_ossa_remove (struct yonk_ossa *o, const char *name);

enum yonk_kind {
	YONK_GROUP = 0,
	YONK_NODE,
	YONK_TAG,
	YONK_ATTR,
	YONK_VALUE,
	YONK_FLAG,
};

struct yonk_ossis {
	char *name;
	char kind, single;
	struct yonk_ossa *childs;
};

void yonk_ossa_show (struct yonk_ossa *o, FILE *to);

#endif  /* YONK_OSSA_H */
