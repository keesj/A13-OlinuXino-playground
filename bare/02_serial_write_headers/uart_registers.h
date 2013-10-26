#ifndef __UART_H__
#define __UART_H__
/*
 * Configuration taken from A13 User Manual - v1.2 (2013-01-08).pdf
 * 
 * You can use the pfd reading program called okular to read the PDF
 * and by using control-5 you can select text in "table selection mode".
 * An other tool that can be used if pdf2text to generate an ASCII version
 * of the reference manual
 */

/* 
 * The following addresses are "in memory" addresses for the hardware. 
 */
#define UART0_BASE  0x01C28400  
#define UART3_BASE  0x01C28C00 


/* #Register Name 	Offset 	Description  */
#define UART_RBR 	0x00 	/* UART Receive Buffer Register  */
#define UART_THR 	0x00 	/* UART Transmit Holding Register  */
#define UART_DLL 	0x00 	/* UART Divisor Latch Low Register  */
#define UART_DLH 	0x04 	/* UART Divisor Latch High Register  */
#define UART_IER 	0x04 	/* UART Interrupt Enable Register  */
#define UART_IIR 	0x08 	/* UART Interrupt Identity Register  */
#define UART_FCR 	0x08 	/* UART FIFO Control Register  */
#define UART_LCR 	0x0C 	/* UART Line Control Register  */
#define UART_MCR 	0x10 	/* UART Modem Control Register  */
#define UART_LSR 	0x14 	/* UART Line Status Register  */
#define UART_MSR 	0x18 	/* UART Modem Status Register  */
#define UART_SCH 	0x1C 	/* UART Scratch Register  */
#define UART_USR 	0x7C 	/* UART Status Register  */
#define UART_TFL 	0x80 	/* UART Transmit FIFO Level  */
#define UART_RFL 	0x84 	/* UART_RFL  */
#define UART_HALT 	0xA4 	/* UART Halt TX Register  */


#define UART_LSR_THRE (1 <<5)   /* THR Empty bit of the Line status register */

#endif
