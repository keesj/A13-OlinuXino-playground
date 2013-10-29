/*
 * This code it indented to exmplain a little more about the assembly process
 * and is supposed to be run on the host pc as opposed to the device under test
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

#include "asmgen.h"

void 
main(int argc,char **argv)
{
	/* Assembly or machine language is the language processors
         * understand. In the end it is just data that gets read 
	 * and interpreted by the processor.
 	 *
         * The default ARM instruction set is relatively simple compared to 
	 * the intel instruction set. We are going to look at the normal
	 * instruction set on arm (e.g. not thumb or 64 bits).
  	 * 
 	 * Given ARM is a load/store architecture things get even simpler
	 * we can 
         * - Load and store data from memory to processor register
	 *   but not modify the memory directly.
         * - Modify registers (e.g. perform arithmetic and logical operations.
	 * - Directly encode a value to be put into a register. e.g. put 32 in the 
         *   first register
	 * - Change the program counter(register 15) to change program flow
	 * - Conditionally execute code based on the program state register
         *
	 * The ARM Reference Manual chapter "A1 Introduction to the ARM architecture"
	 * describes this into way more details and also goes into optimized versions
	 * of the above but the above.  Any ARM program will consist of the above command 
         * this is often combined with same memory data store (e.g. to put variable in)
 	 *
	 * The focus here in on understating how things work and not so much
	 * about writing a full assembler and we are going to write a sample
	 * program that will output data on the serial. To understand the next
	 * step we need to also understand how devices are accessed on ARM. On 
	 * ARM devices are accessed the same way memory is accessed e.g by writing to a 
	 * special memory location one can talk to the hardware. These addresses
	 * Always vary from ARM powered device to ARM powered device and are described
	 * in the vendor's manual in the memory map section. As said the focus is
	 * on writing to the serial. We are using the OLinuxXino-MICRO board containing
 	 * a AllWinnner A13 System on chip. The A13 has multiple serials in it's soc
	 * and thus memory map. We are in luck that these serial adhere to the de facto
	 * standard or UART's. For short if we write a 'a' to memory address 0x01C28400
	 * on the device the letter 'a' will be printed on the serial. For a proper serial
	 * Now we know enough to write pseudo code to write hello world to the serial
	 *
	 * load the address of the uart 'var' into register r0
	 * load the address of the string 'var' into register r1
         * start_of_loop:
	 * 	read the content of address r1 into r2  @read a char from memory
	 * 	compare r2 with 0                       @chek if this is the end of the string
	 * 	if the compare wat equals goto end      @if so goto end
	 * 	write the content of r2 into the address in r0  @else write the char
	 * 	increase r1 by one
	 * 	goto  start_of_loop
	 * end:
	 *    goto end
	 * We also need to   uart register address and a 0 terminated hello world
	 *   Somewhere in the program. We will do that just after the program end.
	 * 
 	 * In ARM assembly using the GNU assembly syntax this would look  like this:
	 * .text	@ tell the assembler this is a text section. 
	 *     ldr r0, =0x28  @ We have storred the serial address at position 28 hex in the code
	 *     ldr r0, [r0]   @read the content at 0x28 and put it in r0
	 *     ldr r1, =0x2c  @start of the string is at location 0x2c this can directly be entered 
	 * start_of_loop:  
	 *     ldrb r2 , [r1]  @load a byte
	 *     cmp r2,#0       @do the compare
	 *     beq end         @and switch based on the flags set by the pre instruction
	 *     str r2, [r0]    @write the string
	 *     add r1,r1,#1    @increase the value of r1 by one(there are nicer ways to do this in arm
	 *     b start_of_loop @jump back
	 * end:
	 *     b end  @endless loop
	 * .align
	 * .word 0x01C28400
	 * .string "Hello,from Olimex\n"
	 *
	 *
	 * Every ARM instruction is encoded in 32 bits. This includes the operands 
	 * and conditionals. This is all described in the ARM * Architecture Reference 
	 * Manual chapter "A5 ARM Instruction Set encoding"
         * 
	 * To describe bits I will use the [] notation "[4]" meas the bit at index 4
	 * [0] means the least significant bit (e.g. the bit on the right). [31] is
	 * the most significant bit in a 32 bits word. [31:28] determines a set of
 	 * bits "inclusive"
	 * ARM instructions have the following content
	 * [31:28] Cond 
	 * [27:25] op1
	 * [24:5]  --
	 * [4] op
	 * [3:0] --
         *
	 * In our sample program we need to load a direct v.s. indirect. 
	 * 
         */

	printf("Assembler\n");

	/* Create a new empty buffer */
	u_int8_t buffer[100];
	memset(buffer,0,sizeof(buffer));
   	printf("0xe59f001c        ldr     r0, [pc, #28]   ; 24 <__bss_end__-0x8018>\n");
	printf("0x%08x\n",LDR_LITERAL(INST_COND_AL,R0,28));
   	printf("0xe3a01028        mov     r1, #40 ; 0x28\n");
	printf("0x%08x\n",MOV_LITERAL(INST_COND_AL,R1,40));
	/* Create a memory structure for the prog */
	/*prog  * p = new_prog(); */
	//var uart_base = p.add_var_u32_t("UART_BASE",0x01C28400);
	//var message = p.add_var_string("message","Hello,from Olimex\n");
	//p.add_ldr(p.reg.r0,
	exit(0);
}
