################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv7/tools/compiler/msp430_4.2.1

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./main.obj" \
"./t_my_app.obj" \
"./tmain.obj" \
"./Lcd updated/library/gpio.obj" \
"./Lcd updated/main.obj" \
"./libraries/I2C.obj" \
"./libraries/LiquidCrystal.obj" \
"./libraries/NCN_GPIO.obj" \
"../lnk_msp430g2553.cmd" \
"../mdk/np_module_mdk_v1.lib" \
$(GEN_CMDS__FLAG) \
-l"C:/Users/IBM/Documents/GitHub/msp430-firmware-template/mdk/np_module_mdk_v1.lib" \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include Lcd\ updated/library/subdir_vars.mk
-include Lcd\ updated/subdir_vars.mk
-include libraries/subdir_vars.mk
-include mdk/subdir_vars.mk
-include subdir_rules.mk
-include Lcd\ updated/library/subdir_rules.mk
-include Lcd\ updated/subdir_rules.mk
-include libraries/subdir_rules.mk
-include mdk/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
msp430-firmware-template.out \

EXE_OUTPUTS__QUOTED += \
"msp430-firmware-template.out" \


# All Target
all: msp430-firmware-template.out

# Tool invocations
msp430-firmware-template.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: MSP430 Linker'
	"C:/ti/ccsv7/tools/compiler/msp430_4.2.1/bin/cl430" -vmsp --abi=eabi --advice:power="all" -g --define=__MSP430G2553__ --diag_warning=225 --display_error_number --diag_wrap=off --printf_support=minimal -z -m"msp430-firmware-template.map" --heap_size=80 --stack_size=80 -i"C:/ti/ccsv7/ccs_base/msp430/include" -i"C:/Users/IBM/Documents/GitHub/msp430-firmware-template/mdk" -i"C:/Users/IBM/Documents/GitHub/msp430-firmware-template" -i"C:/Users/IBM/Documents/GitHub/msp430-firmware-template/libraries" -i"C:/ti/ccsv7/tools/compiler/msp430_4.2.1/lib" -i"C:/ti/ccsv7/tools/compiler/msp430_4.2.1/include" --reread_libs --warn_sections --display_error_number --diag_wrap=off --xml_link_info="msp430-firmware-template_linkInfo.xml" --rom_model -o "msp430-firmware-template.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '
	@$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)
	-$(RM) "main.obj" "t_my_app.obj" "tmain.obj" "Lcd updated\library\gpio.obj" "Lcd updated\main.obj" "libraries\I2C.obj" "libraries\LiquidCrystal.obj" "libraries\NCN_GPIO.obj" 
	-$(RM) "t_my_app.d" "Lcd updated\library\gpio.d" "libraries\NCN_GPIO.d" 
	-$(RM) "main.d" "tmain.d" "Lcd updated\main.d" "libraries\I2C.d" "libraries\LiquidCrystal.d" 
	-@echo 'Finished clean'
	-@echo ' '

post-build:
	-@echo 'Create flash image: TI-TXT'
	-"C:/ti/ccsv7/tools/compiler/msp430_4.2.1/bin/hex430" --ti_txt "msp430-firmware-template.out" -o "msp430-firmware-template.txt" -order MS -romwidth 16
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

