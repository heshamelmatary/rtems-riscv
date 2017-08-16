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

#ifndef PRCI_H
#define PRCI_H

#include <stdint.h>

/*
 * PRCI description for HiFive1 system
 */
#define PRCI_BASE 0x10008000
#define PRCI_HFROSCCFG 0x10008000
#define PRCI_HFXOSCCFG 0x10008004
#define PRCI_PLLCFG 0x10008008
#define PRCI_PLLOUTDIV 0x1000800C
#define PRCI_CORECLKCFG 0x10008010

/*
 * 16 MHz from external crystal oscillator
 */
#define hifive1_default_freq 16000000

/* 
 * HFROSCCFG configuration register values
 */
#define HFROSC_DIV_VAL 4
#define HFROSC_TRIM_VAL 16
#define HFROSC_EN_VAL 1
#define HFROSC_RDY_VAL 1
#define HFROSC_DIV_OFFSET 0
#define HFROSC_TRIM_OFFSET 16
#define HFROSC_EN_OFFSET 30
#define HFROSC_RDY_OFFSET 31

/* 
 * HFXOSCCFG configuration register values
 */
#define HFXOSC_EN_VAL 1
#define HFXOSC_RDY_VAL 1
#define HFXOSC_EN_OFFSET 30
#define HFXOSC_RDY_OFFSET 31

/* 
 * PLLCFG configuration register
 */
#define PLL_SEL_OFFSET 16

uint32_t hifive1_current_freq();

#endif /* PRCI_H */
