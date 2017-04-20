################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Current_log.obj: ../Current_log.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/James/Documents/RTOS_Workspace/Prjct_tirtos_driverlib" --include_path="C:/ti/simplelink_msp432_sdk_1_30_00_40/source/third_party/CMSIS/Include" --include_path="C:/ti/simplelink_msp432_sdk_1_30_00_40/kernel/tirtos/packages/ti/sysbios/posix" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/include" --advice:power=all --advice:power_severity=suppress --define=__MSP432P401R__ -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="Current_log.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

MSP_EXP432P401R.obj: ../MSP_EXP432P401R.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/James/Documents/RTOS_Workspace/Prjct_tirtos_driverlib" --include_path="C:/ti/simplelink_msp432_sdk_1_30_00_40/source/third_party/CMSIS/Include" --include_path="C:/ti/simplelink_msp432_sdk_1_30_00_40/kernel/tirtos/packages/ti/sysbios/posix" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/include" --advice:power=all --advice:power_severity=suppress --define=__MSP432P401R__ -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="MSP_EXP432P401R.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Motor_control.obj: ../Motor_control.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/James/Documents/RTOS_Workspace/Prjct_tirtos_driverlib" --include_path="C:/ti/simplelink_msp432_sdk_1_30_00_40/source/third_party/CMSIS/Include" --include_path="C:/ti/simplelink_msp432_sdk_1_30_00_40/kernel/tirtos/packages/ti/sysbios/posix" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/include" --advice:power=all --advice:power_severity=suppress --define=__MSP432P401R__ -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="Motor_control.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Prjct_tirtos_driverlib.obj: ../Prjct_tirtos_driverlib.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP432 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/Users/James/Documents/RTOS_Workspace/Prjct_tirtos_driverlib" --include_path="C:/ti/simplelink_msp432_sdk_1_30_00_40/source/third_party/CMSIS/Include" --include_path="C:/ti/simplelink_msp432_sdk_1_30_00_40/kernel/tirtos/packages/ti/sysbios/posix" --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/include" --advice:power=all --advice:power_severity=suppress --define=__MSP432P401R__ -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="Prjct_tirtos_driverlib.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

build-1437867119:
	@$(MAKE) -Onone -f subdir_rules.mk build-1437867119-inproc

build-1437867119-inproc: ../Prjct_tirtos_driverlib.cfg
	@echo 'Building file: $<'
	@echo 'Invoking: XDCtools'
	"C:/ti/xdctools_3_50_01_12_core/xs" --xdcpath="C:/ti/simplelink_msp432_sdk_1_30_00_40/source;C:/ti/simplelink_msp432_sdk_1_30_00_40/kernel/tirtos/packages;C:/ti/ccsv7/ccs_base;" xdc.tools.configuro -o configPkg -t ti.targets.arm.elf.M4F -p ti.platforms.msp432:MSP432P401R -r release -c "C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS" --compileOptions "-mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path=\"C:/Users/James/Documents/RTOS_Workspace/Prjct_tirtos_driverlib\" --include_path=\"C:/ti/simplelink_msp432_sdk_1_30_00_40/source/third_party/CMSIS/Include\" --include_path=\"C:/ti/simplelink_msp432_sdk_1_30_00_40/kernel/tirtos/packages/ti/sysbios/posix\" --include_path=\"C:/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.2.LTS/include\" --advice:power=all --advice:power_severity=suppress --define=__MSP432P401R__ -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on  " "$<"
	@echo 'Finished building: $<'
	@echo ' '

configPkg/linker.cmd: build-1437867119 ../Prjct_tirtos_driverlib.cfg
configPkg/compiler.opt: build-1437867119
configPkg/: build-1437867119


