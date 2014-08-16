#include <constants.h>

inline unsigned char inb(uint16_t port)
{
	unsigned char ret;
	asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
	return ret;
}
