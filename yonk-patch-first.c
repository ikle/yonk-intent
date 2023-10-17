/*
 * Yonk Patch Iteration
 *
 * Copyright (c) 2022-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdlib.h>

#include "yonk-patch-int.h"

struct yonk_intent *yonk_patch_first (struct yonk_patch *o)
{
	return o->seq.head;
}
