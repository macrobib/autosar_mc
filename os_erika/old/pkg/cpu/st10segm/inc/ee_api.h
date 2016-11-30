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
 * Author: 2000-2002 Paolo Gai
 * CVS: $Id: ee_api.h,v 1.4 2007/06/01 09:00:21 pj Exp $
 */


#ifndef __CPU_ST10SEGM_EE_OPT_H__
#define __CPU_ST10SEGM_EE_OPT_H__


/* If ST10_OPTIMIZED is defined, the endinstance functions have to be
   hand-optimized.  Moreover, if nested IRQs are allowed, a little
   stub have to be executed before calling the hand-optimized code.
*/
#ifdef __ST10_OPTIMIZED__

#define EE_thread_end_instance EE_st10_thread_end_instance 

#ifdef __ALLOW_NESTED_IRQ__
#define EE_IRQ_end_instance    EE_st10_optimized_IRQ_end_instance 
#else
#define EE_IRQ_end_instance    EE_st10_IRQ_end_instance 
#endif

#endif



#if defined(__FP__) || defined(__EDF__)
#if !defined(__FP_NO_MUTEX__) && !defined(__EDF_NO_MUTEX__)

#define __PRIVATE_MUTEX_LOCK__

_inline void EE_mutex_lock(EE_MUTEX m)
{
  EE_hal_disableIRQ();
  EE_mutex_oldceiling[m] = EE_sys_ceiling;
  EE_sys_ceiling |= EE_mutex_ceiling[m];
  EE_hal_enableIRQ();
}

#endif
#endif




#endif
