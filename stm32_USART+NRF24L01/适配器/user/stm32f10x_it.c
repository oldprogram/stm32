/**
  ******************************************************************************
  * @file USART/Interrupt/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version  V3.0.0
  * @date  04/06/2009
  * @brief  Main Interrupt Service Routines.
  *         This file provides template for all exceptions handler and 
  *         peripherals interrupt service routine.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "stm32f10x_usart.h"
#include "NRF24L01.h"
#include "globals.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern uint8_t TxBufferUSART[40];  
extern uint8_t RxBufferUSART[40];
extern __IO uint8_t TxCounter1;
extern __IO uint8_t RxCounter1; 

extern uint8_t usart_rec_flag,usart_tx_flag;

extern uint8_t TxBufferRF[40];  
extern uint8_t RxBufferRF[40];
extern uint8_t rf_rec_flag,rf_tx_flag;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval : None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval : None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval : None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval : None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval : None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval : None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval : None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval : None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval : None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*            STM32F10x Peripherals Interrupt Handlers                        */
/******************************************************************************/

/**
  * @brief  This function handles USART1 global interrupt request.
  * @param  None
  * @retval : None
  */
void USART1_IRQHandler(void)      //串口1 中断服务程序
{
  unsigned int i;
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)	   //判断读寄存器是否非空
  {	
    
    RxBufferUSART[RxCounter1++] = USART_ReceiveData(USART1);   //将读寄存器的数据缓存到接收缓冲区里
	
    if(RxBufferUSART[RxCounter1-2]==0x0d&&RxBufferUSART[RxCounter1-1]==0x0a)     //判断结束标志是否是0x0d 0x0a
    {
	  for(i=0; i< RxCounter1; i++) TxBufferRF[i] = RxBufferUSART[i]; 	     //将接收缓冲器的数据转到发送缓冲区，准备转发
	  usart_rec_flag=1;															 //接收成功标志
	  TxBufferRF[RxCounter1]=0;		                                     //发送缓冲区结束符    
	  TxCounter1=RxCounter1;
	  RxCounter1=0;
    }
  }
  
  if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)                   //这段是为了避免STM32 USART 第一个字节发不出去的BUG 
  { 
     USART_ITConfig(USART1, USART_IT_TXE, DISABLE);					     //禁止发缓冲器空中断， 
  }	
}  
/*******************************************************************************
* Function Name  : EXTI0 中断函数
* Description    : NRF24L01中断服务程序
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI0_IRQHandler(void){
	u8 i=0;
 	u8 status;	
	if(EXTI_GetITStatus(EXTI_Line0) != RESET)		    //判断是否产生了EXTI0中断
  	{
		if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0){ //判断是否是PA0线变低			
			status=SPI_Read(READ_REG1+STATUS);			// 读取状态寄存其来判断数据接收状况	
			if(status & 0x40)				    		// 判断是否接收到数据				   
			{			
				//GPIO_ResetBits(GPIOB, GPIO_Pin_5);   
			 	SPI_Read_Buf(RD_RX_PLOAD,rx_buf,TX_PLOAD_WIDTH);  //从接收缓冲区里读出数据
				for(i=0; i<32; i++){							  //向USB 端点1的缓冲区里放置数据
					TxBufferUSART[i] = rx_buf[i];     
				}
				rf_rec_flag=1;
			}
			else if((status &0x10)>0){					 //发射达到最大复发次数				
				SPI_RW_Reg(0xe1,0);					 	 //清除发送缓冲区  				
				RX_Mode();								 //进入接收模式	   			
			}
			else if((status &0x20)>0){					 //发射后收到应答 
				GPIO_SetBits(GPIOB, GPIO_Pin_5);   
				SPI_RW_Reg(0xe1,0);					     //清除发送缓冲区  			
				RX_Mode();								 //进入接收模式	   			
			}
			SPI_RW_Reg(WRITE_REG1+STATUS, status);	     //清除07寄存器标志
		}		
		EXTI_ClearITPendingBit(EXTI_Line0);			 //清除EXTI0上的中断标志              
	} 
}
