#include "uart_registers.h"

#define REG(x)(*((volatile unsigned int *)(x)))

static inline void
write32(unsigned int address, unsigned int value)
{
        REG(address) = value;
}

/* Read an unsigned int from a memory address */
static inline unsigned int
read32(unsigned int address)
{
        return REG(address);
}


void putchar(int c){
	write32(UART0_BASE,c);
}

void puts(char *r){
	int i =0;
	while( r[i] != 0){
		putchar(r[i]);
		i++;
	}
}

int iamzero;
const int iamtwo =2;

void putschar_hex(unsigned char c){
	//assert(c < 16)
	if (c < 10){
		putchar('0' + c);
	} else  if (c < 16){
		c -= 10;
		putchar('a' + c );
	} else { 
		putchar('F');
	}
}

void puts_hexs(int value){
	int x =8;/* 4 bytes */
	unsigned char v;
	puts("0x");
	while(x > 0){
		v = (value >> (x << 2)) & 0xF;
		putschar_hex(v);
		x--;
	}
}

int 
main (int argc, char **argv)
{
	int x,y;
	
//	x= 0xaaaaaa;
	x= 0xaaaaaaaa;
	y= 0xbbbbbbbb;
	puts("x =");
	puts_hexs(x);
	puts("\r\n");
	puts("&x =");
	puts_hexs((unsigned int)&x);
	puts("\r\n");
	puts("y =");
	puts_hexs(y);
	puts("\r\n");
	puts("&y =");
	puts_hexs((unsigned int)&y);
	puts("\r\n");
	
	puts_hexs(0xffff);
	puts("\r\n");
	if (iamzero != 0){
		puts("int test failed!\r\n");
		puts_hexs(iamzero);
		puts("\r\n");
		puts_hexs((unsigned int)&iamzero);
		puts("\r\n");
	}
	if (iamtwo != 2){
		puts("const int test failed!\r\n");
		puts_hexs(iamtwo);
		puts("\r\n");
		puts_hexs((unsigned int)&iamtwo);
		puts("\r\n");
	}
	puts("hello!\r\n");
	
	return 0;
};
