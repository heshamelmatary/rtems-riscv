/*
 * Copyright (c) 2015 University of York.
 * Hesham ALMatary <hmka501@york.ac.uk>
 *
 * Copyright (c) 2017 Denis Obrezkov <denisobrezkov@gmail.com>
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

#define CLINT_BASE 0x02000000
#define MTIME_OFFSET 0xBFF8
#define MTIMECMP_OFFSET 0x4000
#define MTIME_REG CLINT_BASE+MTIME_OFFSET
#define MTIMECMP CLINT_BASE+MTIMECMP_OFFSET

#define MSTATUS_MIE 0x8

#define MIE_ENABLE_ALL 0x888

#define REGBYTES 4

EXTERN(bsp_section_bss_begin)
EXTERN(bsp_section_bss_end)
EXTERN(ISR_Handler)
EXTERN(bsp_start_vector_table_end)
EXTERN(bsp_start_vector_table_size)
EXTERN(bsp_vector_table_size)
EXTERN(bsp_section_stack_begin)

.balign 4
PUBLIC(RISCV_Exception_default)
/* PUBLIC(bsp_start_vector_table_begin) */ 
PUBLIC(_start)

.section .start, "wax"
TYPE_FUNC(_start)
SYM(_start):
  li x1, 0
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
_end_clear_bss:

/* Copy data */
  la t0, _copy_start
  la t1, _copy_end
  la t3, __data_start_rom

_loop_copy_data:
  bge t0, t1, _end_copy_data
  lw  t4, 0(t3)
  sw   t4, 0(t0)
  addi t0, t0, 4
  addi t3, t3, 4
  j    _loop_copy_data
_end_copy_data:
  
/* 
 * Examples of generating clock and software interrupts.
 * Interrupts won't be generated because they are turned off
 */
irq_gen:
  li t2, MTIME_REG
  /* 
   * We want to place a big value in comparator to make timer interrupts
   * be not generated right after turning them on
   */  
  li t4, 0xfffff
  lw t0, 0(t2)
  add t0, t0, t4
  li t3, MTIMECMP 
  sw t0, 0(t3)

/* copy MSB of mtime */
  addi t3, t3, 4
  addi t2, t2, 4
  lw t0, 0(t2)
  sw t0, 0(t3)
  
/* Enable interrupts in mie register (not enabled in mstatus yet) */
  la t0, RISCV_Exception_default
  csrw mtvec, t0
  csrci mstatus, MSTATUS_MIE
  li t0, MIE_ENABLE_ALL
  csrs mie, t0

  call boot_card
  nop

bsp_start_vector_table_begin:

  .word RISCV_Exception_default /* bad_trap */
#define TRAP_FROM_MACHINE_MODE_VECTOR 13
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
  csrci mstatus, MSTATUS_MIE
  addi sp, sp, -34*REGBYTES
  SREG x1, 1*REGBYTES(sp)
  SREG x2, 2*REGBYTES(sp)
  SREG x3, 3*REGBYTES(sp)
  SREG x4, 4*REGBYTES(sp)
  SREG x5, 5*REGBYTES(sp)
  SREG x6, 6*REGBYTES(sp)
  SREG x7, 7*REGBYTES(sp)
  SREG x8, 8*REGBYTES(sp)
  SREG x9, 9*REGBYTES(sp)
  SREG x10, 10*REGBYTES(sp)
  SREG x11, 11*REGBYTES(sp)
  SREG x12, 12*REGBYTES(sp)
  SREG x13, 13*REGBYTES(sp)
  SREG x14, 14*REGBYTES(sp)
  SREG x15, 15*REGBYTES(sp)
  SREG x16, 16*REGBYTES(sp)
  SREG x17, 17*REGBYTES(sp)
  SREG x18, 18*REGBYTES(sp)
  SREG x19, 19*REGBYTES(sp)
  SREG x20, 20*REGBYTES(sp)
  SREG x21, 21*REGBYTES(sp)
  SREG x22, 22*REGBYTES(sp)
  SREG x23, 23*REGBYTES(sp)
  SREG x24, 24*REGBYTES(sp)
  SREG x25, 25*REGBYTES(sp)
  SREG x26, 26*REGBYTES(sp)
  SREG x27, 27*REGBYTES(sp)
  SREG x28, 28*REGBYTES(sp)
  SREG x29, 29*REGBYTES(sp)
  SREG x30, 30*REGBYTES(sp)
  SREG x31, 31*REGBYTES(sp)
  
  csrr t0, mepc
  SREG t0, 32*REGBYTES(sp)

  csrr t0, mcause
  SREG t0, 33*REGBYTES(sp)

  mv   a0, t0
  call handle_trap

  LREG t0, 32*REGBYTES(sp)
  csrw mepc, t0
 
  LREG t0, 33*REGBYTES(sp)
  csrw mcause, t0

  LREG x1, 1*REGBYTES(sp)
  LREG x2, 2*REGBYTES(sp)
  LREG x3, 3*REGBYTES(sp)
  LREG x4, 4*REGBYTES(sp)
  LREG x5, 5*REGBYTES(sp)
  LREG x6, 6*REGBYTES(sp)
  LREG x7, 7*REGBYTES(sp)
  LREG x8, 8*REGBYTES(sp)
  LREG x9, 9*REGBYTES(sp)
  LREG x10, 10*REGBYTES(sp)
  LREG x11, 11*REGBYTES(sp)
  LREG x12, 12*REGBYTES(sp)
  LREG x13, 13*REGBYTES(sp)
  LREG x14, 14*REGBYTES(sp)
  LREG x15, 15*REGBYTES(sp)
  LREG x16, 16*REGBYTES(sp)
  LREG x17, 17*REGBYTES(sp)
  LREG x18, 18*REGBYTES(sp)
  LREG x19, 19*REGBYTES(sp)
  LREG x20, 20*REGBYTES(sp)
  LREG x21, 21*REGBYTES(sp)
  LREG x22, 22*REGBYTES(sp)
  LREG x23, 23*REGBYTES(sp)
  LREG x24, 24*REGBYTES(sp)
  LREG x25, 25*REGBYTES(sp)
  LREG x26, 26*REGBYTES(sp)
  LREG x27, 27*REGBYTES(sp)
  LREG x28, 28*REGBYTES(sp)
  LREG x29, 29*REGBYTES(sp)
  LREG x30, 30*REGBYTES(sp)
  LREG x31, 31*REGBYTES(sp) 
  
  addi sp, sp, 34*REGBYTES

  csrsi mstatus, MSTATUS_MIE

  mret
