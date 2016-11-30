
## CPU OPTIONS ##
EEOPT += __CORTEX_RX__
# CPU Model 
EEOPT += __CORTEX_R4__
# Compiler Type
EEOPT += __CCS__


EEOPT += __RTD_TMS570__
#################

## MCU OPTIONS ## 
EEOPT += __TI__
EEOPT += __TMS570__

APPBASE := ..
OUTBASE := Debug
#################
### Setting Erika's variables:
# ERIKA_FILES= ../../..
# APPBASE = .
# 
# EEOPT =


RTDRUID_CONFIGURATOR_NUMBER:=1278


EEOPT += DEBUG
EEOPT += __USE_SYSTICK__
EEOPT += __TI_DRIVER_LIB__
EEOPT += __ALLOW_NESTED_IRQ__
EEOPT += __USE_GIO__
EEOPT += __USE_LEDS__
EEOPT += __USE_HET__
EEOPT += __USE_SCI__
EEOPT += __CORTEX_RX__

EEOPT += __RTD_LINUX__
EEOPT += __DISABLE_EEOPT_DEFINES__

ifdef ERIKA_FILES
ifdef EEBASE
    $(warning EEBASE is set, but it has been overridden by ERIKA_FILES)
endif
EEBASE := ${ERIKA_FILES}

else # ERIKA_FILES

ifndef EEBASE
        EEBASE := /opt/ti/ccsv6/eclipse/plugins/com.eu.evidence.ee_2.7.0.N20160609_1458/ee_files
else
        $(warning The usage of EEBASE is deprecated. Please use ERIKA_FILES)
endif
endif # ERIKA_FILES
# ERIKA_FILES has fulfilled its role. Make sure it's not used inside Erika makefiles
ERIKA_FILES :=
$(info Using erika files in $(EEBASE))

CFLAGS  += 
ASFLAGS += 
LDFLAGS += 
LDDEPS  += 
LIBS    += 


APP_SRCS += eecfg.c code.c ee_mc_data.c sys_pmu.asm
TMPDIR=/tmp/ti
include $(EEBASE)/pkg/cfg/rules.mk
