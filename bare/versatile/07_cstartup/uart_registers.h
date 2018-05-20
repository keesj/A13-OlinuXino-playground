#ifndef __UART_H__
#define __UART_H__
/*
 * http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0225d/BBAJIHEC.html
 */

/* 
 * The following addresses are "in memory" addresses for the hardware. 
 */
#define UART0_BASE  0x101f1000


/* #Register Name 	Offset 	Description  */
#define UART_UARTDR 	0x00 	/* UART Data register */

#define UART_UARTFR 	0x18 	/* UART Flag register */
#define UART_UARTFR_BUSY (0x1  << 3)   /* UART busy.  */
#define UART_UARTFR_RXFE (0x01 << 4) /* Receive FIFO empty.  */
#define UART_UARTFR_TXFF (0x01 << 5) /* Transmit FIFO Full */



#endif
