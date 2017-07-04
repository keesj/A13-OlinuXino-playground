#include "uart_registers.h"
	.text	@ tell the assembler this is a text section. 
	.align  @ older ARM cpu's like their code to be non word alligned
		@ this tells the linker the next command needs to be word
		@ aliged.
	.section "crt0"
start:
_start: @main loop
	@ setup vector base address
	.global _start
	ldr sp, =stack_top @ from the linker script
	ldr fp, =fp_top @ from the linker script

	bl init_bss
	bl main
	cmp r0,#0
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
end:
	b end
