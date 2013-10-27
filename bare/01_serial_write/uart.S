	.text	@ tell the assembler this is a text section. 
	adr r0,hello
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
	.align
hello:
	.string "Hello,from Olimex 02\n"
	.equ    UART0_BASE,0x01C28400 @define a constant that point to the UART register
