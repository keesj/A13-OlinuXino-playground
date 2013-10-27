	.text	@ tell the assembler this is a text section. 
	ldr r0, [pc , #0x24 -8]
	ldr r1, =0x28
start_of_loop:  
	ldrb r2 , [r1]  @load a byte
	cmp r2,#0
	beq end
	str r2, [r0]
	add r1,r1,#1 
	b start_of_loop
end:
	b end
	.align
	.word 0x01C28400
	.string "Hello,from Olimex\n"
