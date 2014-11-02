/*
LCR	LineControl Register
TBR	TransmittingBuffer Register
IER	InterruptEnable Register


*/


#include <constants.h>

extern int printk(const char *,...);
extern void outb(uint16_t,uint8_t);
extern int inb(uint16_t);

uint16_t offset = 0x3F8;
uint16_t baudrate = 9600; //TODO
uint8_t lbyte = 0x00;
uint8_t ubyte = 0x00;
uint16_t teiler = 0x0000;


uint16_t LCR = 0x03;
uint16_t TBR = 0x00;
uint16_t IER = 0x01;


void com(uint8_t data)
{
	
	//disable interrupts
	outb(offset+IER,0x00);

		
	outb(offset+LCR,0x80);	// set the 7th Bit in the LCR, to be prepared to set the bauds.
		
	teiler = 115200/baudrate;
	lbyte = (char)teiler;
	ubyte = (char)(teiler>>8);
	outb(offset+IER,ubyte);
	outb(offset+TBR,lbyte);
	outb(offset+LCR,0x00); // finished setting up the bauds, bring back the LCR to its original state.
	outb(offset+LCR,0x03); // Tell the computer that we want 8 bits to be one byte
			       // we could also set up the halt/stop-bits here.



	if(!(inb(offset+LCR)&0x20)){ //lets have a look if the port is ready to send a byte.
		outb(offset+TBR,data);	// It is! Lets write the byte we want to send in the TBR, the rest will be done
					// by the hardware.

	}
	
	
}

// Todo: writing bedder code. This is ugly.
//       also: be able to recive a byte
