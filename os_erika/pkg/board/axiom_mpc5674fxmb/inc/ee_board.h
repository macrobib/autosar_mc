/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2010  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * ERIKA Enterprise is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation,
 * (with a special exception described below).
 *
 * Linking this code statically or dynamically with other modules is
 * making a combined work based on this code.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this code with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module.  An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.  If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */
/*
 * MPC5674FXMB register mappings
 * Author: 2010 Fabio Checconi
 */

#ifndef __INCLUDE_EE_AXIOM_MPC5674FXMB_BOARD_H__
#define __INCLUDE_EE_AXIOM_MPC5674FXMB_BOARD_H__

#define SIU_BASE	0xc3f90000

#define SIU_PCRS	((volatile EE_UINT16 *)SIU_BASE)

/* Leds */
#define SIU_PCR147	SIU_PCRS[179]
#define SIU_PCR148	SIU_PCRS[180]
#define SIU_PCR149	SIU_PCRS[181]
#define SIU_PCR150	SIU_PCRS[182]
#define SIU_PCR151	SIU_PCRS[183]
#define SIU_PCR152	SIU_PCRS[184]
#define SIU_PCR153	SIU_PCRS[185]
#define SIU_PCR154	SIU_PCRS[186]
/* Button */
#define SIU_PCR450	SIU_PCRS[482]

#define SIU_GPIO	((volatile EE_UINT8 *)(SIU_BASE + 0x0600))

#define SIU_IREER	(*(volatile EE_UINT32 *)(SIU_BASE + 0x0028))
#define SIU_IFEER	(*(volatile EE_UINT32 *)(SIU_BASE + 0x002c))

#define SIU_EISR	(*(volatile EE_UINT32 *)(SIU_BASE + 0x0014))

#define SIU_DIRER	(*(volatile EE_UINT32 *)(SIU_BASE + 0x0018))

#define SIU_DIRSR	(*(volatile EE_UINT32 *)(SIU_BASE + 0x001c))

#define SIU_EIISR	(*(volatile EE_UINT32 *)(SIU_BASE + 0x0904))

#ifdef __USE_LEDS__

#define LED_0	1
#define LED_1	2
#define LED_2	4
#define LED_3	8
#define LED_4	16
#define LED_5	32
#define LED_6	64
#define LED_7	128

__INLINE__ void __ALWAYS_INLINE__ EE_leds_init(void)
{
	SIU_PCR147 = 0x200;
	SIU_PCR148 = 0x200;
	SIU_PCR149 = 0x200;
	SIU_PCR150 = 0x200;
        SIU_PCR151 = 0x200;
        SIU_PCR152 = 0x200;
        SIU_PCR153 = 0x200;
        SIU_PCR154 = 0x200;
	SIU_GPIO[147] = 1;
	SIU_GPIO[148] = 1;
	SIU_GPIO[149] = 1;
	SIU_GPIO[150] = 1;
        SIU_GPIO[151] = 1;
	SIU_GPIO[152] = 1;
	SIU_GPIO[153] = 1;
	SIU_GPIO[154] = 1;
}

__INLINE__ void __ALWAYS_INLINE__ EE_leds(EE_UREG led)
{
	SIU_GPIO[147] = led & 1;
	SIU_GPIO[148] = (led >> 1) & 1;
	SIU_GPIO[149] = (led >> 2) & 1;
	SIU_GPIO[150] = (led >> 3) & 1;
        SIU_GPIO[151] = (led >> 4) & 1;
        SIU_GPIO[152] = (led >> 5) & 1;
        SIU_GPIO[153] = (led >> 6) & 1;
        SIU_GPIO[154] = (led >> 7) & 1;
}

__INLINE__ void __ALWAYS_INLINE__ EE_led_set(EE_UREG idx, EE_UREG val)
{
	SIU_GPIO[147 + idx] = val;
}

#define EE_led_0_on()	EE_led_set(0, 1);
#define EE_led_0_off()	EE_led_set(0, 0);
#define EE_led_1_on()	EE_led_set(1, 1);
#define EE_led_1_off()	EE_led_set(1, 0);
#define EE_led_2_on()	EE_led_set(2, 1);
#define EE_led_2_off()	EE_led_set(2, 0);
#define EE_led_3_on()	EE_led_set(3, 1);
#define EE_led_3_off()	EE_led_set(3, 0);
#define EE_led_4_on()	EE_led_set(4, 1);
#define EE_led_4_off()	EE_led_set(4, 0);
#define EE_led_5_on()	EE_led_set(5, 1);
#define EE_led_5_off()	EE_led_set(5, 0);
#define EE_led_6_on()	EE_led_set(6, 1);
#define EE_led_6_off()	EE_led_set(6, 0);
#define EE_led_7_on()	EE_led_set(7, 1);
#define EE_led_7_off()	EE_led_set(7, 0);

#endif

#ifdef __USE_BUTTONS__

#define BUTTON_0	1

__INLINE__ void __ALWAYS_INLINE__ EE_buttons_disable_interrupts(EE_UREG btn)
{
	EE_UINT32 val;

	val = SIU_DIRER;
	SIU_DIRER = val & ~1UL;
}

__INLINE__ void __ALWAYS_INLINE__ EE_buttons_enable_interrupts(EE_UREG btn)
{
	EE_UINT32 val;

	val = SIU_DIRER;
	SIU_DIRER = val | 1;
}

__INLINE__ void __ALWAYS_INLINE__ EE_buttons_clear_ISRflag(EE_UREG btn)
{
	SIU_EISR = 1;
}

__INLINE__ EE_UINT32 __ALWAYS_INLINE__ EE_button_get_B0(void)
{
	return !((*(volatile EE_UINT32 *)(SIU_BASE + 0x0FC0))&0x100);
}

__INLINE__ void __ALWAYS_INLINE__ EE_buttons_init(EE_UREG btn, int n)
{
	EE_UINT32 val;

	SIU_PCR450 = 0x900;
	val = SIU_EIISR;
	SIU_EIISR = val & ~3UL;
	val = SIU_IFEER;
	SIU_IREER = val | 1;
	val = SIU_DIRER;
	SIU_DIRER = val | 1;
	SIU_DIRSR = 0;
}

#endif

#endif
