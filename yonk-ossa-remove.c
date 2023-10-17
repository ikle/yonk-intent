/*
 * Yonk Ossa Remove
 *
 * Copyright (c) 2022-2023 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "yonk-ossa-int.h"

void yonk_ossa_remove (struct yonk_ossa *o, const char *name)
{
	yonk_ossa_node_free (yonk_ossa_node_tree_remove (&o->set, name));
}
