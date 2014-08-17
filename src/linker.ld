/* set the entrypoint for the execution (_start is the assembly function from start.s) */
ENTRY(_start)

/* set positions of sections in the binary */
SECTIONS
{
	/* ELFs (are executables, our kernel is one too) are loaded to 1MB) */
	. = 0x100000;

	KERNEL_START = .;

	/* section .text (executable code) comes first */
	.text : {
		/* multiboot first (for grub) */
		*(multiboot)
		/* the rest of .text */
		*(.text)
	}

	/* than data */
	.data ALIGN(4096) : {
		*(.data)
	}

	.rodata ALIGN(4096) : {
		*(.rodata)
	}

	/* this is the stack */
	.bss ALIGN(4096) : {
		*(.bss)
	}

	KERNEL_END = .;
}
