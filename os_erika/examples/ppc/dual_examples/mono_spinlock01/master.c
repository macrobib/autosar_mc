/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2011  Evidence Srl
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
 * Simple test for spinlocks and shared memory
 * Author: 2011 Bernardo Dal Seno
 */


#include "shared.h"

/* Space for my shared data */
volatile int EE_SHARED_UDATA shared[SHARED_LONG_LEN];

/* Counters; volatile because they are accessed in interrupt handlers and
 * different tasks */
volatile int counter, tick_counter;

/* started: Set to 1 at the beginning of main() */
int started;

/* Final result */
EE_TYPEASSERTVALUE result;

/* Assertion */
enum assertions {
	asr_init = 1,
	asr_startz0,
	asr_shared,
	asr_shared_last = asr_shared + SHARED_LEN - 1,
	asr_crit_1,
	asr_crit_1_out,
	asr_crit_2,
	asr_crit_2_out,
	asr_dim
};
EE_TYPEASSERTVALUE EE_assertions[asr_dim];

DeclareTask(TaskZ6);


static int check_shared_value(int val)
{
	int ret = 1;
	unsigned i;
	for (i = 0; i < SHARED_LONG_LEN; ++i) {
		if (shared[i] != val)
			ret = 0;
	}
	return ret;
}


static void set_shared_value(int val)
{
	unsigned i;
	for (i = 0; i < SHARED_LONG_LEN; ++i) {
		shared[i] = val;
	}
}


TASK(TaskZ6)
{
	unsigned i;
	started = 1;
	EE_assert(asr_init, 1, EE_ASSERT_NIL);
	/* Setup interprocessor irqs */
	EE_mpc5668_setup_inter_irqs();
	/* Start Z0 from RAM */
	EE_mpc5668_start_z0((void (*)(void))0x40020000);
	EE_assert(asr_startz0, 1, asr_init);

	/* Test shared memory */
	for (i = 0; i < SHARED_LEN; ++i) {
		shared[i] = 1;
		while (shared[i] == 1)
			;
		EE_assert(i + asr_shared, 1, i + asr_shared - 1);
	}

	/* Test spin locks */
	EE_mpc5668_spin_in(MY_SPINLOCK);
	EE_assert(asr_crit_1, check_shared_value(2), asr_shared_last);
	set_shared_value(1);
	EE_mpc5668_spin_out(MY_SPINLOCK);
	/* EE_assert() should also give time to the other core to get the lock */
	EE_assert(asr_crit_1_out, 1, asr_crit_1);
	EE_mpc5668_spin_in(MY_SPINLOCK);
	EE_assert(asr_crit_2, check_shared_value(2), asr_crit_1_out);
	EE_mpc5668_spin_out(MY_SPINLOCK);
	EE_assert(asr_crit_2_out, 1, asr_crit_2);
	
	EE_assert_range(0, 1, asr_dim - 1);
	result = EE_assert_last();
	started = 0;
}


/*
 * MAIN TASK
 */
int main(void)
{
	ActivateTask(TaskZ6);
	/* ActivateTask does not return until the task has ended */
	return 0;
}
