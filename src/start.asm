section .multiboot

;multiboot header
dd mb_magic
dd mb_flags
dd mb_check

section .bss

;our stack
global kernel_stack
kernel_stack:
	resb 16384

section .text

;our code
extern clear

;our c function
global _start
_start:
	;first call clear
	call clear
	;TODO:then start the kernel

	;then stop
.hlt:
	hlt
	jmp .hlt

section .data

;our multiboot data
mb_flags equ 0x00000003
mb_magic equ 0x1badb002
mb_check equ -(mb_magic+mb_flags)  

