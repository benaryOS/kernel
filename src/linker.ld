/*
 * Copyright 2014 benaryorg (benaryorg@benaryos.org)
 *
 * This file is part of benaryOS.
 *
 * benaryOS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * benaryOS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with benaryOS.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

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

	. = ALIGN(4096);
	KERNEL_END = .;
}
