/*
 * Yonk Patch
 *
 * Copyright (c) 2022-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef YONK_PATCH_H
#define YONK_PATCH_H  1

#include <stdio.h>
#include <yonk/intent.h>

struct yonk_patch *yonk_patch_alloc (void);
void yonk_patch_free (struct yonk_patch *o);

struct yonk_patch *yonk_patch_read (const char *path);
int yonk_patch_write (struct yonk_patch *o, const char *path);

struct yonk_intent *yonk_patch_first (struct yonk_patch *o);

int yonk_patch_drop (struct yonk_patch *o, int argc, char *argv[]);
int yonk_patch_add  (struct yonk_patch *o, int argc, char *argv[], int alone);
int yonk_patch_del  (struct yonk_patch *o, int argc, char *argv[]);

int yonk_patch_show (struct yonk_patch *o, FILE *to, int json);

#endif  /* YONK_PATCH_H */
