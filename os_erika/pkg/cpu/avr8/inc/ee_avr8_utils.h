/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2013  Evidence Srl
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
 * Author: 2013,  Giuseppe Serano
 */

#ifndef	__INCLUDE_EE_AVR8_UTILS_H__
#define	__INCLUDE_EE_AVR8_UTILS_H__

/*************************************************************************
 Types
 *************************************************************************/

/*************************************************************************
 Variables
 *************************************************************************/

/*************************************************************************
 Functions
 *************************************************************************/

#ifndef	F_CPU
#define	F_CPU	32000000UL
#endif	/* F_CPU */

#define	EE_DELAY(_us)	\
	__builtin_avr_delay_cycles(EE_MCU_US_2_TICKS((_us), F_CPU))

/** @brief	Write to a CCP-protected 8-bit I/O register.
 *  @param[in]	addr	Address of the I/O register.
 *  @param[in]	value	Value to be written.
 *  @return	Nothing.
 *
 *  @note	This function is written in assembly because of the timecritial
 *  		operation of writing to the registers.
 *
 *  @note	CCP Register Address:	0x0034U
 *
 *  @note	CCP I/O register signature:	0xD8U
 *
 *  @note	INTERRUPTS MUST BE DISABLED!!!
 *
 */
void EE_avr8_WriteCCPReg(volatile EE_UREG * addr, EE_UREG value);

#endif /* __INCLUDE_EE_AVR8_UTILS_H__ */
