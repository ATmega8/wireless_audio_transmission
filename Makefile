#工程名
PROJ_NAME=wireless_audio

#要编译的文件
SRCS  = stm32f4xx_it.c system_stm32f4xx.c
SRCS += main.c

SRCS += ../STM32F4xx_DSP_StdPeriph_Lib_V1.5.1/Libraries/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc_ride7/startup_stm32f40_41xxx.s

#链接脚本路径
LDSCRIPT_INC = ../ldscrpit

#标准库位置
STDPERIPHSRC= ../STM32F4xx_DSP_StdPeriph_Lib_V1.5.1/Libraries/STM32F4xx_StdPeriph_Driver

#C编译器
CC=arm-none-eabi-gcc

#链接器
LD=arm-none-eabi-gcc

#打包器
AR=arm-none-eabi-ar

#二进制文件生成
OBJCOPY=arm-none-eabi-objcopy

#SIZE
SIZE=arm-none-eabi-size

#make
MAKE=make

#编译选项
CFLAGS  = -nostartfiles -Wl,--gc-sections -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 
CFLAGS += -mfloat-abi=hard -mabi=aapcs
CFLAGS += -I inc
CFLAGS += -I ../STM32F4xx_DSP_StdPeriph_Lib_V1.5.1/Libraries/STM32F4xx_StdPeriph_Driver/inc
CFLAGS += -I ../STM32F4xx_DSP_StdPeriph_Lib_V1.5.1/Libraries/CMSIS/Device/ST/STM32F4xx/Include
CFLAGS += -I ../STM32F4xx_DSP_StdPeriph_Lib_V1.5.1/Libraries/CMSIS/Include
CFLAGS += -D USE_STDPERIPH_DRIVER -D STM32F40_41xxx

#链接选项
LDFLAGS = -nostartfiles -Wl,--gc-sections -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mabi=aapcs

vpath %.c src
vpath %.a $(STDPERIPHSRC)

.PHONY: lib proj

all: lib proj

lib:
	$(MAKE) -C $(STDPERIPHSRC)

proj:$(PROJ_NAME).elf

$(PROJ_NAME).elf:$(SRCS)
	$(CC) $(CFLAGS) $^ -o $@ -L$(STDPERIPHSRC) -lstm32f405 -L$(LDSCRIPT_INC) -Tstm32f4_flash.ld
	$(OBJCOPY) -O ihex $(PROJ_NAME).elf $(PROJ_NAME).hex
	$(OBJCOPY) -O binary $(PROJ_NAME).elf $(PROJ_NAME).bin
	$(SIZE) $(PROJ_NAME).elf
	
program: $(PROJ_NAME).bin
	st-flash write $(PROJ_NAME).bin 0x08000000

clean:
	find ./ -name '*~' | xargs rm -f	
	rm -f *.o
	rm -f $(PROJ_NAME).elf
	rm -f $(PROJ_NAME).hex
	rm -f $(PROJ_NAME).bin
	rm -f $(PROJ_NAME).map


