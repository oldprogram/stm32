/* Includes ------------------------------------------------------------------*/
#include "includes.h"
#include "demo.h"
#include "NRF24L01.h"

extern unsigned char SPI_Read(BYTE reg);
extern unsigned char SPI_Read_Buf(BYTE reg, BYTE *pBuf, BYTE bytes);
extern unsigned char SPI2_NRF_SendByte(unsigned char byte);
extern void MODE_CE(unsigned char a);
extern unsigned char SPI2_NRF_SendByte(unsigned char byte);
extern unsigned char SPI_RW_Reg(unsigned char data1,unsigned char data2);
extern unsigned char SPI_Write_Buf(BYTE reg, BYTE *pBuf, BYTE bytes);
extern void RX_Mode(void);
extern void TX_Mode(void);


extern volatile  unsigned long  SoftTimer;
extern unsigned char _it0,_it1,_it2,_it3;
extern INT8U P500usReq;
#define   TimerCnt    SysTick->VAL  


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : NMIException
* Description    : This function handles NMI exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NMIException(void)
{
 
}

/*******************************************************************************
* Function Name  : HardFaultException
* Description    : This function handles Hard Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void HardFaultException(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : MemManageException
* Description    : This function handles Memory Manage exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void MemManageException(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : BusFaultException
* Description    : This function handles Bus Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void BusFaultException(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : UsageFaultException
* Description    : This function handles Usage Fault exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UsageFaultException(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/*******************************************************************************
* Function Name  : DebugMonitor
* Description    : This function handles Debug Monitor exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DebugMonitor(void)
{
}

/*******************************************************************************
* Function Name  : SVCHandler
* Description    : This function handles SVCall exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SVCHandler(void)
{
}

/*******************************************************************************
* Function Name  : PendSVC
* Description    : This function handles PendSVC exception.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void PendSVC(void)
{
}

/*******************************************************************************
* Function Name  : SysTickHandler
* Description    : This function handles SysTick Handler.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SysTickHandler(void)
{
   OS_CPU_SR  cpu_sr;	 
    OS_ENTER_CRITICAL();  //±£´æÈ«¾ÖÖÐ¶Ï±êÖ¾,¹Ø×ÜÖÐ¶Ï/* Tell uC/OS-II that we are starting an ISR*/
    OSIntNesting++;		  //ÊÇÎªÁËÖÐ¶ÏÇ¶Ì×
    OS_EXIT_CRITICAL();	  //»Ö¸´È«¾ÖÖÐ¶Ï±êÖ¾	 
    OSTimeTick();     /* Call uC/OS-II's OSTimeTick(),ÔÚos_core.cÎÄ¼þÀï¶¨Òå,Ö÷ÒªÅÐ¶ÏÑÓÊ±µÄÈÎÎñÊÇ·ñ¼ÆÊ±µ½*/	
    OSIntExit();  //ÔÚos_core.cÎÄ¼þÀï¶¨Òå,Èç¹ûÓÐ¸ü¸ßÓÅÏÈ¼¶µÄÈÎÎñ¾ÍÐ÷ÁË,ÔòÖ´ÐÐÒ»´ÎÈÎÎñÇÐ»»     
}


