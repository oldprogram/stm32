#ifdef NRF_GLOBALS 
#define NRF_EXT
#else
#define NRF_EXT extern 
#endif

#define Led_ON()   GPIO_SetBits(GPIOB, GPIO_Pin_5);  	      //LED1亮
#define Led_OFF()  GPIO_ResetBits(GPIOB, GPIO_Pin_5); 	      //LED2灭

#define Select_NRF()     GPIO_ResetBits(GPIOB, GPIO_Pin_0)	  //NRF24L01 选择
#define NotSelect_NRF()  GPIO_SetBits(GPIOB, GPIO_Pin_0)	  //NRF24L01 禁止
#define uchar unsigned char
#define TX_ADR_WIDTH    5                                     //TX(RX) 地址宽度
#define TX_PLOAD_WIDTH  32                      			  //发送帧长度 
NRF_EXT unsigned char it_msg,led_flash,rx_count,Rx_Succ;

NRF_EXT unsigned char TX_ADDRESS0[TX_ADR_WIDTH]; // Define a static TX address
NRF_EXT unsigned char TX_ADDRESS1[TX_ADR_WIDTH]; // Define a static TX address
NRF_EXT unsigned char TX_ADDRESS2[TX_ADR_WIDTH]; // Define a static TX address
NRF_EXT unsigned char TX_ADDRESS3[TX_ADR_WIDTH]; // Define a static TX address
NRF_EXT unsigned char TX_ADDRESS4[TX_ADR_WIDTH]; // Define a static TX address
NRF_EXT unsigned char TX_ADDRESS5[TX_ADR_WIDTH]; // Define a static TX address

NRF_EXT unsigned char rx_buf[32];				 //接收缓冲区
NRF_EXT unsigned char tx_buf[32];				 //发送缓冲区
NRF_EXT unsigned char status_buf[20];			 //状态字缓冲区
NRF_EXT unsigned char flag,nrf_baud,nrf_Pipe,nrf_Pipe_r;

//无线的数据
extern uint8_t TxBufferRF[40];  
extern uint8_t RxBufferRF[40];
extern uint8_t rf_rec_flag,rf_tx_flag;
//串口的数据
extern uint8_t TxBufferUSART[40]; 
extern uint8_t RxBufferUSART[40];
extern uint8_t usart_rec_flag,usart_tx_flag;
extern __IO uint8_t TxCounter1;
extern __IO uint8_t RxCounter1; 



