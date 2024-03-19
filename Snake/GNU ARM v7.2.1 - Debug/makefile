################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include emlib/subdir.mk
-include drivers/subdir.mk
-include CMSIS/EFM32GG/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: Snake.axf

# Tool invocations
Snake.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m3 -mthumb -T "Snake.ld" -Xlinker --gc-sections -Xlinker -Map="Snake.map" --specs=nano.specs -o Snake.axf "./CMSIS/EFM32GG/startup_gcc_efm32gg.o" "./CMSIS/EFM32GG/system_efm32gg.o" "./drivers/segmentlcd.o" "./emlib/bsp_stk_buttons.o" "./emlib/em_cmu.o" "./emlib/em_core.o" "./emlib/em_gpio.o" "./emlib/em_lcd.o" "./emlib/em_system.o" "./emlib/em_timer.o" "./src/functions.o" "./src/main.o" "./src/segmentlcd_individual.o" -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: Snake.hex'
	arm-none-eabi-objcopy -O ihex "Snake.axf" "Snake.hex"
	@echo ' '

	@echo 'Building bin file: Snake.bin'
	arm-none-eabi-objcopy -O binary "Snake.axf" "Snake.bin"
	@echo ' '

	@echo 'Building s37 file: Snake.s37'
	arm-none-eabi-objcopy -O srec "Snake.axf" "Snake.s37"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "Snake.axf" -A
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) Snake.axf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
