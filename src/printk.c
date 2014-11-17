/*
 * Copyright 2014 benaryorg (benaryorg@benaryos.org)
 *
 * This file is part of benaryOS.
 *
 * benaryOS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * benaryOS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with benaryOS.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <constants.h>

extern int putchar(int);
extern size_t strlen(const char *);

size_t print_base(uint32_t n,int base)
{
	static const char *digits="0123456789abcdefghijklmnopqrstuvwxyz";
	int count=0;
	int sign=base<0;
	if(sign)
	{
		base=-base;
	}
	if(base<2||base>=38)
	{
		return count;
	}
	if(sign&&((int)n)<0)
	{
		n=-(int)n;
		putchar('-');
		count++;
	}
	if(!n)
	{
		putchar('0');
		count++;
		return count;
	}
	uint32_t nbase;
	for(nbase=1;nbase<=(sign?(int)n:n)/base;nbase*=base);
	do
	{
		putchar(digits[(n/nbase)%base]);
		count++;
	}while(nbase/=base);
	return count;
}

int printk(const char *format,...)
{
	va_list args;
	va_start(args,format);

	size_t len;
	int i;
	for(len=i=0;i<strlen(format);i++)
	{
		switch(format[i])
		{
			case '%':
				i++;
				switch(format[i])
				{
					case 'd':
					{
						len+=print_base(va_arg(args,int),-10);
						break;
					}
					case 'u':
					{
						len+=print_base(va_arg(args,int),10);
						break;
					}
					case 'x':
					{
						len+=print_base(va_arg(args,int),16);
						break;
					}
					case 'c':
					{
						putchar(va_arg(args,int));
						len++;
						break;
					}
					case 's':
					{
						int j;
						char *str=va_arg(args,char *);
						for(j=0;j<strlen(str);j++,len++)
						{
							putchar(str[j]);
						}
						break;
					}
					case '%':
					{
						putchar('%');
						len++;
						break;
					}
					default:
					{
						continue;
					}
				}
				break;
			default:
				putchar(format[i]);
				len++;
				break;
		}
	}
	va_end(args);
	return len;
}
