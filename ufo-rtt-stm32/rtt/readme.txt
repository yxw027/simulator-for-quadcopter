默认参数按64K FLASH，20K SRAM来配置。
当应用到具体某个型号芯片时，需要修改相应参数：

公共部分：
1. drivers/board.h
    修改 STM32_SRAM_SIZE 大小，此参数在 startup.c 中用于把全部空闲RAM用于heap，单位为KB。
    如果使用FSMC外扩SRAM，并想用做 heap，可以修改 STM32_EXT_SRAM 为 1，并设置其它容量。
	startup.c 中会自动将其它初始化为heap. 如果目标板的外扩SRAM所在的bank与例程不一样，
	还需要修改 board.c 中 FSMC_SRAM_Init 的对应配置。

MDK:
1. 生成工程后，target选项中需要选择对应的型号，并检查与 board.h的参数是否一致。

IAR:
1. 生成工程后，在 general options 中选择对应的型号，
    并根据芯片容量，修改工程对应的icf文件。
	再检查与 board.h 中的参数是否一致。

