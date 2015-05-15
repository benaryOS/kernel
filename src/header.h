#ifndef HEADER
#define HEADER

/* INCLUDES */

#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>

#include <macros.h>

/* DATATYPES */

struct mb_header
{
	//TODO
};

/* CONSTANTS */

#define EOF (-1)

#define TEXT ((void *)0xb8000)
#define TEXT_WIDTH (80)
#define TEXT_HEIGHT (40)

/* FUNCTIONS */

//main

void main(struct mb_header *);

//textio

void clear(void);

#endif /* HEADER */

