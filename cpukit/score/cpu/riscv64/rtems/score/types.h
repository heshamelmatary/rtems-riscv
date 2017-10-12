/**
 * @file
 *
 * @brief RISCV Architecture Types API
 */

/*
 *  This include file contains type definitions pertaining to the
 *  arm processor family.
 *
 *  COPYRIGHT (c) 2014 Hesham ALMatary <heshamelmatary@gmail.com>
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.org/license/LICENSE.
 *
 */

 #ifndef _RTEMS_SCORE_TYPES_H
#define _RTEMS_SCORE_TYPES_H

#include <rtems/score/basedefs.h>

#ifndef ASM

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup ScoreCPU
 */
/**@{**/

/*
 *  This section defines the basic types for this processor.
 */

/** Type that can store a 32-bit integer or a pointer. */
typedef uintptr_t CPU_Uint32ptr;

typedef uint16_t Priority_bit_map_Word;
typedef void riscv_isr;
typedef void ( *riscv_isr_entry )( void );

/** @} */

#ifdef __cplusplus
}
#endif

#endif  /* !ASM */

#endif
