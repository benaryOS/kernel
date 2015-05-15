/* start at our assembly function */
ENTRY(_start)

/* we need 32-bit elfs even if it contains 64-bit code so it is loaded */
OUTPUT_FORMAT(elf32-i386)

SECTIONS
{
	/* place some marks */
	KERNEL_START = .;

	/* text section */
	.text : {
		/* multiboot comes first */
		*(.multiboot)
		/* then the rest */
		*(.text)
	}
	.data ALIGN(4096) : {
		/* our data */
		*(.data)
	}
	.rodata ALIGN(4096) : {
		/* more data */
		*(.rodata)
	}
	.bss ALIGN(4096) : {
		/* kernel stack */
		*(.bss)
	}
	. = ALIGN(4096);
	/* endmark */
	KERNEL_END = .;
}

