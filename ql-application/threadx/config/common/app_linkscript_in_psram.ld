SECTIONS
{
	. = 0x7e100000;
	.initdata : 
	{ 
		KEEP(*(.initdata))
	}
	.userStartUp :
	{
		KEEP(*(.userInit))
	}
	.text : 
	{ 
	    *(.text)
	    *(.text*)
	}
	.rodata : 
	{
	    *(.rodata)
	    *(.rodata*)
	}
	.data : 
	{
		PROVIDE_HIDDEN (__data_load = LOADADDR(.data));
		PROVIDE_HIDDEN (__data_start = .);
		*(.data)
		*(.data*)
		PROVIDE_HIDDEN (_edata = .);
	}
	.userBootTable :
	{
		PROVIDE_HIDDEN (__userBoot_start__ = .);
		KEEP(*(.userBootTable))
		PROVIDE_HIDDEN (__userBoot_end__ = .);
	}
	.userKernelTable :
	{
		PROVIDE_HIDDEN (__userKernel_start__ = .);
		KEEP(*(.userKernelTable))
		PROVIDE_HIDDEN (__userKernel_end__ = .);
	}
	.appRegTable :
	{
		PROVIDE_HIDDEN (__appRegTable_start__ = .);
		KEEP(*(.appRegTable))
		PROVIDE_HIDDEN (__appRegTable_end__ = .);
	}
	.ARM.exidx : 
	{ 
		PROVIDE_HIDDEN (__exidx_start = .);
		*(.ARM.exidx);
		PROVIDE_HIDDEN (__exidx_end = .);
	}
	.bss : 
	{
		PROVIDE_HIDDEN (__bss_start__ = .);
		*(.bss)
		*(.bss*)
		*(COMMON)
		PROVIDE_HIDDEN (__bss_end__ = .);
	}
	end = .;
}