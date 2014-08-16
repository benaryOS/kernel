#ifndef __BENARYOS_CONSTANTS__
#define __BENARYOS_CONSTANTS__

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
	GDT flags
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

#define GDT_SIZE			0x08

/*
	typedefs
*/
typedef unsigned int size_t;

typedef signed char int_8t;
typedef signed short int int_16t;
typedef signed long int int_32t;
typedef signed long long int int_64t;

typedef unsigned char uint_8t;
typedef unsigned short int uint_16t;
typedef unsigned long int uint_32t;
typedef unsigned long long int uint_64t;

#endif /** __BENARYOS_CONSTANTS__ **/
