.section .text

.extern init

#define MB_MAGIC 0x1badb002
#define MB_FLAGS 0x0
#define MB_CHECKSUM -(MB_MAGIC + MB_FLAGS)

.align 4
.int    MB_MAGIC
.int    MB_FLAGS
.int    MB_CHECKSUM

.global _start
_start:
	mov $kernel_stack, %esp

	call init

_stop:
	cli
	hlt

	jmp _stop

.section .bss
.space 8192
kernel_stack:
