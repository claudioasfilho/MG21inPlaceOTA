################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../platform/emdrv/sleep/src/sleep.c 

OBJS += \
./platform/emdrv/sleep/src/sleep.o 

C_DEPS += \
./platform/emdrv/sleep/src/sleep.d 


# Each subdirectory must supply rules for building sources it contributes
platform/emdrv/sleep/src/sleep.o: ../platform/emdrv/sleep/src/sleep.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU ARM C Compiler'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m33 -mthumb -std=c99 '-DHAL_CONFIG=1' '-DNVM3_DEFAULT_NVM_SIZE=24576' '-D__StackLimit=0x20000000' '-D__STACK_SIZE=0x800' '-D__HEAP_SIZE=0xD00' '-DEFR32MG21A010F1024IM32=1' -I"/Users/clfilho/SimplicityStudio/ZIGBEE/MG21inPlaceOTA/platform/emlib/src" -I"/Applications/Simplicity Studio.app/Contents/MacOS/GNU ARM v7.2.1 - Default/$/platform/bootloader" -I"/Applications/Simplicity Studio.app/Contents/Eclipse/developer/sdks/gecko_sdk_suite/v2.6//platform/bootloader/api" -I"/Users/clfilho/SimplicityStudio/ZIGBEE/MG21inPlaceOTA/platform/Device/SiliconLabs/EFR32MG21/Include" -I"/Users/clfilho/SimplicityStudio/ZIGBEE/MG21inPlaceOTA/platform/emlib/inc" -I"/Users/clfilho/SimplicityStudio/ZIGBEE/MG21inPlaceOTA/platform/CMSIS/Include" -I"/Users/clfilho/SimplicityStudio/ZIGBEE/MG21inPlaceOTA/hardware/kit/common/bsp" -I"/Users/clfilho/SimplicityStudio/ZIGBEE/MG21inPlaceOTA/hardware/kit/common/drivers" -I"/Users/clfilho/SimplicityStudio/ZIGBEE/MG21inPlaceOTA/platform/emdrv/nvm3/src" -I"/Users/clfilho/SimplicityStudio/ZIGBEE/MG21inPlaceOTA/platform/emdrv/uartdrv/inc" -I"/Users/clfilho/SimplicityStudio/ZIGBEE/MG21inPlaceOTA/protocol/bluetooth/ble_stack/inc/common" -I"/Users/clfilho/SimplicityStudio/ZIGBEE/MG21inPlaceOTA/hardware/kit/EFR32MG21_BRD4181A/config" -I"/Users/clfilho/SimplicityStudio/ZIGBEE/MG21inPlaceOTA/platform/emdrv/sleep/inc" -I"/Users/clfilho/SimplicityStudio/ZIGBEE/MG21inPlaceOTA/platform/Device/SiliconLabs/EFR32MG21/Source/GCC" -I"/Users/clfilho/SimplicityStudio/ZIGBEE/MG21inPlaceOTA/platform/halconfig/inc/hal-config" -I"/Users/clfilho/SimplicityStudio/ZIGBEE/MG21inPlaceOTA/platform/radio/rail_lib/protocol/ble" -I"/Users/clfilho/SimplicityStudio/ZIGBEE/MG21inPlaceOTA/app/bluetooth/common/util" -I"/Users/clfilho/SimplicityStudio/ZIGBEE/MG21inPlaceOTA/platform/radio/rail_lib/common" -I"/Users/clfilho/SimplicityStudio/ZIGBEE/MG21inPlaceOTA/platform/emdrv/nvm3/inc" -I"/Users/clfilho/SimplicityStudio/ZIGBEE/MG21inPlaceOTA/hardware/kit/common/halconfig" -I"/Users/clfilho/SimplicityStudio/ZIGBEE/MG21inPlaceOTA/platform/radio/rail_lib/chip/efr32/efr32xg2x" -I"/Users/clfilho/SimplicityStudio/ZIGBEE/MG21inPlaceOTA/platform/bootloader/api" -I"/Users/clfilho/SimplicityStudio/ZIGBEE/MG21inPlaceOTA/platform/emdrv/gpiointerrupt/inc" -I"/Users/clfilho/SimplicityStudio/ZIGBEE/MG21inPlaceOTA/platform/emdrv/common/inc" -I"/Users/clfilho/SimplicityStudio/ZIGBEE/MG21inPlaceOTA/platform/emdrv/sleep/src" -I"/Users/clfilho/SimplicityStudio/ZIGBEE/MG21inPlaceOTA/protocol/bluetooth/ble_stack/inc/soc" -I"/Users/clfilho/SimplicityStudio/ZIGBEE/MG21inPlaceOTA/platform/Device/SiliconLabs/EFR32MG21/Source" -I"/Users/clfilho/SimplicityStudio/ZIGBEE/MG21inPlaceOTA/platform/radio/rail_lib/protocol/ieee802154" -I"/Users/clfilho/SimplicityStudio/ZIGBEE/MG21inPlaceOTA" -I"/Users/clfilho/SimplicityStudio/ZIGBEE/MG21inPlaceOTA/platform/bootloader" -O2 -Wall -c -fmessage-length=0 -ffunction-sections -fdata-sections -mfpu=fpv5-sp-d16 -mfloat-abi=hard -MMD -MP -MF"platform/emdrv/sleep/src/sleep.d" -MT"platform/emdrv/sleep/src/sleep.o" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


