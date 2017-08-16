/*
 * Copyright (c) 2017 Denis Obrezkov <denisobrezkov@gmail.com>
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.org/license/LICENSE.
 */

#ifndef FE310_GPIO_H
#define FE310_GPIO_H


#include <rtems/termiostypes.h>
#include <rtems/irq.h>

#define IOF0_UART0_MASK 0x00030000
#define IOF0_UART1_MASK 0x00300000

typedef struct {
  uint32_t value;
  uint32_t input_en;
  uint32_t output_en;
  uint32_t port;
  uint32_t pue;
  uint32_t ds;
  uint32_t rise_ie;
  uint32_t rise_ip;
  uint32_t fall_ie;
  uint32_t fall_ip;
  uint32_t high_ie;
  uint32_t high_ip;
  uint32_t low_ie;
  uint32_t low_ip;
  uint32_t iof_en;
  uint32_t iof_sel;
  uint32_t out_xor;
} fe310_gpio_t;



#endif /* FE310_GPIO_H */
