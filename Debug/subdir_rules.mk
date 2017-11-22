################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
main.obj: ../main.cpp $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv7/tools/compiler/msp430_4.2.1/bin/cl430" -vmsp --abi=eabi --include_path="C:/ti/ccsv7/ccs_base/msp430/include" --include_path="C:/Users/IBM/Documents/GitHub/msp430-firmware-template/mdk" --include_path="C:/Users/IBM/Documents/GitHub/msp430-firmware-template/libraries" --include_path="C:/Users/IBM/Documents/GitHub/msp430-firmware-template" --include_path="C:/ti/ccsv7/tools/compiler/msp430_4.2.1/include" --advice:power="all" -g --define=__MSP430G2553__ --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal --preproc_with_compile --preproc_dependency="main.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

t_my_app.obj: ../t_my_app.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv7/tools/compiler/msp430_4.2.1/bin/cl430" -vmsp --abi=eabi --include_path="C:/ti/ccsv7/ccs_base/msp430/include" --include_path="C:/Users/IBM/Documents/GitHub/msp430-firmware-template/mdk" --include_path="C:/Users/IBM/Documents/GitHub/msp430-firmware-template/libraries" --include_path="C:/Users/IBM/Documents/GitHub/msp430-firmware-template" --include_path="C:/ti/ccsv7/tools/compiler/msp430_4.2.1/include" --advice:power="all" -g --define=__MSP430G2553__ --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal --preproc_with_compile --preproc_dependency="t_my_app.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

tmain.obj: ../tmain.cpp $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv7/tools/compiler/msp430_4.2.1/bin/cl430" -vmsp --abi=eabi --include_path="C:/ti/ccsv7/ccs_base/msp430/include" --include_path="C:/Users/IBM/Documents/GitHub/msp430-firmware-template/mdk" --include_path="C:/Users/IBM/Documents/GitHub/msp430-firmware-template/libraries" --include_path="C:/Users/IBM/Documents/GitHub/msp430-firmware-template" --include_path="C:/ti/ccsv7/tools/compiler/msp430_4.2.1/include" --advice:power="all" -g --define=__MSP430G2553__ --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal --preproc_with_compile --preproc_dependency="tmain.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


