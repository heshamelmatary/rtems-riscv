/*
 * Copyright (c) 2017 Denis Obrezkov <denisobrezkov@gmail.com>
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.org/license/LICENSE.
 */

#include <bsp/irq.h>
#include <bsp/fatal.h>
#include <bsp/fe310.h>
#include <stdint.h>

static uint32_t fe310_clock_period = 0;

static void FE310_clock_driver_support_install_isr(
  rtems_isr_entry Clock_isr
)
{
  rtems_status_code sc = RTEMS_SUCCESSFUL;
    
  sc = rtems_interrupt_handler_install(
    1,
    "Clock",
    RTEMS_INTERRUPT_UNIQUE,
    (rtems_interrupt_handler) Clock_isr,
    NULL
  );
  if ( sc != RTEMS_SUCCESSFUL ) {
    rtems_fatal_error_occurred(0xdeadbeef);
  }
}

static void FE310_clock_driver_support_at_tick ( void )
{
  (*MTIMECMP) += fe310_clock_period;
}

static void FE310_clock_init ( void )
{
  fe310_clock_period = rtems_configuration_get_microseconds_per_tick() * \
                        FE310_CLOCK_FREQ / 1000000;
  (*MTIMECMP) = (*MTIME) + fe310_clock_period;
  enable_mtime_interrupts();
}

#define Clock_driver_support_initialize_hardware() \
  FE310_clock_init()

#define CLOCK_DRIVER_USE_DUMMY_TIMECOUNTER

#define Clock_driver_support_install_isr(isr,old) \
  FE310_clock_driver_support_install_isr ( isr )

#define Clock_driver_support_at_tick() \
  FE310_clock_driver_support_at_tick()

#include "../../../shared/clockdrv_shell.h"
