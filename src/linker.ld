/* start at our assembly function */
ENTRY(_start)

OUTPUT_FORMAT(elf32-i386)

SECTIONS
{
	. = 1M;
	/* place some marks */
	KERNEL_START = .;

	/* text section */
	.text BLOCK(4K) : ALIGN(4K)
	{
		/* multiboot comes first */
		*(multiboot)
		/* then the rest */
		*(.text)
	}
	.data BLOCK(4K) : ALIGN(4K)
	{
		/* our data */
		*(.data)
	}
	.rodata BLOCK(4K) : ALIGN(4K)
	{
		/* more data */
		*(.rodata)
	}
	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		/* kernel stack */
		*(.bss)
	}

	. = ALIGN(4096);
	/* endmark */
	KERNEL_END = .;
}

