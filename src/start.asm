section multiboot

;our multiboot data
MB_FLAGS equ 0x00000003
MB_MAGIC equ 0x1badb002
MB_CHECK equ -(MB_MAGIC+MB_FLAGS)  

;multiboot header
align 4
	dd MB_MAGIC
	dd MB_FLAGS
	dd MB_CHECK

section .bss,nobits

align 4
stack_bot:
	times 2048 dd 0 ;our stack
stack_top:

section .text

extern main ;our c function

global _start
_start:
	mov esp,stack_top	;initialise our stack
	push ebx			;pass the multiboot header
	call main			;start the kernel
	
global halt ;then stop
halt:
	hlt
	jmp halt

section .data


