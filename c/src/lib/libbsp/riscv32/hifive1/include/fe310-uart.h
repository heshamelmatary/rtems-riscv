/*
 * Copyright (c) 2017 Denis Obrezkov <denisobrezkov@gmail.com>
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.org/license/LICENSE.
 */

#ifndef FE310_UART_H
#define FE310_UART_H

#define TXRXREADY (1 << 31)

#include <rtems/termiostypes.h>
#include <rtems/irq.h>

typedef struct {
  uint32_t txdata;
  uint32_t rxdata;
  uint32_t txctrl;
  uint32_t rxctrl;
  uint32_t ie;
  uint32_t ip;
  uint32_t div;
} fe310_uart_t;

/* Low-level driver specific data structure */
typedef struct {
  rtems_termios_device_context base;
  const char *device_name;
  volatile fe310_uart_t *regs;
} fe310_uart_context;

extern const rtems_termios_device_handler fe310_uart_handler_polled;

extern fe310_uart_context driver_context;

#endif /* FE310_UART_H */
