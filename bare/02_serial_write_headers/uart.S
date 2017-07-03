	@
	@ Sample assembly for writing data to the UART
	@
	@ This whole sample is mainly about documenting part of the
	@ file.
	@ We use the c preprosessor here so we can use defines and includes
	@ if you do not want to do this you need to define your constants
	@ in a different way:
	@ 
	@.equ    UART0_BASE,0x01C28400 @define a constant that point to the UART register
	@
#include "uart_registers.h"

	.text	@ tell the assembler this is a text section. 
	.align  @ older ARM cpu's like their code to be non word alligned
		@ this tells the linker the next command needs to be word
		@ aliged.
	@ 
	@ Define _start label. After assembling and linking, sections of 
	@ code are gattered together and there is no guaranty the code needs 
	@ to start executing at 0x00 of the program.  The _start symbol pretty 
	@ much defines the "main" method to execute and this information will
	@ be put into the elf file (usually in a INIT section) to be executed
	@ by the dynamic loader before the main is called.
	@ debuggers like gdb will look for this symbol to startup.
	@
	@ labels in general will not end up in the assembly. They can be put
	@ in a separate section of the elf file if there are external references.
	@ for short they don't represent assembly instructions. For example
	@ if you dump the symbols of the uart.elf it might look like this:
	@ use man nm to get information about the flags.
	@ for short: 
	@ lower case -> symbol is local
	@ upper case -> symbol is global
	@ A -> The symbol is absolute 
	@ T -> The symbol points to code
	@ arm-none-eabi-nm  uart.elf 
	@ 00010038 A __bss_end__
	@ 00010038 A __bss_start
	@ 00010038 A __bss_start__
	@ 4b008038 T __data_start
	@ 00010038 A __end__
	@ 00010038 A _bss_end__
	@ 00010038 A _edata
	@ 00010038 A _end
	@ 4b078000 T _stack
	@ 4b000000 T _start
	@ 4b00801c t end
	@ 4b008020 t hello
	@ 4b008000 t start
	@ 4b008008 t write

	@
start:
_start:
	@
	@ When programming c you can declare variable and functions static.
	@ this has the effect to only define the symbols inside the compilation
	@ unit. The default however is to export the symbols.
	@
	@ In assembly it is the other way around. Unless you define the symbol
	@ as "global" it won't be visible to other compilation units.
	@
	.global _start
	adr r0,hello	@ Store the address of "hello" in r0, using the adr pseudo 
		 	@ assembly instruction. this is a pseudo instruction because 
			@ of limitations of the ARM assembly instruction. These 
			@ instructions are ony 32 bits and contain both the instructions 
			@ and arguments to use. The implication of this is that it is
			@ not possible to assign any value to a register in a single
			@ instruction. The assembler will chose the best way to assign
			@ the value to the register. In practice it does one of the
			@ following:
			@ * store the value in the code in a location near this instruction
			@   and use relative addressing.
			@     lrd r0, [PC 0x14] 
			@ * use two instructions to store the upper and lower 16 bits
			@     fix add instructions here.
		
	ldr r2, = UART0_BASE
write:  
	ldrb r1 , [r0] , #1  @  r1 = *r0++

	cmp r1,#0
	strne r1, [r2] @ write to the UART not even waiting for the buffer 
		       @ to be empty.
	bne write
	b end
end:
	b end
hello:
	.string "Hello,from Qemu\n"
