/*
 * we now modified the load address to be near 0
 */

stack_size = 512;

MEMORY {                                       /* memory map of AT91SAM7S64 */
    INIT (rwx)  : ORIGIN = 0x0000, LENGTH = 4k
    RAM (rwx) : ORIGIN = 0x10000, LENGTH = 64k
}
SECTIONS {
	. = 0x10000;


	.text : { 
		code_start = . ;
		* (.text) 
	; }  > RAM

		vtable_start = .;
	.text :  { 
 		* (vectors) 
	; }  AT> INIT

	.data : { * (.data) ; 
		stack_bottom = .; /* define variable stack bottom and such to use in the assembly code */
		. += stack_size;
		stack_top = .;
	}  > RAM

}
