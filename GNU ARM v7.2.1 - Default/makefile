################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include protocol/bluetooth/lib/EFR32MG21/GCC/subdir.mk
-include platform/emlib/src/subdir.mk
-include platform/emdrv/sleep/src/subdir.mk
-include platform/emdrv/nvm3/src/subdir.mk
-include platform/Device/SiliconLabs/EFR32MG21/Source/GCC/subdir.mk
-include platform/Device/SiliconLabs/EFR32MG21/Source/subdir.mk
-include hardware/kit/common/drivers/subdir.mk
-include hardware/kit/common/bsp/subdir.mk
-include app/bluetooth/common/util/subdir.mk
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
all: MG21inPlaceOTA.axf

# Tool invocations
MG21inPlaceOTA.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m33 -mthumb -T "/Users/clfilho/SimplicityStudio/ZIGBEE/MG21inPlaceOTA/efr32mg21a010f1024im32.ld" -Xlinker --gc-sections -Xlinker -Map="MG21inPlaceOTA.map" -mfpu=fpv5-sp-d16 -mfloat-abi=hard --specs=nano.specs -o MG21inPlaceOTA.axf -Wl,--start-group "./app/bluetooth/common/util/infrastructure.o" "./app.o" "./application_properties.o" "./btl_interface.o" "./btl_interface_storage.o" "./gatt_db.o" "./init_app.o" "./init_board.o" "./init_mcu.o" "./main.o" "./pti.o" "./hardware/kit/common/bsp/bsp_stk.o" "./hardware/kit/common/drivers/retargetio.o" "./hardware/kit/common/drivers/retargetserial.o" "./platform/Device/SiliconLabs/EFR32MG21/Source/GCC/startup_efr32mg21.o" "./platform/Device/SiliconLabs/EFR32MG21/Source/system_efr32mg21.o" "./platform/emdrv/nvm3/src/nvm3_default.o" "./platform/emdrv/nvm3/src/nvm3_hal_flash.o" "./platform/emdrv/nvm3/src/nvm3_lock.o" "./platform/emdrv/sleep/src/sleep.o" "./platform/emlib/src/em_assert.o" "./platform/emlib/src/em_burtc.o" "./platform/emlib/src/em_cmu.o" "./platform/emlib/src/em_core.o" "./platform/emlib/src/em_cryotimer.o" "./platform/emlib/src/em_crypto.o" "./platform/emlib/src/em_emu.o" "./platform/emlib/src/em_eusart.o" "./platform/emlib/src/em_gpio.o" "./platform/emlib/src/em_i2c.o" "./platform/emlib/src/em_msc.o" "./platform/emlib/src/em_rmu.o" "./platform/emlib/src/em_rtcc.o" "./platform/emlib/src/em_se.o" "./platform/emlib/src/em_system.o" "./platform/emlib/src/em_timer.o" "./platform/emlib/src/em_usart.o" "/Users/clfilho/SimplicityStudio/ZIGBEE/MG21inPlaceOTA/protocol/bluetooth/lib/EFR32MG21/GCC/libbluetooth.a" "/Users/clfilho/SimplicityStudio/ZIGBEE/MG21inPlaceOTA/platform/emdrv/nvm3/lib/libnvm3_CM33_gcc.a" "/Users/clfilho/SimplicityStudio/ZIGBEE/MG21inPlaceOTA/protocol/bluetooth/lib/EFR32MG21/GCC/libmbedtls.a" "/Users/clfilho/SimplicityStudio/ZIGBEE/MG21inPlaceOTA/platform/radio/rail_lib/autogen/librail_release/librail_efr32xg21_gcc_release.a" "/Users/clfilho/SimplicityStudio/ZIGBEE/MG21inPlaceOTA/protocol/bluetooth/lib/EFR32MG21/GCC/binapploader.o" -lm -Wl,--end-group -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: MG21inPlaceOTA.hex'
	arm-none-eabi-objcopy -O ihex "MG21inPlaceOTA.axf" "MG21inPlaceOTA.hex"
	@echo ' '

	@echo 'Building bin file: MG21inPlaceOTA.bin'
	arm-none-eabi-objcopy -O binary "MG21inPlaceOTA.axf" "MG21inPlaceOTA.bin"
	@echo ' '

	@echo 'Building s37 file: MG21inPlaceOTA.s37'
	arm-none-eabi-objcopy -O srec "MG21inPlaceOTA.axf" "MG21inPlaceOTA.s37"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "MG21inPlaceOTA.axf" -A
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) MG21inPlaceOTA.axf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
