/*
 * we now modified the load address to be near 0
 */

stack_size = 512;
fp_size = 512;

SECTIONS {
        . = 0x10000;
	.text : { * (crt0) 
	; } 
	.text : { * (.text) 
	; } 

	/* put all the content in the data section */
	.data : { 
		* (.data) ; 

		* (.rodata) ; 

		stack_bottom = .; /* define variable stack bottom and such to use in the assembly code */
		. += stack_size;
		stack_top = .;

		fp_bottom = .; /* room for the frame pointers */
		. += fp_size;
		fp_top = .;
		
	}
	bss_start = .;
	.bss : { 
		* (.bss) ; 
	}
	bss_end = .;
}
