/*
 * we now modified the load address to be near 0
 */

stack_size = 512;

SECTIONS {
	. = 0x0;
	.text : { * (vectors) 
	; } 
	.text : { * (.text) 
	; } 

	.data : { 
		* (.data) ; 

		* (.bss) ; 
		* (.rodata) ; 

		stack_bottom = .; /* define variable stack bottom and such to use in the assembly code */
		. += stack_size;
		stack_top = .;
		
	}
}
