//begin of the executable code
.section .text

//the C function
.extern init

//align everything
.align 4
//throw the multiboot header into the .text section
.int 0x1badb002
.int 0x0
.int -(0x1badb002+0x0)

//define the function that will be called on boot
.global _start
_start:
	//set the stack pointer to the stack
	mov $kernel_stack, %esp

	//call init <- i love those comments
	call init

	//if the init should return (e.g. kernel panic)
_stop:
	//stop interrupts
	cli
	//stop the cpu
	hlt
	
	//WHY DIDN'T THE CPU STOP?!?!?!
	jmp _stop
	//Neh. Try again.

//start data segment
.section .bss
//leave a 8192kb(?) gap
.space 8192
//`kernel_stack` will get a pointer (used a few lines up)
kernel_stack:
