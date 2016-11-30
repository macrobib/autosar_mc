### Setting Erika's variables:
# ERIKA_FILES= ../../..
# APPBASE = .
# 
# EEOPT =


RTDRUID_CONFIGURATOR_NUMBER:=1278



############################################################################
#
# User options
#
############################################################################
EEOPT += EE_DEBUG
EEOPT += __ASSERT__
EEOPT += EE_EXECUTE_FROM_RAM
EEOPT += EE_SAVE_TEMP_FILES


############################################################################
#
# Automatic options
#
############################################################################
EEOPT += __RTD_CYGWIN__
EEOPT += EE_TRIBOARD_TC2X5
EEOPT += EE_TRICORE__
EEOPT += EE_TC27X__
EEOPT += EE_GNU__
EEOPT += ENABLE_SYSTEM_TIMER
EEOPT += __OO_ORTI_LASTERROR__
EEOPT += __OO_ORTI_SERVICETRACE__
EEOPT += __OO_ORTI_PRIORITY__
EEOPT += __OO_ORTI_RES_LOCKER_TASK__
EEOPT += __OO_ORTI_RES_ISLOCKED__
EEOPT += __OO_ORTI_STACK__
EEOPT += __OO_ORTI_ALARMTIME__
EEOPT += __OO_ORTI_RUNNINGISR2__
EEOPT += __OO_ECC1__
EEOPT += __OO_EXTENDED_STATUS__
EEOPT += __MULTI__
EEOPT += EE_AS_SCHEDULETABLES__
EEOPT += __OO_NO_ALARMS__
EEOPT += __OO_NO_RESOURCES__
EEOPT += __OO_AUTOSTART_TASK__
EEOPT += EE_AS_AUTOSTART_SCHEDULETABLE__
EEOPT += __ALLOW_NESTED_IRQ__
EEOPT += __DISABLE_EEOPT_DEFINES__


############################################################################
#
# Erika base directory
#
############################################################################
ifdef ERIKA_FILES
ifdef EEBASE
    $(warning EEBASE is set, but it has been overridden by ERIKA_FILES)
endif
EEBASE := $(shell cygpath `cygpath -ms '${ERIKA_FILES}'`)

else # ERIKA_FILES

ifndef EEBASE
        EEBASE := $(shell cygpath `cygpath -ms 'C:\Evidence\eclipse\plugins\com.eu.evidence.ee_2.4.0.N20140807_2204\ee_files'`)
else
        $(warning The usage of EEBASE is deprecated. Please use ERIKA_FILES)
endif
endif # ERIKA_FILES
# ERIKA_FILES has fulfilled its role. Make sure it's not used inside Erika makefiles
ERIKA_FILES :=
$(info Using erika files in $(EEBASE))


############################################################################
#
# Tricore
#
############################################################################
export PLATFORM := CYGWIN

APPBASE := ..
OUTBASE := Output

-include $(EEBASE)/pkg/cfg/path_helper.mk
$(eval $(call check_and_set_cygwin_compiler_path,TRICORE_GCCDIR,C:/HighTec/toolchains/tricore/v4.6.3.1))
TRICORE_MODEL  := tc27x

# Add a flag for the linkerscript to set the minimum size of system stack
LDFLAGS += -Wl,--defsym=__USTACK_SIZE=8192
LDFLAGS += -Wl,--defsym=__CSA_SIZE=16384



############################################################################
#
# Flags
#
############################################################################
CFLAGS  += 
ASFLAGS += 
LDFLAGS += 
LDDEPS  += 
LIBS    += 



############################################################################
#
# Sources
#
############################################################################
APP_SRCS += eecfg.c code.c


############################################################################
#
# end
#
############################################################################
include $(EEBASE)/pkg/cfg/rules.mk
