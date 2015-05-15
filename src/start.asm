section .multiboot

;multiboot header
dd mb_magic
dd mb_flags
dd mb_check

section .bss

align 4
stack_bot:
	resb 16384 ;our stack
stack_top:

section .text

extern main ;our c function

global _start
_start:
	mov rsp,stack_top	;initialise our stack
	push rbx			;pass the multiboot header
	call main			;start the kernel

	
global halt ;then stop
halt:
	hlt
	jmp halt

section .data

;our multiboot data
mb_flags equ 0x00000003
mb_magic equ 0x1badb002
mb_check equ -(mb_magic+mb_flags)  

