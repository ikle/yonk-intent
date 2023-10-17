/*
 * Yonk Patch Internals
 *
 * Copyright (c) 2022-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef YONK_PATCH_INT_H
#define YONK_PATCH_INT_H  1

#include <capsa/seq.h>
#include <yonk/patch.h>

SEQ_DECLARE (yonk_intent)

struct yonk_patch {
	struct yonk_intent_seq seq;
};

#endif  /* YONK_PATCH_INT_H */
