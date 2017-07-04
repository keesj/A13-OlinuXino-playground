#include "uart_registers.h"
	.text
	.align
	.section "vectors"
reset: b start
undef: b undef
swi:   b swi_handler
pabt:  b pabt
dabt:  b dabt
	nop
irq:   b irq
fiq:   b fiq

	.text	@ tell the assembler this is a text section. 
	.align  @ older ARM cpu's don't like their code to be non word 
		@ alligned this tells the linker the next command needs 
		@ to be word aliged.
start:
_start: @main loop
	@ setup vector base address
	.global _start
	ldr r0, =vtable_start
	ldr r1, =#0

	ldr r2 , [r0] , #4  @  r2 = *r0++
	str r2,  [r1] , #4  @  
	ldr r2 , [r0] , #4  @  r2 = *r0++
	str r2,  [r1] , #4  @  
	ldr r2 , [r0] , #4  @  r2 = *r0++
	str r2,  [r1] , #4  @  
	ldr r2 , [r0] , #4  @  r2 = *r0++
	str r2,  [r1] , #4  @  
	ldr r2 , [r0] , #4  @  r2 = *r0++
	str r2,  [r1] , #4  @  
	ldr r2 , [r0] , #4  @  r2 = *r0++
	str r2,  [r1] , #4  @  
	ldr r2 , [r0] , #4  @  r2 = *r0++
	str r2,  [r1] , #4  @  
	ldr r2 , [r0] , #4  @  r2 = *r0++
	str r2,  [r1] , #4  @  
	

	ldr sp, =stack_top @ from the linker script
	//adr r0,hello	
	//bl write_string    @ 
main:
//	bl read_uart
//	cmp r0,#1    @ the return value of read_uart and 0
//	bne main   @ if null call write uart 
//	bl write_uart   @ if null call write uart 
	swi 0           @ test calling supervisor
	bl main     @ back to the start

swi_handler:
	push {r4-r10,lr}   
	adr r0,swi_hello	
	bl write_string    @ 
	pop     {r4-r10, lr}
	bx lr

write_string: @r0 == string
	push {r4-r10,lr}   
write_string_loop:
	ldrb r1 , [r0] , #1  @  r1 = *r0++
	push {r1}
	bl write_uart
	pop {r1}
	cmp r1,#0
	bne write_string_loop
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
swi_hello:
	.string "Hello from SWI\r\n"
