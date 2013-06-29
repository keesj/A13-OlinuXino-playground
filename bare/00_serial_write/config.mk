#
# Sample bare code for the A13
#
# There is no standard cross toolchain on linux for arm
# and about every project either build it's own or uses
# either the linaro toolchain or the code sourcery one.
# I also use the one delivered with Android at times.
#
# Some toolchain are so called "bare" as in that they do not
# contain support libraries for the OS. this include the startup 
# code "crt-something" and other libraries (libgcc or even a libc)
# Either of these toolchain can be "trained" to either product bare
# code or code that will run on an os
#
# /opt/codesourcery/arm/bin/arm-none-eabi-gcc
#CROSS_COMPILE=arm-none-eabi-
CROSS_COMPILE=arm-linux-androideabi-

#LOAD_ADDRESS=0x4B0000000
