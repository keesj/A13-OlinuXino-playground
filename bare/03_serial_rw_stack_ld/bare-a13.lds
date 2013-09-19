/*
 * the A13 has the DDR memory mapped at 0x4000 0000 -> 0XBFFF FFFFF
 * (see page 31 of the User manual) and a quick glance at the u-boot memory
 * layout (arm-none-eabi-readelf -S u-boot) shows us u-boot is to be loaded
 * at 0x4A000 0000) we are going to load at 0x4B000 0000
 *
 * In it's simplets form yo can compile setting the text sections (these 
 * contain the executable code this address e.g.
 *
 * ${CROSS_COMPILE}ld  -Ttext=${LOAD_ADDRESS}
 *
 * More often you will want more control over the layout so not only
 * the text section but also of the initialized(data) , uninitialized(bss) 
 * sections in such event writing an linker script is the way to go.
 */

stack_size = 512;

SECTIONS {
	. = 0x4B000000; 
	.text : { * (.text) ; } 
	.data : { * (.data) ; 
		stack_bottom = .; /* define variable stack bottom and such to use in the assembly code */
		. += stack_size;
		stack_top = .;
	}
}
