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
	.align  @ older ARM cpu's like their code to be non word alligned
		@ this tells the linker the next command needs to be word
		@ aliged.
start:
_start: @main loop
	@ setup vector base address
	.global _start
	mrc p15, 0, r0, c1, c0, 0
	bic r0, r0, #0x2000 @ set SCTRL.V to 0
	mcr p15, 0, r0, c1, c0, 0
	mov r0 , #0
	mcr p15, 0, r0, c12, c0, 0 @ Write VBAR
	ldr sp, =stack_top @ from the linker script
	ldr fp, =fp_top @ from the linker script

	bl init_bss
	adr r0,hello	
	bl write_string    @ 
	bl main
	cmp r0,#0
	bleq write_string    @ 
	b end

init_bss:
	push {r4-r10,lr}   
	ldr r1, =bss_start
	ldr r2, =bss_end
	mov r3, #0
init_bss_loop:
	strb  r3, [r1], #1
	cmp r1,r2
	bne init_bss_loop
	
	pop  {r4-r10,lr}
	bx lr
	
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
	ldr r3,[r2 , #UART_LSR]  @UART Line Status register
	and r3,r3,#UART_LSR_THRE  @check if there is data present
	cmp r3,#UART_LSR_THRE
	bne wait_for_empty
	str r1, [r2] @ write to the UART the buffer is empty
	pop     {r4-r10, lr}
	bx lr
	
read_uart:
	push {r4-r10,lr}   
	mov r0,#0 @ set return value 
	ldr r2, = UART0_BASE     @UART base address
	ldr r3,[r2 , #UART_LSR]  @UART Line Status register
	and r3,r3,#UART_LSR_DR  @check if there is data present
	cmp r3,#UART_LSR_DR
	bne read_uart_end
	ldr r1, [r2]  @load the data
	mov r0,#1 @ set return value 
read_uart_end:
	pop     {r4-r10, lr}
	bx lr
end:
	b end
hello:
	.string "Hello,from Olimex. typed text will be echoed back.\n\r\r\n"
swi_hello:
	.string "Hello from SWI\r\n"
