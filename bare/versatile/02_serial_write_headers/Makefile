#
# Sample bare application for the A13
#

#
# Configuration for thinkg like cross toolchain to use
# and load address of the binary.
include config.mk


#
# the first target in a makefile is the default target
# we make this target depend on what we want. 
# first "needed" to check we go the tools we want for the job
#
#
default:needed uart.bin uart.elf

#
# 
OBJECTS=uart.s.o
TOOLS=picocom sx expect ${CROSS_COMPILE}gcc

needed:
	@for i in ${TOOLS} ; \
	 do  \
		if ! which $$i 2>&1 1>/dev/null ; \
		then  echo missing tool "$$i" ;\
		 exit 1 ; \
		fi ; \
	 done  

#
# Define a rule to assemble assembly files. We are using gcc here and not as
# as we also want to use cpp (the c preprosessor)
#
%.s.o:%.S
	${CROSS_COMPILE}gcc -fPIC -nostdlib -o  $@  $<
#	${CROSS_COMPILE}gcc -fPIC -shared -nostdlib -o  $@  $<
	
#
# Link using a linker script 
#
%.elf:${OBJECTS}
	${CROSS_COMPILE}ld -T versatilepb.lds -o $@ $<

#
# We are loading the binary directly into memory so we need a flat model.
#
%.bin:%.elf
	${CROSS_COMPILE}objcopy -O binary $< $@

run:uart.bin
	QEMU_AUDIO_DRV="none" qemu-system-arm -M versatilepb -m 128M -nographic  -kernel uart.bin

clean:
	rm -rf *.bin *.elf *.o *.out
