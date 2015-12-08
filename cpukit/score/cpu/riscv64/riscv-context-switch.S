/*
 * RISCV CPU Dependent Source
 *
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

#ifdef HAVE_CONFIG_H
  #include "config.h"
#endif

#include <rtems/asm.h>

.section .text,"ax"
.align 4

# define LREG lw
# define SREG sw

PUBLIC(_CPU_Context_switch)
PUBLIC(_CPU_Context_restore)
PUBLIC(_CPU_Context_restore_fp)
PUBLIC(_CPU_Context_save_fp)
PUBLIC(restore)

SYM(_CPU_Context_switch):
  /* Disable interrupts and store all registers */
  SREG x1, 4(a0)
  SREG x2, 8(a0)
  SREG x3, 12(a0)
  SREG x4, 16(a0)
  SREG x5, 20(a0)
  SREG x6, 24(a0)
  SREG x7, 28(a0)
  SREG x8, 32(a0)
  SREG x9, 36(a0)
  SREG x10, 40(a0)
  SREG x11, 44(a0)
  SREG x12, 48(a0)
  SREG x13, 52(a0)
  SREG x14, 56(a0)
  SREG x15, 60(a0)
  SREG x16, 64(a0)
  SREG x17, 68(a0)
  SREG x18, 72(a0)
  SREG x19, 76(a0)
  SREG x20, 80(a0)
  SREG x21, 84(a0)
  SREG x22, 88(a0)
  SREG x23, 92(a0)
  SREG x24, 96(a0)
  SREG x25, 100(a0)
  SREG x26, 104(a0)
  SREG x27, 108(a0)
  SREG x28, 112(a0)
  SREG x29, 116(a0)
  SREG x30, 120(a0)
  SREG x31, 124(a0)

SYM(restore):

  LREG x1, 4(a1)
  LREG x2, 8(a1)
  LREG x3, 12(a1)
  LREG x4, 16(a1)
  LREG x5, 20(a1)
  LREG x6, 24(a1)
  LREG x7, 28(a1)
  LREG x8, 32(a1)
  LREG x9, 36(a1)
  LREG x10, 40(a1)
  //LREG x11, 44(t0)
  LREG x12, 48(a1)
  LREG x13, 52(a1)
  LREG x14, 56(a1)
  LREG x15, 60(a1)
  LREG x16, 64(a1)
  LREG x17, 68(a1)
  LREG x18, 72(a1)
  LREG x19, 76(a1)
  LREG x20, 80(a1)
  LREG x21, 84(a1)
  LREG x22, 88(a1)
  LREG x23, 92(a1)
  LREG x24, 96(a1)
  LREG x25, 100(a1)
  LREG x26, 104(a1)
  LREG x27, 108(a1)
  LREG x28, 112(a1)
  LREG x29, 116(a1)
  LREG x30, 120(a1)
  LREG x31, 124(a1)
	ret

SYM(_CPU_Context_restore):
  mv     a1, a0
  j       restore
  nop

/* No FP support for Epiphany yet */
SYM(_CPU_Context_restore_fp):
  nop

 SYM(_CPU_Context_save_fp):
  nop
