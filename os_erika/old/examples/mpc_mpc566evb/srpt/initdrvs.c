/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2008  Evidence Srl
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
 * Author: 2004 Antonio Fiaschi
 * CVS: $Id: initdrvs.c,v 1.2 2004/11/30 09:59:44 pj Exp $
 */

#include "code.h"
#include "erikahal.h"


void init_drivers(void)
{
    ERIKA_clear_pending_IRQ();

#ifdef __EXT0_USED__
    ERIKA_enable_external_IRQ(IRQ_EXT0_MASK);	/* button */
    ERIKA_ext0_init();
#endif

#ifdef __LEDS_USED__
    ERIKA_leds_init();
#endif

#ifdef __LCD_USED__
    ERIKA_LCD_init();
#endif

#ifdef __TIMER_USED__		/* defined through __TIMER_?_USED__ */
    ERIKA_timer_init();
#endif

#ifdef __TIMER_0_USED__
    ERIKA_enable_external_IRQ(IRQ_TIMER0_MASK);
#endif

#ifdef __TIMER_1_USED__
    ERIKA_enable_external_IRQ(IRQ_TIMER1_MASK);
#endif

#ifdef __DIP_SWITCH_USED__
    /* do nothing */
#endif

    /* for hal_gettime() */
#ifdef __TIME_SUPPORT__
    ERIKA_timer_0_set(0xffffffff);
    ERIKA_timer_0_start();
#endif
    
}

