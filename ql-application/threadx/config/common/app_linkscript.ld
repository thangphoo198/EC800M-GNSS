
__ROM_START_ADDR = 0x802E2000;
__MAX_ROM_SIZE = 0x100000;

__RAM_START_ADDR = 0x7e197000;
__MAX_RAM_SIZE   = 0x100000;

MEMORY
{
	ROM (rx)     : ORIGIN = __ROM_START_ADDR + 8, LENGTH = __MAX_ROM_SIZE
	SRAM (rwx)     : ORIGIN = __RAM_START_ADDR, LENGTH = __MAX_RAM_SIZE
}

SECTIONS
{
	. = __ROM_START_ADDR + 8;
	.initdata : ALIGN(4)
	{ 
		KEEP(*(.initdata))
	}>ROM 
	.userStartUp :ALIGN(4)
	{
		KEEP(*(.userInit))
	}>ROM 
	.text : ALIGN(4)
	{ 
	    *(.text)
	    *(.text*)
	}>ROM 
	.rodata : ALIGN(4)
	{
	    *(.rodata)
	    *(.rodata*)
	}>ROM 
	
	. = __RAM_START_ADDR;
	.data : ALIGN(4)
	{
		PROVIDE_HIDDEN (__data_load = LOADADDR(.data));
		PROVIDE_HIDDEN (__data_start = .);
		*(.data)
		*(.data*)
		PROVIDE_HIDDEN (_edata = .);
	}>SRAM AT>ROM
	.userBootTable :ALIGN(4)
	{
		PROVIDE_HIDDEN (__userBoot_start__ = .);
		KEEP(*(.userBootTable))
		PROVIDE_HIDDEN (__userBoot_end__ = .);
	}>SRAM AT>ROM
	.userKernelTable :ALIGN(4)
	{
		PROVIDE_HIDDEN (__userKernel_start__ = .);
		KEEP(*(.userKernelTable))
		PROVIDE_HIDDEN (__userKernel_end__ = .);
	}>SRAM AT>ROM
	.appRegTable :ALIGN(4)
	{
		PROVIDE_HIDDEN (__appRegTable_start__ = .);
		KEEP(*(.appRegTable))
		PROVIDE_HIDDEN (__appRegTable_end__ = .);
	}>SRAM AT>ROM
	.ARM.exidx : ALIGN(4)
	{ 
		PROVIDE_HIDDEN (__exidx_start = .);
		*(.ARM.exidx);
		PROVIDE_HIDDEN (__exidx_end = .);
	}>SRAM AT>ROM
	
	_bin_end = LOADADDR(.ARM.exidx) + SIZEOF(.ARM.exidx)  ;
	ASSERT(_bin_end - __ROM_START_ADDR < __MAX_ROM_SIZE,"xxxx ERR:APP ROM OVERFLOW !!")

	.bss : ALIGN(4)
	{
		PROVIDE_HIDDEN (__bss_start__ = .);
		*(.bss)
		*(.bss*)
		*(COMMON)
		PROVIDE_HIDDEN (__bss_end__ = .);
	}>SRAM 
	end = .;

	ASSERT(__bss_end__ -  __RAM_START_ADDR < __MAX_RAM_SIZE,"xxxx ERR:APP RAM OVERFLOW !!")

}
