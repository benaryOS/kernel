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
	typedefs
*/
typedef unsigned int size_t;

typedef signed char int_8t;
typedef signed short int int_16t;
typedef signed long int int_32t;
typedef signed long long int int_64t;

typedef unsigned int8_t uint8_t;
typedef unsigned int16_t uint16_t;
typedef unsigned int32_t uint32_t;
typedef unsigned int64_t uint64_t;

#endif /** __BENARYOS_CONSTANTS__ **/
