/*
 * Copyright (c) 2017 Denis Obrezkov <denisobrezkov@gmail.com>
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.org/license/LICENSE.
 */

#ifndef FE310_H
#define FE310_H

#include <bsp/fe310-uart.h>

#define FE310
#define FE3XX

#define FE310_GPIO  (*(volatile fe310_gpio_t*) 0x10012000)
#define FE310_UART0 (*(volatile fe310_uart_t*) 0x10013000)
#define FE310_UART1 (*(volatile fe310_uart_t*) 0x10023000)

/* Choose oscillator */
#define USE_HFXOSC
#define USE_PLL

/* Clock parameters */
#define FE310_CLOCK_PERIOD 512
#define CONFIGURE_MICROSECONDS_PER_TICK 15625


#endif /* FE310_H */
