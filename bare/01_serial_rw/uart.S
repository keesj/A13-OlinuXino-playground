#include "uart_registers.h"

	.text	@ tell the assembler this is a text section. 
	.align  @ older ARM cpu's like their code to be non word alligned
		@ this tells the linker the next command needs to be word
		@ aliged.
start:
_start: @main loop
	.global _start
	bl header    @ 
main:

	bl read_uart @ branch link uart e,g goto read_uart and set the 
		     @ program counter in the link register (r14)
	cmp r0,#1    @ the return value of read_uart and 0
	bleq write_uart   @ if null call write uart 
	bl main     @ back to the start

header:
	adr r0,hello	
	ldr r2, = UART0_BASE
write_header_loop:
	ldrb r1 , [r0] , #1  @  r1 = *r0++
	cmp r1,#0
	strne r1, [r2] @ write to the UART not even waiting for the buffer 
		       @ to be empty.
	bne write_header_loop
	mov pc,lr @ jump back


write_uart:
	ldr r2, = UART0_BASE
	str r1, [r2] @ write to the UART not even waiting for the buffer 
	mov pc,lr    @ jump back
	
read_uart:
	mov r0,#0 @ set return value 
	ldr r2, = UART0_BASE     @UART base address
	ldr r3,[r2 , #UART_LSR]  @UART Line Status register
	and r3,r3,#0x1  @check if there is data present
	cmp r3,#0x1
	bne read_uart_end
	ldr r1, [r2]  @load the data
	mov r0,#1 @ set return value 
read_uart_end:
	mov pc,lr @ jump back
end:
	b end
hello:
	.string "Hello,from Olimex\n\r"
