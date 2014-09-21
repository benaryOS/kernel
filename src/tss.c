#include <constants.h>

static uint32_t tss[32]={0,0,0x10};

void tss_entry_set(uint32_t i,uint32_t val)
{
	tss[i]=val;
}

uint32_t tss_entry_get(uint32_t i)
{
	return tss[i];
}
