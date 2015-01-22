#include "includes.h"

//--------------------------------------------------------------------------------------
void USART_SendChar(USART_TypeDef* USARTx,uint8_t data)
{
	USART_SendData(USARTx,data);
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)==RESET);
}
//--------------------------------------------------------------------------------------
void USART_Config(USART_TypeDef* USARTx)
{
	USART_InitTypeDef USART_InitStructure;
	
	USART_InitStructure.USART_BaudRate = 9600;						//速率19200bps
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//数据位8位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;			//停止位1位
	USART_InitStructure.USART_Parity = USART_Parity_No;				//无校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   //无硬件流控
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;					//收发模式
	
	/* Configure USART1 */
	USART_Init(USARTx, &USART_InitStructure);							//配置串口参数函数
	
	/* Enable USART1 Receive and Transmit interrupts */
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);                    //使能接收中断
	USART_ITConfig(USART1, USART_IT_TXE, ENABLE);						//使能发送缓冲空中断   
	
	/* Enable the USART1 */
	USART_Cmd(USART1, ENABLE);	
}