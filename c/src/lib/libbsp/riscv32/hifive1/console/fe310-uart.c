/*
 * Copyright (c) 2017 Denis Obrezkov <denisobrezkov@gmail.com>
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.org/license/LICENSE.
 */

#include <rtems/console.h>
#include <rtems/termiostypes.h>
#include <termios.h>
#include <bsp/prci.h>
#include <bsp/fe310-uart.h>
#include <bsp/fe310-gpio.h>
#include <bsp/fe310.h>
#include <bsp/fatal.h>

/*
 * TODO: UART code should be separated from the console code,
 * uart_num probably should be an enumeration in the future
 */
void fe310_enable_uart (volatile fe310_gpio_t * gpio, uint32_t uart_num)
{
  if (uart_num == 0) {
    gpio->iof_sel &= ~IOF0_UART0_MASK;
    gpio->iof_en |= IOF0_UART0_MASK;
  } else
  if (uart_num == 1) {
    gpio->iof_sel &= ~IOF0_UART1_MASK;
    gpio->iof_en |= IOF0_UART1_MASK;  
  } else {
    return;
  }
}

void fe310_disable_uart (volatile fe310_gpio_t * gpio, uint32_t uart_num)
{
  if (uart_num == 0) {
    gpio->iof_en &= ~IOF0_UART0_MASK;
  } else
  if (uart_num == 1) {
    gpio->iof_en &= ~IOF0_UART1_MASK;
  } else {
    return;
  }
}

static void fe310_console_putc (char ch);

fe310_uart_context driver_context = {
  .base = RTEMS_TERMIOS_DEVICE_CONTEXT_INITIALIZER("FE310_UART0"),
  .device_name = "/dev/console",
  .regs = (volatile fe310_uart_t *) &FE310_UART0,
};

rtems_device_driver console_initialize(
  rtems_device_major_number  major,
  rtems_device_minor_number  minor,
  void                      *arg
)
{ 
  rtems_status_code sc;
  const rtems_termios_device_handler *handler = &fe310_uart_handler_polled;
  
  /*
   * Initialize the Termios infrastructure.  If Termios has already
   * been initialized by another device driver, then this call will
   * have no effect.
   */
  rtems_termios_initialize();
  fe310_uart_context * ctx = &driver_context;
    /*
     * Install this device in the file system and Termios.  In order
     * to use the console (i.e. being able to do printf, scanf etc.
     * on stdin, stdout and stderr), one device must be registered as
     * "/dev/console" (CONSOLE_DEVICE_NAME).
     */
  sc = rtems_termios_device_install(
      ctx->device_name,
      handler,
      NULL,
      &ctx->base
  );
  if ( sc != RTEMS_SUCCESSFUL ) {
    bsp_fatal(BSP_FATAL_CONSOLE_NO_DEV);
  }

  return RTEMS_SUCCESSFUL;
}

static bool fe310_uart_first_open (
  rtems_termios_tty             *tty,
  rtems_termios_device_context  *base,
  struct termios                *term,
  rtems_libio_open_close_args_t *args
)
{
  fe310_uart_context * ctx;
  rtems_status_code sc;

  /* Configure GPIO to be UART */
  fe310_enable_uart((volatile fe310_gpio_t *)&FE310_GPIO, 0);

  sc = rtems_termios_set_initial_baud (tty, B115200);
  if ( sc != RTEMS_SUCCESSFUL ) {
    return false;
  }

  /* Set up a baud rate and enable tx and rx */
  ctx = (fe310_uart_context *) base;
  (ctx->regs)->div = hifive1_default_freq / 115200 - 1;
  (ctx->regs)->txctrl |= 1;
  (ctx->regs)->rxctrl |= 1;
  return true;
};

static void fe310_uart_last_close (
  rtems_termios_tty             *tty,
  rtems_termios_device_context  *base,
  rtems_libio_open_close_args_t *args
)
{
  fe310_disable_uart((volatile fe310_gpio_t *)&FE310_GPIO, 0);
}

static int fe310_uart_poll_read (
  rtems_termios_device_context  *base
)
{
  fe310_uart_context * ctx = (fe310_uart_context*) base;
  size_t i;
  
  if (((ctx->regs->rxdata) & TXRXREADY) != 0) {
    return -1;
  } else {
    return ctx->regs->rxdata;
  }  
}

static ssize_t fe310_uart_poll_write (
  rtems_termios_device_context  *base,
  const char                    *buf,
  size_t                        n
)
{
  fe310_uart_context * ctx = (fe310_uart_context*) base;
  size_t i;

  rtems_status_code sc;

  fe310_enable_uart((volatile fe310_gpio_t *)&FE310_GPIO, 0);

  (ctx->regs)->div = hifive1_default_freq / 115200 - 1;
  (ctx->regs)->txctrl |= 1;
  (ctx->regs)->rxctrl |= 1;

  for (i = 0; i < n; ++i) {
    while (((ctx->regs->txdata) & TXRXREADY) != 0) {
        ;
    }
    ctx->regs->txdata = buf[i];
  }
  return n;
}

static void fe310_console_putc (char ch) {
  fe310_uart_poll_write ( (rtems_termios_device_context *)&driver_context, &ch, 1);
}

static bool fe310_uart_set_attributes(
  rtems_termios_device_context  *base,
  const struct termios          *term
)
{
  return true;
}

const rtems_termios_device_handler fe310_uart_handler_polled = {
  .first_open = fe310_uart_first_open,
  .last_close = fe310_uart_last_close,
  .poll_read = fe310_uart_poll_read,
  .write = fe310_uart_poll_write,
  .set_attributes = fe310_uart_set_attributes,
  .ioctl = NULL,
  .mode = TERMIOS_POLLED
};

void console_outbyte_polled(
  int port,
  char ch
)
{
  fe310_console_putc(ch);   
}

int console_inbyte_nonblocking(
  int port
)
{
  return -1;
}

void console_initialize_hardware (void)
{
  volatile fe310_gpio_t * gpio;
  volatile fe310_uart_t * uregs = (volatile fe310_uart_t *) &FE310_UART0;
  rtems_status_code sc;
  
  fe310_enable_uart((volatile fe310_gpio_t *)&FE310_GPIO, 0);
  
  uregs->div = hifive1_default_freq / 115200 - 1;
  uregs->txctrl |= 1;
  return;
}

#include <rtems/bspIo.h>
BSP_output_char_function_type  BSP_output_char = fe310_console_putc;
