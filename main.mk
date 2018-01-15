CC = arm-none-eabi-gcc
SIZE = arm-none-eabi-size

COMMON_FLAGS = -mcpu=cortex-m3 -mthumb -mfloat-abi=soft -g

OPT = -Os

DEFINES = -DSTM32L1XX_MDP -DUSE_STDPERIPH_DRIVER

INCLUDE += -I CMSIS/Device/ST/STM32L1xx/Include -I CMSIS/Include -I./ -I STM32L1xx_StdPeriph_Driver/inc

CFLAGS := $(COMMON_FLAGS) $(INCLUDE) $(DEFINES) $(OPT) -std=gnu11 -Wall -pipe -ffunction-sections -fdata-sections

SUBMAKEFILES := main/main.mk startup_code/startup_code.mk SEGGER/SEGGER.mk STM32L1xx_StdPeriph_Driver/library.mk

BUILD_DIR  := build

TARGET_DIR := .

LIBC_SPECS = --specs=nano.specs
#LIBC_SPECS = --specs=nosys.specs #see newlib documentation if you need more functionality

LDFLAGS = $(COMMON_FLAGS) $(LIBC_SPECS) -T linker_script/STM32_flash.ld -Wl,--gc-sections

TARGET := main.elf

SOURCES := \
    CMSIS/Device/ST/STM32L1xx/Source/Templates/system_stm32l1xx.c

size: main.elf
	$(SIZE) main.elf
