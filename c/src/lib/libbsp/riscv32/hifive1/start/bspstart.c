/*
 *  Copyright (c) 2017
 *  Denis Obrezkov <denisobrezkov@gmail.com>
 *
 *  The license and distribution terms for this file may be
 *  found in the file LICENSE in this distribution or at
 *  http://www.rtems.org/license/LICENSE.
 */

#include <bsp.h>
#include <bsp/bootcard.h>
#include <bsp/prci.h>
#include <bsp/fe310.h>

/*
 * This routine make initialization of HiFive1 (FE310) counters.
 */

void bsp_start( void )
{
  fe310_initialize_oscills();
  bsp_interrupt_initialize();
}
