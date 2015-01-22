#ifdef NRF_GLOBALS 
#define NRF_EXT
#else
#define NRF_EXT extern 
#endif

#define Led_ON()   GPIO_SetBits(GPIOB, GPIO_Pin_5);  	   //LED1 
#define Led_OFF()  GPIO_ResetBits(GPIOB, GPIO_Pin_5); 	   //LED2

#define Select_NRF()     GPIO_ResetBits(GPIOB, GPIO_Pin_12)
#define NotSelect_NRF()    GPIO_SetBits(GPIOB, GPIO_Pin_12)
#define uchar unsigned char
#define TX_ADR_WIDTH    5   // 5 bytes TX(RX) address width
#define TX_PLOAD_WIDTH  32  // 1bytes TX payload
NRF_EXT unsigned char it_msg,led_flash;

NRF_EXT unsigned char TX_ADDRESS0[TX_ADR_WIDTH]; // Define a static TX address
NRF_EXT unsigned char TX_ADDRESS1[TX_ADR_WIDTH]; // Define a static TX address
NRF_EXT unsigned char TX_ADDRESS2[TX_ADR_WIDTH]; // Define a static TX address
NRF_EXT unsigned char TX_ADDRESS3[TX_ADR_WIDTH]; // Define a static TX address
NRF_EXT unsigned char TX_ADDRESS4[TX_ADR_WIDTH]; // Define a static TX address
NRF_EXT unsigned char TX_ADDRESS5[TX_ADR_WIDTH]; // Define a static TX address

NRF_EXT unsigned char rx_buf[TX_PLOAD_WIDTH];
NRF_EXT unsigned char tx_buf[TX_PLOAD_WIDTH];
NRF_EXT unsigned char status_buf[TX_PLOAD_WIDTH];
NRF_EXT unsigned char flag,nrf_baud,nrf_Pipe,nrf_Pipe_r;
