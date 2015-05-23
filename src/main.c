#include <header.h>

/*
 * the kernel
 */
void main(struct mb_header *mb)
{
	//firstly, clear the screen
	clear();
	char *str;
	for(str="Meow! This is a very long teststring!";*str;str++)
	{
		putchar(*str);
	}
}

