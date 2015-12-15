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

#include <bsp.h>
#include <bsp/console-polled.h>
#include <rtems/libio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

/* TODO: move this to riscv-utility */
#define read_csr(reg) ({ unsigned long __tmp; \
  asm volatile ("csrr %0, " #reg : "=r"(__tmp)); \
  __tmp; })

#define write_csr(reg, val) \
  asm volatile ("csrw " #reg ", %0" :: "r"(val))

#define swap_csr(reg, val) ({ long __tmp; \
  asm volatile ("csrrw %0, " #reg ", %1" : "=r"(__tmp) : "r"(val)); \
  __tmp; })

#define set_csr(reg, bit) ({ unsigned long __tmp; \
  if (__builtin_constant_p(bit) && (bit) < 32) \
    asm volatile ("csrrs %0, " #reg ", %1" : "=r"(__tmp) : "i"(bit)); \
  else \
    asm volatile ("csrrs %0, " #reg ", %1" : "=r"(__tmp) : "r"(bit)); \
  __tmp; })

#define clear_csr(reg, bit) ({ unsigned long __tmp; \
  if (__builtin_constant_p(bit) && (bit) < 32) \
    asm volatile ("csrrc %0, " #reg ", %1" : "=r"(__tmp) : "i"(bit)); \
  else \
    asm volatile ("csrrc %0, " #reg ", %1" : "=r"(__tmp) : "r"(bit)); \
  __tmp; })

#define SYS_write 64
#define SYS_exit 93
#define SYS_stats 1234

#define SSTATUS_FS          0x00003000
static void outbyte_console( char );
static char inbyte_console( void );

volatile uint64_t magic_mem[8] __attribute__((aligned(64)));

static long syscall(long num, long arg0, long arg1, long arg2)
{
  register long a7 asm("a7") = num;
  register long a0 asm("a0") = arg0;
  register long a1 asm("a1") = arg1;
  register long a2 asm("a2") = arg2;
  asm volatile ("ecall" : "+r"(a0) : "r"(a1), "r"(a2), "r"(a7));
  return a0;
}

static long handle_frontend_syscall(long which, long arg0, long arg1, long arg2)
{
  magic_mem[0] = which;
  magic_mem[1] = arg0;
  magic_mem[2] = arg1;
  magic_mem[3] = arg2;
  __sync_synchronize();
  write_csr(mtohost, (long)magic_mem);
  while (swap_csr(mfromhost, 0) == 0); 
  return magic_mem[0];
}

long handle_trap(uint32_t cause, uint32_t epc, uint64_t regs[32])
{
  long sys_ret = 0;

  if(cause == 7)
  {
    return 0;  
  }   

  sys_ret = handle_frontend_syscall(regs[17], regs[10], regs[11], regs[12]);

  regs[10] = sys_ret;
  return epc+4;
}

void console_initialize_hardware(void)
{
	set_csr(sstatus, SSTATUS_FS);
  /* Do nothing */
}

/* Epiphany simulator would handle this system call */
static char buf[64] __attribute__((aligned(64)));
static int  buflen = 0;

static void outbyte_console(char ch)
{
  buf[buflen++] = ch;
  if (ch == '\n' || buflen == sizeof(buf))
  {
    syscall(SYS_write, 1, ((long) buf) + 0x02974000, buflen);
    buflen = 0;
  }
  return 0;
}

static char inbyte_console(void)
{

}

/*
 *  console_outbyte_polled
 *
 *  This routine transmits a character using polling.
 */
void console_outbyte_polled(
  int  port,
  char ch
)
{
  outbyte_console( ch );
}

/*
 *  console_inbyte_nonblocking
 *
 *  This routine polls for a character.
 */

int console_inbyte_nonblocking(int port)
{
  char c;

  c = inbyte_console();
  if (!c)
    return -1;
  return (int) c;
}

/*
 *  To support printk
 */

#include <rtems/bspIo.h>

static void RISCV_output_char(char c) { console_outbyte_polled( 0, c ); }

BSP_output_char_function_type BSP_output_char = RISCV_output_char;
BSP_polling_getchar_function_type BSP_poll_char =
  (void *)console_inbyte_nonblocking;
