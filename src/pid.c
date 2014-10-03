#include <constants.h>

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

uint32_t *task_pid_bitmap[PID_BITMAP_SIZE];

extern void *pmm_alloc_block(void);
extern void halt(void);
extern size_t printk(const char *,...);

uint32_t pid_get(void)
{
	size_t i,j,k;
choose_map:
	for(i=0;i<PID_BITMAP_SIZE;i++)
	{
		if(task_pid_bitmap[i])
		{
			for(j=0;j<0x400;j++)
			{
				if(~task_pid_bitmap[i][j])
				{
					for(k=0;k<0x20;k++)
					{
						if(!((task_pid_bitmap[i][j]>>k)&0x01))
						{
							task_pid_bitmap[i][j]|=1<<k;
							return (i*0x400+j)*0x20+k;
						}
					}
				}
			}
		}
	}
	for(i=0;i<PID_BITMAP_SIZE;i++)
	{
		if(!task_pid_bitmap[i])
		{
			task_pid_bitmap[i]=pmm_alloc_block();
			goto choose_map;
		}
	}
	printk("no more pids left\n");
	halt();
	return 0;
}

void pid_free(uint32_t pid)
{
	task_pid_bitmap[(pid/0x8000)%PID_BITMAP_SIZE][(pid/0x20)%0x400]&=~(0x1<<(pid%0x20));
}
