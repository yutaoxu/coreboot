/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2011 Advanced Micro Devices, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

/******************************************************************************
 * $Workfile:: cache_as_ram.S
 *
 * Description: CAR setup called from bootblock_crt0.S.
 *
 ******************************************************************************
 */

#include "gcccar.inc"
#include <cpu/x86/cache.h>
#include <cpu/x86/post_code.h>

/*
 * on entry:
 *   mm0: BIST (ignored)
 *   mm2_mm1: timestamp at bootblock_protected_mode_entry
 */

.global bootblock_pre_c_entry
bootblock_pre_c_entry:

	post_code(0xa0)

	AMD_ENABLE_STACK

	/* Align the stack and keep aligned for call to bootblock_c_entry() */
	and	$0xfffffff0, %esp
	sub	$8, %esp

	movd	%mm2, %eax
	pushl	%eax		/* tsc[63:32] */
	movd	%mm1, %eax
	pushl	%eax		/* tsc[31:0] */

before_carstage:
	post_code(0xa2)

	call	bootblock_c_entry
	/* Never reached */

.halt_forever:
	post_code(POST_DEAD_CODE)
	hlt
	jmp	.halt_forever
