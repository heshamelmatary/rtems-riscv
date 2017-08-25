/*
 *
 * Copyright (c) 2017
 * Denis Obrezkov <denisobrezkov@gmail.com>
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

#include <bsp/prci.h>
#include <bsp/fe310.h>

uint32_t hifive1_current_freq() {
  return hifive1_default_freq;
}

void fe310_initialize_oscills() {
  volatile uint32_t * pll_reg = (volatile uint32_t *) PRCI_PLLCFG;
  volatile uint32_t * high_freq_reg = (volatile uint32_t *) PRCI_HFROSCCFG;

#ifdef USE_HFROSC
  /* Setting up osc frequency */
  uint32_t tmp_reg = 0;
  /* Install divider in high frequency oscillator */
  tmp_reg |= (HFROSC_DIV_VAL & HFROSC_DIV_MASK) << HFROSC_DIV_OFFSET;
  tmp_reg |= (HFROSC_TRIM_VAL & HFROSC_TRIM_MASK) << HFROSC_TRIM_OFFSET;
  tmp_reg |= (HFROSC_EN_VAL & HFROSC_EN_MASK) << HFROSC_EN_OFFSET;
  (*high_freq_reg) = tmp_reg; 
  while (( (*high_freq_reg) & ((HFROSC_RDY_VAL & 0x1) \
                  << HFROSC_RDY_OFFSET)) == 0 ) {
    ;             
  } 
#endif /* USE_HFROSC */

#ifdef USE_HFXOSC
  volatile uint32_t * ext_freq_reg = (volatile uint32_t *) PRCI_HFXOSCCFG;
  (*ext_freq_reg) |= ((HFXOSC_EN_VAL & 0x1) << HFXOSC_EN_OFFSET);
  while (( (*ext_freq_reg) & ((HFXOSC_RDY_VAL & 0x1) \
                  << HFXOSC_RDY_OFFSET)) == 0 ) {
    ;             
  }
  (*pll_reg) |= (0x1 << PLL_BYPASS_OFFSET);
  (*pll_reg) |= (0x1 << PLL_REF_SEL_OFFSET);
  (*pll_reg) |= (0x1 << PLL_SEL_OFFSET);
  (*high_freq_reg) &= ~(0x1 << HFROSC_EN_OFFSET);
  
#endif /* USE_HFXOSC */
#ifndef USE_PLL
  /* Disable PLL */
  (*pll_reg) &= ~(0x1 << PLL_SEL_OFFSET);
#else 

#endif
}
