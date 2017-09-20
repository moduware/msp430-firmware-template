################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
libraries/NCN_GPIO.obj: ../libraries/NCN_GPIO.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"D:/ti/ccsv7/tools/compiler/msp430_4.2.1/bin/cl430" -vmsp --abi=eabi --include_path="D:/ti/ccsv7/ccs_base/msp430/include" --include_path="D:/GitHub/msp430-firmware-template/mdk" --include_path="D:/GitHub/msp430-firmware-template/libraries" --include_path="D:/GitHub/msp430-firmware-template" --include_path="D:/ti/ccsv7/tools/compiler/msp430_4.2.1/include" --advice:power="all" -g --define=__MSP430G2553__ --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal --preproc_with_compile --preproc_dependency="libraries/NCN_GPIO.d" --obj_directory="libraries" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