/*******************************************************************************
* Function Name  : WWDG_IRQHandler
* Description    : This function handles WWDG interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void WWDG_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : PVD_IRQHandler
* Description    : This function handles PVD interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void PVD_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TAMPER_IRQHandler
* Description    : This function handles Tamper interrupt request. 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TAMPER_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : RTC_IRQHandler
* Description    : This function handles RTC global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RTC_IRQHandler(void)
{
    
}

/*******************************************************************************
* Function Name  : FLASH_IRQHandler
* Description    : This function handles Flash interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void FLASH_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : RCC_IRQHandler
* Description    : This function handles RCC interrupt request. 
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RCC_IRQHandler(void)
{
}


/*******************************************************************************
* Function Name  : EXTI1_IRQHandler
* Description    : This function handles External interrupt Line 1 request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : EXTI2_IRQHandler
* Description    : This function handles External interrupt Line 2 request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/

////////////////¼üÅÌÐÐÏß2ÖÐ¶Ï
void EXTI2_IRQHandler(void)
{
  
}
/*******************************************************************************
* Function Name  : EXTI3_IRQHandler
* Description    : This function handles External interrupt Line 3 request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI3_IRQHandler(void)
{  
}

/*******************************************************************************
* Function Name  : EXTI4_IRQHandler
* Description    : This function handles External interrupt Line 4 request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI4_IRQHandler(void)
{   
}

/*******************************************************************************
* Function Name  : DMA1_Channel1_IRQHandler
* Description    : This function handles DMA1 Channel 1 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMAChannel1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA1_Channel2_IRQHandler
* Description    : This function handles DMA1 Channel 2 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMAChannel2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA1_Channel3_IRQHandler
* Description    : This function handles DMA1 Channel 3 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMAChannel3_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA1_Channel4_IRQHandler
* Description    : This function handles DMA1 Channel 4 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMAChannel4_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA1_Channel5_IRQHandler
* Description    : This function handles DMA1 Channel 5 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMAChannel5_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA1_Channel6_IRQHandler
* Description    : This function handles DMA1 Channel 6 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMAChannel6_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA1_Channel7_IRQHandler
* Description    : This function handles DMA1 Channel 7 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMAChannel7_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : ADC1_2_IRQHandler
* Description    : This function handles ADC1 and ADC2 global interrupts requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ADC_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : USB_HP_CAN_TX_IRQHandler
* Description    : This function handles USB High Priority or CAN TX interrupts 
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USB_HP_CAN_TX_IRQHandler(void)
{
 
}

/*******************************************************************************
* Function Name  : USB_LP_CAN_RX0_IRQHandler
* Description    : This function handles USB Low Priority or CAN RX0 interrupts 
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USB_LP_CAN_RX0_IRQHandler(void)
{
 
}

/*******************************************************************************
* Function Name  : CAN_RX1_IRQHandler
* Description    : This function handles CAN RX1 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CAN_RX1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : CAN_SCE_IRQHandler
* Description    : This function handles CAN SCE interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void CAN_SCE_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : EXTI9_5_IRQHandler
* Description    : This function handles External lines 9 to 5 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI9_5_IRQHandler(void)
{
}

/////////////////////////////
void EXTI0_IRQHandler(void)
{ 
  unsigned char status,i;
  OS_CPU_SR  cpu_sr;
  OS_ENTER_CRITICAL();  //±£´æÈ«¾ÖÖÐ¶Ï±êÖ¾,¹Ø×ÜÖÐ¶Ï Tell uC/OS-II that we are starting an ISR
  OSIntNesting++;
  OS_EXIT_CRITICAL();	  //»Ö¸´È«¾ÖÖÐ¶Ï±êÖ¾	 	    
  
  if(EXTI_GetITStatus(EXTI_Line0) != RESET)		    //ÅÐ¶ÏÊÇ·ñ²úÉúÁËEXTI0ÖÐ¶Ï
  {
  	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)==0){ //ÅÐ¶ÏÊÇ·ñÊÇPA0Ïß±äµÍ			
		status=SPI_Read(READ_REG1+STATUS);			// ¶ÁÈ¡×´Ì¬¼Ä´æÆäÀ´ÅÐ¶ÏÊý¾Ý½ÓÊÕ×´¿ö	
		if(status & 0x40)				    		// ÅÐ¶ÏÊÇ·ñ½ÓÊÕµ½Êý¾Ý				   
		{											 			
		 	SPI_Read_Buf(RD_RX_PLOAD,rx_buf,TX_PLOAD_WIDTH);  //´Ó½ÓÊÕ»º³åÇøÀï¶Á³öÊý¾Ý 
			for(i=0; i<32; i++){							  //ÏòUSB ¶Ëµã1µÄ»º³åÇøÀï·ÅÖÃÊý¾Ý
				TxBufferUSART[i] = rx_buf[i];     
			}
			rf_rec_flag=1;		  
			if((status&0x0e)<=0x0a){						   
			   nrf_Pipe_r=(status&0x0e)>>1;					  //¶Á³öÊÇÔÚÄÄ¸öÍ¨µÀ½ÓÊÕµÄ
			}
			else nrf_Pipe_r=0;					 
			Rx_Succ=1;			//¶ÁÈ¡Êý¾ÝÍê³É±êÖ¾
			/* ¸ù¾Ý¶Á³öµÄ½ÓÊÕÍ¨µÀºÅ£¬½«ÏàÓ¦ÐÅÏ¢Ð´Èë×´Ì¬ÎÄ±¾»º³åÇø */
			if(nrf_Pipe_r==0) memcpy(status_buf, "Pipe 0 Recive OK!   ", 20);		   
			else if(nrf_Pipe_r==1) memcpy(status_buf, "Pipe 1 Recive OK!   ", 20);
			else if(nrf_Pipe_r==2) memcpy(status_buf, "Pipe 2 Recive OK!   ", 20);
			else if(nrf_Pipe_r==3) memcpy(status_buf, "Pipe 3 Recive OK!   ", 20);
			else if(nrf_Pipe_r==4) memcpy(status_buf, "Pipe 4 Recive OK!   ", 20);
			else if(nrf_Pipe_r==5) memcpy(status_buf, "Pipe 5 Recive OK!   ", 20);
		}
		else if((status &0x10)>0){					 //·¢Éä´ïµ½×î´ó¸´·¢´ÎÊý				
			SPI_RW_Reg(0xe1,0);					 	 //Çå³ý·¢ËÍ»º³åÇø  				
			RX_Mode();								 //½øÈë½ÓÊÕÄ£Ê½								 
			Rx_Succ=1;	   																			 
			/* ¸ù¾Ý·¢ËÍÍ¨µÀ£¬½«ÏàÓ¦ÐÅÏ¢Ð´Èë×´Ì¬ÎÄ±¾»º³åÇø */
			if(nrf_Pipe==0) memcpy(status_buf, "Pipe 0 NO ACK!      ", 20);
			else if(nrf_Pipe==1) memcpy(status_buf, "Pipe 1 NO ACK!      ", 20);
			else if(nrf_Pipe==2) memcpy(status_buf, "Pipe 2 NO ACK!      ", 20);
			else if(nrf_Pipe==3) memcpy(status_buf, "Pipe 3 NO ACK!      ", 20);  
			else if(nrf_Pipe==4) memcpy(status_buf, "Pipe 4 NO ACK!      ", 20);
			else if(nrf_Pipe==5) memcpy(status_buf, "Pipe 5 NO ACK!      ", 20);			
		}
		else if((status &0x20)>0){					 //·¢ÉäºóÊÕµ½Ó¦´ð 			
			SPI_RW_Reg(0xe1,0);					     //Çå³ý·¢ËÍ»º³åÇø  			
			RX_Mode();								 //½øÈë½ÓÊÕÄ£Ê½
			Rx_Succ=1;
			/* ¸ù¾Ý·¢ËÍÍ¨µÀ£¬½«ÏàÓ¦ÐÅÏ¢Ð´Èë×´Ì¬ÎÄ±¾»º³åÇø */
			if(nrf_Pipe==0) memcpy(status_buf, "Pipe 0 Send OK!     ", 20);
			else if(nrf_Pipe==1) memcpy(status_buf, "Pipe 1 Send OK!     ", 20);
			else if(nrf_Pipe==2) memcpy(status_buf, "Pipe 2 Send OK!     ", 20);
			else if(nrf_Pipe==3) memcpy(status_buf, "Pipe 3 Send OK!     ", 20);
			else if(nrf_Pipe==4) memcpy(status_buf, "Pipe 4 Send OK!     ", 20);
			else if(nrf_Pipe==5) memcpy(status_buf, "Pipe 5 Send OK!     ", 20);   			
		}
		
		SPI_RW_Reg(WRITE_REG1+STATUS, status);	     //Çå³ý07¼Ä´æÆ÷±êÖ¾	  		
	  }		
	  EXTI_ClearITPendingBit(EXTI_Line0);			 //Çå³ýEXTI0ÉÏµÄÖÐ¶Ï±êÖ¾              
  }   
  OSIntExit();           //ÔÚos_core.cÎÄ¼þÀï¶¨Òå,Èç¹ûÓÐ¸ü¸ßÓÅÏÈ¼¶µÄÈÎÎñ¾ÍÐ÷ÁË,ÔòÖ´ÐÐÒ»´ÎÈÎÎñÇÐ»»     
}

