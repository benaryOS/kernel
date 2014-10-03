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

//multiboot header defines
#define MB_MAGIC 0x1badb002
#define MB_FLAGS 0x0
#define MB_CHECKSUM -(MB_MAGIC+MB_FLAGS)

//first place the multiboot header (for grub)
.section multiboot

//align everything
.align 4
//throw the multiboot header into the .text section
.int MB_MAGIC
.int MB_FLAGS
.int MB_CHECKSUM

//begin of the executable code
.section .text

//the C function
.extern init

//define the function that will be called on boot
.global _start
_start:
	//set the stack pointer to the stack
	mov $kernel_stack, %esp

	//throw the multiboot structure on the stack
	push %ebx

	//call init <- i love those comments
	call init

	//if the init should return (e.g. should NEVER happen)
_stop:
	//stop interrupts
	cli
	//stop the cpu
	hlt
	
	//WHY DIDN'T THE CPU STOP?!?!?!
	jmp _stop
	//Neh. Try again.


//some interrupts have an error code. if there is no error code pushed, we get a problem when popping it….

.macro intr_stub nr
.global intr_stub_\nr
	intr_stub_\nr:
	pushl $0
	pushl $\nr
	jmp intr_common_handler
.endm
		  
.macro intr_stub_error_code nr
.global intr_stub_\nr
	intr_stub_\nr:
	pushl $\nr
	jmp intr_common_handler
.endm

//exceptions
intr_stub 0
intr_stub 1
intr_stub 2
intr_stub 3
intr_stub 4
intr_stub 5
intr_stub 6
intr_stub 7
intr_stub_error_code 8
intr_stub 9
intr_stub_error_code 10
intr_stub_error_code 11
intr_stub_error_code 12
intr_stub_error_code 13
intr_stub_error_code 14
intr_stub 15
intr_stub 16
intr_stub_error_code 17
intr_stub 18

//hardware interrupts
intr_stub 32
intr_stub 33
intr_stub 34
intr_stub 35
intr_stub 36
intr_stub 37
intr_stub 38
intr_stub 39
intr_stub 40
intr_stub 41
intr_stub 42
intr_stub 43
intr_stub 44
intr_stub 45
intr_stub 46
intr_stub 47

//syscall
intr_stub 48

.extern int_handler
intr_common_handler:
	//save all registers (cpu already saved some)
	push %ebp
	push %edi
	push %esi
	push %edx
	push %ecx
	push %ebx
	push %eax

	//load kernel data-segments
	mov $0x10, %ax
	mov %ax, %ds
	mov %ax, %es

	//throw our stack pointer (where the saved registers are) on the stack
	push %esp
	//call our C function
	call int_handler
	//restore the stack (and cpu_state) our handler returned
	mov %eax, %esp

	//load user data-segments
	mov $0x23, %ax
	mov %ax, %ds
	mov %ax, %es

	//restore our cpu state
	pop %eax
	pop %ebx
	pop %ecx
	pop %edx
	pop %esi
	pop %edi
	pop %ebp

	//errorcode and interruptnumber
	add $8, %esp

	//return
	iret

//start data segment
.section .bss
//leave a 8192kb(?) gap
.space 8192
//`kernel_stack` will become a pointer (used a few lines up)
kernel_stack:
