#if !defined( _BSP_H )
#define _BSP_H

void RCC_Configuration(void);

void GPIO_Configuration(void);

void NVIC_Configuration(void);



void  OS_CPU_SysTickInit(void);

void BSP_Init(void);


#ifdef  DEBUG
void assert_failed(u8* file, u32 line)
#endif



#endif
