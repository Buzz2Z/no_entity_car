/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,??????
 * All rights reserved.
 * ????????QQ???????179029047(????)  ?????244861897(????)  ?????824575535
 *
 * ??????????????????????????��?��???????????????????????
 * ?????��??��?????????????????????????????????????????
 *
 * @file       		board
 * @company	   		???????????????
 * @author     		??????(QQ790875685)
 * @version    		??doc??version??? ?��???
 * @Software 		MDK FOR C251 V5.60
 * @Target core		STC32G12K128
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-4-14
 ********************************************************************************************************************/



#ifndef __BOARD_H
#define __BOARD_H
#include "common.h"

//FOSC????:35000000, 33177600, 30000000, 27000000. 24000000, 22118400

#define FOSC					0			
											

#define EXTERNAL_CRYSTA_ENABLE 	0			
#define PRINTF_ENABLE			1			
#define ENABLE_IAP 				1			

#define DEBUG_UART 			  	UART_1
#define DEBUG_UART_BAUD 	  	115200
#define DEBUG_UART_RX_PIN  		UART1_RX_P30
#define DEBUG_UART_TX_PIN  		UART1_TX_P31
#define DEBUG_UART_TIM			TIM_2

#if (1==PRINTF_ENABLE)
	char putchar(char c);
#endif

#define SET_P54_RESRT 	  (RSTCFG |= 1<<4)

extern int32 sys_clk;

void board_init(void);
void DisableGlobalIRQ(void);
void EnableGlobalIRQ(void);

#endif
