#include <constants.h>

extern int putchar(int);
extern size_t strlen(const char *);

size_t printint(int i)
{
	if(!i)
	{
		putchar('0');
		return 1;
	}
	if(i<0)
	{
		putchar('-');
		return printint(-i)+1;
	}
	int j,k;
	for(k=j=0;i;i/=10,k++)
	{
		j*=10;
		j+=i%10;
	}
	for(i=0;i<k;i++)
	{
		putchar('0'+(j%10));
		j/=10;
	}
	return (size_t)i;
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
						len+=printint(va_arg(args,int));
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