/*******************************************************************************
* Function Name  : TIM1_BRK_IRQHandler
* Description    : This function handles TIM1 Break interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM1_BRK_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM1_UP_IRQHandler
* Description    : This function handles TIM1 overflow and update interrupt 
*                  request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM1_UP_IRQHandler(void)
{
  /* Clear the TIM1 Update pending bit */
 

}

/*******************************************************************************
* Function Name  : TIM1_TRG_COM_IRQHandler
* Description    : This function handles TIM1 Trigger and commutation interrupts 
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM1_TRG_COM_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM1_CC_IRQHandler
* Description    : This function handles TIM1 capture compare interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM1_CC_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM2_IRQHandler
* Description    : This function handles TIM2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM3_IRQHandler
* Description    : This function handles TIM3 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM3_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM4_IRQHandler
* Description    : This function handles TIM4 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM4_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : I2C1_EV_IRQHandler
* Description    : This function handles I2C1 Event interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C1_EV_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : I2C1_ER_IRQHandler
* Description    : This function handles I2C1 Error interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C1_ER_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : I2C2_EV_IRQHandler
* Description    : This function handles I2C2 Event interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C2_EV_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : I2C2_ER_IRQHandler
* Description    : This function handles I2C2 Error interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void I2C2_ER_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : SPI1_IRQHandler
* Description    : This function handles SPI1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : SPI2_IRQHandler
* Description    : This function handles SPI2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI2_IRQHandler(void)
{
 
}

/*******************************************************************************
* Function Name  : USART1_IRQHandler
* Description    : This function handles USART1 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART1_IRQHandler(void)
{ 
	unsigned int i;
	OS_CPU_SR  cpu_sr;
	OS_ENTER_CRITICAL();  //±£´æÈ«¾ÖÖÐ¶Ï±êÖ¾,¹Ø×ÜÖÐ¶Ï Tell uC/OS-II that we are starting an ISR
	OSIntNesting++;
	OS_EXIT_CRITICAL();	  //»Ö¸´È«¾ÖÖÐ¶ÏêÖ¾	 	   

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)	   //ÅÐ¶Ï¶Á¼Ä´æÆ÷ÊÇ·ñ·Ç¿Õ
	{	
		RxBufferUSART[RxCounter1++] = USART_ReceiveData(USART1);   //½«¶Á¼Ä´æÆ÷µÄÊý¾Ý»º´æµ½½ÓÊÕ»º³åÇøÀï
		if(RxBufferUSART[RxCounter1-2]==0x0d&&RxBufferUSART[RxCounter1-1]==0x0a)     //ÅÐ¶Ï½áÊø±êÖ¾ÊÇ·ñÊÇ0x0d 0x0a
		{
			for(i=0; i< RxCounter1; i++) TxBufferRF[i] = RxBufferUSART[i]; 	     //½«½ÓÊÕ»º³åÆ÷µÄÊý¾Ý×ªµ½·¢ËÍ»º³åÇø£¬×¼±¸×ª·¢
			usart_rec_flag=1;															 //½ÓÊÕ³É¹¦±êÖ¾
			TxBufferRF[RxCounter1]=0;		                                     //·¢ËÍ»º³åÇø½áÊø·û    
			TxCounter1=RxCounter1;
			RxCounter1=0;
		}
	}
	
	if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)                   //Õâ¶ÎÊÇÎªÁË±ÜÃâSTM32 USART µÚÒ»¸ö×Ö½Ú·¢²»³öÈ¥µÄBUG 
	{ 
		USART_ITConfig(USART1, USART_IT_TXE, DISABLE);					     //½ûÖ¹·¢»º³åÆ÷¿ÕÖÐ¶Ï£¬ 
	}
		
	OSIntExit();           //ÔÚos_core.cÎÄ¼þÀï¶¨Òå,Èç¹ûÓÐ¸ü¸ßÓÅÏÈ¼¶µÄÈÎÎñ¾ÍÐ÷ÁË,ÔòÖ´ÐÐÒ»´ÎÈÎÎñÇÐ»»    
}

/*******************************************************************************
* Function Name  : USART2_IRQHandler
* Description    : This function handles USART2 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : USART3_IRQHandler
* Description    : This function handles USART3 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART3_IRQHandler(void)
{
 
}

/*******************************************************************************
* Function Name  : EXTI15_10_IRQHandler
* Description    : This function handles External lines 15 to 10 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI15_10_IRQHandler(void)
{
 
}

/*******************************************************************************
* Function Name  : RTCAlarm_IRQHandler
* Description    : This function handles RTC Alarm interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RTCAlarm_IRQHandler(void)
{
 
}

/*******************************************************************************
* Function Name  : USBWakeUp_IRQHandler
* Description    : This function handles USB WakeUp interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USBWakeUp_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM8_BRK_IRQHandler
* Description    : This function handles TIM8 Break interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM8_BRK_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM8_UP_IRQHandler
* Description    : This function handles TIM8 overflow and update interrupt 
*                  request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM8_UP_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM8_TRG_COM_IRQHandler
* Description    : This function handles TIM8 Trigger and commutation interrupts 
*                  requests.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM8_TRG_COM_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM8_CC_IRQHandler
* Description    : This function handles TIM8 capture compare interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM8_CC_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : ADC3_IRQHandler
* Description    : This function handles ADC3 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ADC3_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : FSMC_IRQHandler
* Description    : This function handles FSMC global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void FSMC_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : SDIO_IRQHandler
* Description    : This function handles SDIO global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SDIO_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM5_IRQHandler
* Description    : This function handles TIM5 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM5_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : SPI3_IRQHandler
* Description    : This function handles SPI3 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void SPI3_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : UART4_IRQHandler
* Description    : This function handles UART4 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UART4_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : UART5_IRQHandler
* Description    : This function handles UART5 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void UART5_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM6_IRQHandler
* Description    : This function handles TIM6 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM6_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : TIM7_IRQHandler
* Description    : This function handles TIM7 global interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM7_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA2_Channel1_IRQHandler
* Description    : This function handles DMA2 Channel 1 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA2_Channel1_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA2_Channel2_IRQHandler
* Description    : This function handles DMA2 Channel 2 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA2_Channel2_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA2_Channel3_IRQHandler
* Description    : This function handles DMA2 Channel 3 interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA2_Channel3_IRQHandler(void)
{
}

/*******************************************************************************
* Function Name  : DMA2_Channel4_5_IRQHandler
* Description    : This function handles DMA2 Channel 4 and DMA2 Channel 5
*                  interrupt request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void DMA2_Channel4_5_IRQHandler(void)
{
}

/******************* (C) COPYRIGHT 2011 ·Ü¶·STM32 *****END OF FILE****/
