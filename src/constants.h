#ifndef __BENARYOS_CONSTANTS__
#define __BENARYOS_CONSTANTS__

/*
	typedefs
*/
typedef unsigned int size_t;

typedef signed char int8_t;
typedef signed short int int16_t;
typedef signed long int int32_t;
typedef signed long long int int64_t;

typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned long int uint32_t;
typedef unsigned long long int uint64_t;

/*
	va_args
*/
typedef __builtin_va_list       va_list;
#define va_start(ap, X)         __builtin_va_start(ap, X)
#define va_arg(ap, type)        __builtin_va_arg(ap, type)
#define va_end(ap)              __builtin_va_end(ap)

/*
	buffers (text and later video buffer)
*/
#define TEXT_BUFFER ((char *)0xb8000)
#define TEXT_WIDTH 80
#define TEXT_HEIGHT 25

/*
	GDT
*/
#define GDT_FLAG_DATASEG	0x02
#define GDT_FLAG_CODESEG	0x0a
#define GDT_FLAG_TSS		0x09
 
#define GDT_FLAG_SEGMENT	0x10
#define GDT_FLAG_RING0		0x00
#define GDT_FLAG_RING3		0x60
#define GDT_FLAG_PRESENT	0x80

#define GDT_FLAG_4K_GRAN	0x800
#define GDT_FLAG_32_BIT		0x400

#define GDT_SIZE			0x06

/*
	IDT
*/
#define IDT_SIZE			256

#define IDT_TASK_GATE		0x9
#define IDT_INTERRUPT_GATE	0xe
#define IDT_TRAP_GATE		0xf

/*
	PMM
*/
#define PMM_BITMAP_SIZE ((1024*1024)/32)

struct idt_desc
{
	uint16_t lsb_handler;
	uint16_t selector;
	uint8_t reserved;
	uint8_t access;
	uint16_t msb_handler;
};

/*
	paging
*/
#define VMM_PAGEDIR (((uint32_t)(0x400*0x400*0x400-0x400*0x400))*0x4)

#define PAGING_PRESENT		0x01
#define PAGING_WRITE		0x02
#define PAGING_USER			0x04

typedef uint32_t page_t;
typedef page_t *page_table_t;
typedef page_table_t *page_directory_t;

struct page_context
{
	page_directory_t directory;
};

/*
	interrupts
*/
struct cpu_state
{
	uint32_t eax;
	uint32_t ebx;
	uint32_t ecx;
	uint32_t edx;
	uint32_t esi;
	uint32_t edi;
	uint32_t ebp;

	uint32_t intr;
	uint32_t error;

	uint32_t eip;
	uint32_t cs;
	uint32_t eflags;
	uint32_t esp;
	uint32_t ss; 
};

/*
	tasks
*/
struct task
{
	struct task *next;
	struct page_context context;
	uint32_t pid;
	struct cpu_state *cpu;
};

/*
	PIDs
*/
#define PID_BITMAP_SIZE (128)

/*
	multiboot structure
*/
struct multiboot
{
	uint32_t mbs_flags;
	uint32_t mbs_mem_lower;
	uint32_t mbs_mem_upper;
	uint32_t mbs_bootdevice;
	uint32_t mbs_cmdline;
	uint32_t mbs_mods_count;
	struct mb_module
	{
		void *start;
		void *end;
		void *name;
		void *reserved;
	} *mbs_mods_addr;
	uint64_t mbs_syms1;
	uint64_t mbs_syms2;
	uint32_t mbs_mmap_length;
	struct multiboot_mmap
	{
		uint32_t size;
		uint64_t base;
		uint64_t length;
		uint32_t type;
	} *mbs_mmap_addr;
	uint32_t mbs_drives_length;
	uint32_t mbs_drives_addr;
	uint32_t mbs_config_table;
	uint32_t mbs_boot_loader_name;
	uint32_t mbs_apm_table;
	uint32_t mbs_vbe_control_info;
	uint32_t mbs_vbe_mode_info;
	uint16_t mbs_vbe_mode;
	uint16_t mbs_vbe_interface_seg;
	uint16_t mbs_vbe_interface_off;
	uint16_t mbs_vbe_interface_len;
};

/*
	elfs
*/
#define ELF_MAGIC (0x464C457F)
 
struct elf_header
{
	uint32_t magic;
	uint32_t version;
	uint64_t reserved;
	uint64_t version2;
	uint32_t entry;
	uint32_t ph_offset;
	uint32_t sh_offset;
	uint32_t flags;
	uint16_t header_size;
	uint16_t ph_entry_size;
	uint16_t ph_entry_count;
	uint16_t sh_entry_size;
	uint16_t sh_entry_count;
	uint16_t sh_str_table_index;
} __attribute__((packed));

struct elf_header_program
{
	uint32_t type;
	uint32_t offset;
	uint32_t virt_addr;
	uint32_t phys_addr;
	uint32_t file_size;
	uint32_t mem_size;
	uint32_t flags;
	uint32_t alignment;
} __attribute__((packed));

/*
	syscalls
*/
#define SYSCALL_PUTCHAR			0x0001

#endif /** __BENARYOS_CONSTANTS__ **/
