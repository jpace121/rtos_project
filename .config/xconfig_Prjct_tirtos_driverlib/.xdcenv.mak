#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = C:/ti/simplelink_msp432_sdk_1_30_00_40/source;C:/ti/simplelink_msp432_sdk_1_30_00_40/kernel/tirtos/packages;C:/ti/ccsv7/ccs_base;C:/Users/James/Documents/RTOS_Workspace/Prjct_tirtos_driverlib/.config
override XDCROOT = C:/ti/xdctools_3_50_01_12_core
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = C:/ti/simplelink_msp432_sdk_1_30_00_40/source;C:/ti/simplelink_msp432_sdk_1_30_00_40/kernel/tirtos/packages;C:/ti/ccsv7/ccs_base;C:/Users/James/Documents/RTOS_Workspace/Prjct_tirtos_driverlib/.config;C:/ti/xdctools_3_50_01_12_core/packages;..
HOSTOS = Windows
endif
