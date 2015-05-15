#ifndef HEADER
#define HEADER

/* INCLUDES */

#include <stdint.h>
#include <stddef.h>

/* DATATYPES */

struct mb_header
{
	//TODO
};

/* CONSTANTS */

#define TEXTBUFFER ((void *)0xb8000)

/* FUNCTIONS */

void main(struct mb_header *);
void clear(void);

#endif /* HEADER */

