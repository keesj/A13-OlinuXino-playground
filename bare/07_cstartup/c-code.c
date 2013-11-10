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

int 
main (int argc, char **argv)
{
	if (iamzero != 0){
		puts("int test failed!\r\n");
	}
	if (iamtwo != 2){
		puts("const int test failed!\r\n");
	}
	puts("hello!\r\n");
	
	return 0;
};

