/*
 * Copyright (c) 2015 University of York.
 * Hesham ALMatary <hmka501@york.ac.uk>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
#include <bsp/linker-symbols.h>
#include <rtems/asm.h>

EXTERN(bsp_section_bss_begin)
EXTERN(bsp_section_bss_end)
EXTERN(ISR_Handler)
EXTERN(bsp_start_vector_table_end)
EXTERN(bsp_start_vector_table_size)
EXTERN(bsp_vector_table_size)
EXTERN(bsp_section_stack_begin)

PUBLIC(RISCV_Exception_default)
PUBLIC(bsp_start_vector_table_begin)
PUBLIC(start)

.section .vector, "wax"
TYPE_FUNC(start)
SYM(start):

_bsp_start_vector_table_begin:
  .word .normal_start /* Reset */
  .word _RISCV_Exception_default /* SW exception */
  .word _RISCV_Exception_default /* Data Page Fault */
  .word _RISCV_Exception_default /* Timer 0 */
  .word _RISCV_Exception_default /* Timer 1 */
  .word _RISCV_Exception_default /* Message int */
  .word _RISCV_Exception_default /* DMA0 int */
  .word _RISCV_Exception_default /* DMA1 int */
  .word _RISCV_Exception_default /* WAND */
  .word _RISCV_Exception_default /* User interrupt */

_bsp_start_vector_table_end:

.size  _start, .-_start

.section .start,"ax"
.align  4
.type   _external_start, %function
.normal_start:

.size  .normal_start, .-.normal_start

.balign 4
TYPE_FUNC(RISCV_Exception_default)
SYM(RISCV_Exception_default):
  nop
