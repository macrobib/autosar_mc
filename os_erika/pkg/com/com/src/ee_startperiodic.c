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
 * Author: 2003 Francesco Bertozzi
 * CVS: $Id: ee_startperiodic.c,v 1.2 2005/07/17 13:58:36 pj Exp $
 */

#include "com/com/inc/ee_comprv.h"

/* 2.9.2.2.5 */
#ifdef __COM_CCC1__
#ifndef __PRIVATE_COM_STARTPERIODIC__
StatusType EE_com_StartPeriodic(void)
{
  EE_UINT8 i;
  struct EE_com_ipdu_RAM_TYPE * IPDU_RAM;
  
  GetResource(EE_MUTEX_COM_IPDU);
   
  EE_com_sys.first_PM = EE_COM_NULL;
  for (i=0; i<EE_COM_N_IPDU; i++) 
  {
    IPDU_RAM = EE_com_ipdu_RAM[i];

    if (((IPDU_RAM->property & (EE_MASK_IPDU_TXRX | EE_MASK_IPDU_DPM)) 
          == (EE_COM_IPDU_TX | EE_COM_IPDU_PER)) || 
        ((IPDU_RAM->property & (EE_MASK_IPDU_TXRX | EE_MASK_IPDU_DPM))
          == (EE_COM_IPDU_TX | EE_COM_IPDU_MIX))) 
    {  
      /* mixed or periodic ipdu */

      /* Set the first offset */
      EE_com_insert_PM(i, EE_com_ipdu_ROM[i]->reload_OFFSET);  
    }
  }
  
  ReleaseResource (EE_MUTEX_COM_IPDU);
  return E_OK;
}
#endif
#endif
