/**
 * @file
 *
 * @brief RISCV utility
 */
/*
 * COPYRIGHT (c) 2014 Hesham ALMatary <heshamelmatary@gmail.com>
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.org/license/LICENSE.
 */

#ifndef _RTEMS_SCORE_RISCV_UTILITY_H
#define _RTEMS_SCORE_RISCV_UTILITY_H

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


#endif /* _RTEMS_SCORE_RISCV_UTILITY_H */
