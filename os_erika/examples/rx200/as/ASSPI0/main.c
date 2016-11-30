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
 * Simple project to demonstrate that the GPT driver is integrated into the
 * makefiles and to test Gpt_Init(), Gpt_DeInit() and Gpt_GetVersionInfo()
 * services.
 * 
 * Author: 2013  Gianluca Franchino
 */

#include "Mcu.h"
#include "Port.h"
#include "Dio.h"
#include "Spi.h"
#include "test/assert/inc/ee_assert.h"

/* Assertions */
enum EE_ASSERTIONS {
	EE_ASSERT_FIN = 0,			/*  0 */
	EE_ASSERT_INIT,				/*  1 */
	EE_ASSERT_VERSION,			/*  2 */
	EE_ASSERT_CLOCK_INIT,		/*  3 */
	EE_ASSERT_SPI_UNINIT,		/*  4 */
	EE_ASSERT_SPI_INIT,			/*  5 */
	EE_ASSERT_SPI_HW_UNINIT,	/*  6 */
	EE_ASSERT_SPI_HW_INIT,		/*  7 */
	EE_ASSERT_SPI_DEINIT,		/*  8 */
	EE_ASSERT_DIM
};

EE_TYPEASSERTVALUE EE_assertions[EE_ASSERT_DIM];

/* Final result */
volatile EE_TYPEASSERTVALUE result;

/* counter */
volatile int counter = 0;

/*
 * TASK 1
 */
TASK(Task1)
{
  /* Nothing to do! */
}

/*
 * MAIN TASK
 */
int main(void)
{
	Std_VersionInfoType	version;
	Dio_PortLevelType	lvl;

	EE_assert(EE_ASSERT_INIT, TRUE, EE_ASSERT_NIL);

	Spi_GetVersionInfo(&version);

	EE_assert(EE_ASSERT_VERSION, ( (version.vendorID == 0) && 
		(version.moduleID == 83) && (version.sw_major_version == 1) && 
		(version.sw_minor_version == 0) && (version.sw_patch_version == 0)),
		EE_ASSERT_INIT);
	
	Mcu_Init(MCU_CONFIG_DEFAULT_PTR);
	if (Mcu_InitClock(MCU_CLK_MODE_HOCO40_I1_B2) == E_NOT_OK) {
		/* Clock Initialization Error. */
		Mcu_PerformReset();
	}
	
	EE_assert(EE_ASSERT_CLOCK_INIT, TRUE, EE_ASSERT_VERSION);
	
	Port_Init(PORT_CONFIG_DEFAULT_PTR);

	Dio_Init(DIO_CONFIG_DEFAULT_PTR);

	EE_assert(EE_ASSERT_SPI_UNINIT, ( Spi_GetStatus() == SPI_UNINIT ), 
			EE_ASSERT_CLOCK_INIT);
	
	Spi_Init(SPI_CONFIG_DEFAULT_PTR);
	
	EE_assert(EE_ASSERT_SPI_INIT, ( Spi_GetStatus() == SPI_IDLE ), 
			EE_ASSERT_SPI_UNINIT);
	
	EE_assert(EE_ASSERT_SPI_HW_UNINIT, 
			( Spi_GetHWUnitStatus(SPI_HW_UNIT_5) == SPI_UNINIT ), 
			EE_ASSERT_SPI_INIT);
	
	EE_assert(EE_ASSERT_SPI_HW_INIT, 
			( Spi_GetHWUnitStatus(SPI_HW_UNIT_1) == SPI_IDLE ), 
			EE_ASSERT_SPI_HW_UNINIT);
	
	EE_assert(EE_ASSERT_SPI_DEINIT, ( Spi_DeInit() == E_OK ), 
			EE_ASSERT_SPI_HW_INIT);
	
	EE_assert_range(EE_ASSERT_FIN, ( Spi_GetStatus() == SPI_UNINIT ), 
			EE_ASSERT_SPI_DEINIT);
	
	result = EE_assert_last();
	
	
	/* Forever loop: background activities (if any) should go here */
	for (;result == 1;) {
		while (counter % 100000) counter++;
		
		lvl = Dio_ReadChannel(DIO_CHANNEL_USER_LED_0);
		
		if (lvl & 0x00000001)
			Dio_WriteChannel(DIO_CHANNEL_USER_LED_0, 0x00000000);
	    else 
	    	Dio_WriteChannel(DIO_CHANNEL_USER_LED_0, 0x00000001);

		counter++;
	}

}