; MULTIBOOT

;; FLAGS

MBALIGN		equ		0001h
MEMINFO		equ		0002h

;; HEADER DEFINITIONS

FLAGS		equ		MBALIGN|MEMINFO
MAGIC		equ		1badb002h
CHECKSUM	equ		-(MAGIC+FLAGS)

;; HEADER

section .multiboot ; create multiboot section (must be first in binary)
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM


; STACK

section .bootstrap_stack, nobits
align 4
stack_bottom:
resb 16384 ; reserve 16kib
stack_top:

; ENTRY

section .text
global _start
_start:

	; set stack
	mov esp, stack_top

	; call rust code
	extern kernel_main
	call kernel_main
 
	; disable interrupts
	cli

	; endless loop
.hang:
	; try to stop cpu
	hlt
	jmp .hang

