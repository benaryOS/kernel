#include <constants.h>

extern int printk(const char *,...);
extern void halt(void);

struct cpu_state *int_exception_handler(struct cpu_state *cpu)
{
	switch(cpu->intr)
	{
		case 0x00:
			printk("#DE - Division by Zero\n");
			cpu->eip++;
			cpu->eax=42;
			break;
		case 0x01:
			printk("#DB - Debug\n");
			break;
		case 0x02:
			printk("#NMI - Non Maskable Interrupt\n");
			break;
		case 0x03:
			printk("#BP - BreakPoint\n");
			break;
		case 0x04:
			printk("#OF - Overflow\n");
			break;
		case 0x05:
			printk("#BR - Bound Range Exception\n");
			break;
		case 0x06:
			printk("#UD - Invalid Opcode\n");
			break;
		case 0x07:
			printk("#NM - Device n/a\n");
			break;
		case 0x08:
			printk("#DF - Double Fault\n");
			halt();
			break;
		case 0x09:
			printk("Coprocessor Segment Overrun");
			halt();
			break;
		case 0x0a:
			printk("#TS - Invalid TSS\n");
			break;
		case 0x0b:
			printk("#NP - Segment not Present\n");
			break;
		case 0x0c:
			printk("#SS - Stack Fault\n");
			break;
		case 0x0d:
			printk("#GP - General Protection Fault\nError Code: %d\n",(int)cpu->error);
			halt();
			break;
		case 0x0e:
			printk("#PF - Page Fault\nError Code: %d\n",(int)cpu->error);
			halt();
			break;
		case 0x10:
			printk("#MF - x87 Floating Point\n");
			break;
		case 0x11:
			printk("#AC - Alignment Check\n");
			break;
		case 0x12:
			printk("#MC - Machine Check\n");
			break;
		case 0x13:
			printk("#XF - SIMD Floating Point\n");
			break;
		case 0x0f:
		case 0x14:
		case 0x15:
		case 0x16:
		case 0x17:
		case 0x18:
		case 0x19:
		case 0x1a:
		case 0x1b:
		case 0x1c:
		case 0x1d:
		case 0x1f:
			printk("Reserved Exception");
			break;
		case 0x1e:
			printk("#SX - Security-sensitive event in Host");
			break;
		default:
			printk("impossible exception: %d\n",cpu->intr);
			break;
	}

	return cpu;
}
