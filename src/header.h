#ifndef HEADER
#define HEADER

/* INCLUDES */

#include <stdint.h>
#include <stddef.h>

#include <macros.h>

/* DATATYPES */

struct mb_header
{
	//TODO
};

/* CONSTANTS */

#define TEXT ((void *)0xb8000)
#define TEXT_WIDTH (80)
#define TEXT_HEIGHT (40)

/* FUNCTIONS */

void main(struct mb_header *);
void clear(void);

#endif /* HEADER */

