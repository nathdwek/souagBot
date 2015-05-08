/* 
 * File:   uart.h
 * Author: nathdwek
 *
 * Created on 10 avril 2015, 19:53
 */

#ifndef UART_H
#define	UART_H
//#define UART_DBG

void initUart(void);
void sendCommand(int newCommand);

#ifdef UART_DBG
extern int command;
#endif

#endif	/* UART_H */

