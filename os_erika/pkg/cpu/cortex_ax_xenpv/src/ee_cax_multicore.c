#include "ee_internal.h"
#include "cpu/cortex_ax_xenpv/inc/ee_cax_irq.h"

//DeclareIsr(EE_cax_iirq_handler);

extern void  EE_as_rpc_handler(void);
/* Declare ISR handler */
ISR2(EE_cax_iirq_handler)
{
#ifdef EE_AS_RPC__
  EE_as_rpc_handler();
#elif defined(__RN__)
  EE_rn_handler();
#endif /*  EE_AS_RPC__ || __RN__ */
}
