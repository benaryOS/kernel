/*
 * clears the screen
 */
void clear(void)
{
	//FIXME: use a header
	short int *vid=(void *)0xb8000;
	int i;
	for(i=0;i<80*40;i++)
	{
		//set to zero
		vid[i]=0;
	}
}

