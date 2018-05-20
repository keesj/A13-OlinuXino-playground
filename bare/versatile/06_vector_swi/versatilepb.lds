/*
 * we now modified the load address to be near 0
 */

stack_size = 512;

SECTIONS {

	vtable_start = .;
	
	. = 0x10000;
	.text : { 
		* (.text) 
	; } 

	.text : AT(0x0000)  { 
 		* (vectors) 
	; } 

	.data : { * (.data) ; 
		stack_bottom = .; /* define variable stack bottom and such to use in the assembly code */
		. += stack_size;
		stack_top = .;
	}  



}
