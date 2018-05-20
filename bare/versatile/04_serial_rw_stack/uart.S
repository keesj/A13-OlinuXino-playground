#include "uart_registers.h"

	.text	@ tell the assembler this is a text section. 
	.align  @ older ARM cpu's like their code to be non word alligned
		@ this tells the linker the next command needs to be word
		@ aliged.
start:
_start: @main loop
	.global _start
	ldr sp, =stack_end @we created a 20 word sized stack bellow
	bl header    @ 
main:
	bl read_uart
	cmp r0,#1    @ the return value of read_uart and 0
	bleq write_uart   @ if null call write uart 
	bl main     @ back to the start

header:
	push {r4-r10,lr}   
	adr r0,hello	
write_header_loop:
	ldrb r1 , [r0] , #1  @  r1 = *r0++
	push {r1}
	bl write_uart
	pop {r1}
	cmp r1,#0
	bne write_header_loop
	pop     {r4-r10, lr}
	bx lr


write_uart:
	push {r4-r10,lr}   
	ldr r2, = UART0_BASE
wait_for_empty:
	ldr r3,[r2 ,#UART_UARTFR]  @UART Flag resiter
	tst r3,#UART_UARTFR_TXFF
	bne wait_for_empty
	str r1, [r2] @ write to the UART the buffer is empty
	pop     {r4-r10, lr}
	bx lr
	
read_uart:
	push {r4-r10,lr}   
	mov r0,#0 @ set return value 
	ldr r2, = UART0_BASE     @UART base address
	ldr r3,[r2 , #UART_UARTFR]  @UART Line Status register
	tst r3,#UART_UARTFR_RXFE  @check if there is data present
	bne read_uart_end
	ldr r1, [r2]  @load the data
	mov r0,#1 @ set return value 
read_uart_end:
	pop     {r4-r10, lr}
	bx lr
end:
	b end
hello:
	.string "Hello,from Qemu. typed text will be echoed back\n\r"
stack:
	.4byte 0x0
	.4byte 0x0
	.4byte 0x0
	.4byte 0x0
	.4byte 0x0
	.4byte 0x0
	.4byte 0x0
	.4byte 0x0
	.4byte 0x0
	.4byte 0x0
	.4byte 0x0
	.4byte 0x0
	.4byte 0x0
	.4byte 0x0
	.4byte 0x0
	.4byte 0x0
	.4byte 0x0
	.4byte 0x0
	.4byte 0x0
	.4byte 0x0
	.4byte 0x0
	.4byte 0x0
	.4byte 0x0
	.4byte 0x0
	.4byte 0x0
	.4byte 0x0
	.4byte 0x0
	.4byte 0x0
	.4byte 0x0
	.4byte 0x0
	.4byte 0x0
	.4byte 0x0
	.4byte 0x0
	.4byte 0x0
	.4byte 0x0
	.4byte 0x0
	.4byte 0x0
	.4byte 0x0
	.4byte 0x0
	.4byte 0x0
stack_end:
