################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.12.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="C:/ti/simplelink_msp432p4_sdk_2_20_00_12/source/ti/devices/msp432p4xx/driverlib" --include_path="C:/ti/ccsv8/ccs_base/arm/include" --include_path="C:/ti/simplelink_msp432p4_sdk_2_20_00_12/source/ti/devices/msp432p4xx" --include_path="C:/Users/xavmo/CCS_git/Projects/QuadcopterXXX/Source/portable/CCS/ARM_CM4F" --include_path="C:/ti/simplelink_msp432p4_sdk_2_20_00_12/source" --include_path="C:/Users/xavmo/CCS_git/Projects/QuadcopterXXX/Source/include" --include_path="C:/ti/ccsv8/ccs_base/arm/include/CMSIS" --include_path="C:/Users/xavmo/CCS_git/Projects/QuadcopterXXX" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-arm_18.12.1.LTS/include" --advice:power="all" --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


