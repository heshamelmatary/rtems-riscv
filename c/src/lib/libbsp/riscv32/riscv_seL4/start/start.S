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

# define LREG lw
# define SREG sw

EXTERN(bsp_section_bss_begin)
EXTERN(bsp_section_bss_end)
EXTERN(ISR_Handler)
EXTERN(bsp_start_vector_table_end)
EXTERN(bsp_start_vector_table_size)
EXTERN(bsp_vector_table_size)
EXTERN(bsp_section_stack_begin)

PUBLIC(RISCV_Exception_default)
PUBLIC(bsp_start_vector_table_begin)
PUBLIC(_start)

.section .vector, "ax"
/* 0x100 user-level trap */
  mrts
  #la s0, 0xF0000000
  #jr  s0
/* 0x140 supervisor level trap */
  .align 6
  #mrts
  la s0, trap_entry
  jr s0
/* 0x1C0 Machine level trap */
  .align 6
  la s0, trap_entry
  jr s0
/* 0x1FC external interrupt */
  .align 6
  la s0, trap_entry
  jr s0
/* 0x200 reset */
  .align 6
  la s0, _start
  jr s0

.section .start, "wax"
TYPE_FUNC(_start)
SYM(_start):
  li x2, 0
  li x3, 0
  li x4, 0
  li x5, 0
  li x6, 0
  li x7, 0
  li x8, 0
  li x9, 0
  li x10,0
  li x11,0
  li x12,0
  li x13,0
  li x14,0
  li x15,0
  li x16,0
  li x17,0
  li x18,0
  li x19,0
  li x20,0
  li x21,0
  li x22,0
  li x23,0
  li x24,0
  li x25,0
  li x26,0
  li x27,0
  li x28,0
  li x29,0
  li x30,0
  li x31,0

  /* load stack and frame pointers */
  la sp, bsp_section_stack_begin

/* Clearing .bss */
  la t0, bsp_section_bss_begin
  la t1, bsp_section_bss_end

_loop_clear_bss:
  bge t0, t1, _end_clear_bss
  addi  t0, t0, 4
  sw    x0, 0(t0)
  j     _loop_clear_bss
  nop
_end_clear_bss:

  j boot_card
  nop

bsp_start_vector_table_begin:
  .word .normal_start /* Reset */
  .word RISCV_Exception_default /* SW exception */
  .word RISCV_Exception_default /* Data Page Fault */
  .word RISCV_Exception_default /* Timer 0 */
  .word RISCV_Exception_default /* Timer 1 */
  .word RISCV_Exception_default /* Message int */
  .word RISCV_Exception_default /* DMA0 int */
  .word RISCV_Exception_default /* DMA1 int */
  .word RISCV_Exception_default /* WAND */
  .word RISCV_Exception_default /* User interrupt */

bsp_start_vector_table_end:


.section .start,"ax"
.align  4
.type   _external_start, %function
.normal_start:

.balign 4
TYPE_FUNC(RISCV_Exception_default)
SYM(RISCV_Exception_default):
  nop
trap_entry:
	nop
  addi sp, sp, -272
  SREG x1, 8(sp)
  SREG x2, 16(sp)
  SREG x3, 24(sp)
  SREG x4, 32(sp)
  SREG x5, 40(sp)
  SREG x6, 48(sp)
  SREG x7, 56(sp)
  SREG x8, 64(sp)
  SREG x9, 72(sp)
  SREG x10, 80(sp)
  SREG x11, 88(sp)
  SREG x12, 96(sp)
  SREG x13, 104(sp)
  SREG x14, 112(sp)
  SREG x15, 120(sp)
  SREG x16, 128(sp)
  SREG x17, 136(sp)
  SREG x18, 144(sp)
  SREG x19, 152(sp)
  SREG x20, 160(sp)
  SREG x21, 168(sp)
  SREG x22, 176(sp)
  SREG x23, 184(sp)
  SREG x24, 192(sp)
  SREG x25, 200(sp)
  SREG x26, 208(sp)
  SREG x27, 216(sp)
  SREG x28, 224(sp)
  SREG x29, 232(sp)
  SREG x30, 240(sp)
  SREG x31, 248(sp)

  csrr a0, mcause
  csrr a1, mepc
  mv a2, sp
  jal handle_trap
  csrw mepc, a0

  LREG x1, 8(sp)
  LREG x2, 16(sp)
  LREG x3, 24(sp)
  LREG x4, 32(sp)
  LREG x5, 40(sp)
  LREG x6, 48(sp)
  LREG x7, 56(sp)
  LREG x8, 64(sp)
  LREG x9, 72(sp)
  LREG x10, 80(sp)
  LREG x11, 88(sp)
  LREG x12, 96(sp)
  LREG x13, 104(sp)
  LREG x14, 112(sp)
  LREG x15, 120(sp)
  LREG x16, 128(sp)
  LREG x17, 136(sp)
  LREG x18, 144(sp)
  LREG x19, 152(sp)
  LREG x20, 160(sp)
  LREG x21, 168(sp)
  LREG x22, 176(sp)
  LREG x23, 184(sp)
  LREG x24, 192(sp)
  LREG x25, 200(sp)
  LREG x26, 208(sp)
  LREG x27, 216(sp)
  LREG x28, 224(sp)
  LREG x29, 232(sp)
  LREG x30, 240(sp)
  LREG x31, 248(sp)

  addi sp, sp, 272

  eret
