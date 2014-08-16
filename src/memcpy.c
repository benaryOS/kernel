#include <constants.h>

void *memcpy(void *dst,void *src,size_t n)
{
	char *d=(char *)dst;
	char *s=(char *)src;
	size_t i;
	for(i=0;i<n;i++)
	{
		d[i]=s[i];
	}
	return dst;
}
