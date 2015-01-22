/****************************************************************************
* Copyright (C), 2011 奋斗嵌入式工作室 www.ourstm.net
*
* 本例程在 奋斗版STM32开发板V2,2.1,V3上调试通过           
* QQ: 9191274, 旺旺：sun68, Email: sun68@163.com 
* 淘宝店铺：ourstm.taobao.com  
*
* 文件名: Fun.c
* 内容简述:
*       本例程提供了奋斗板配3寸屏模块(240X400)的驱动程序
		
*
* 文件历史:
* 版本号  日期       作者    说明
* v0.1    2011-12-03 sun68  创建该文件
*
*/


#include "fsmc_sram.h"

#define Bank1_LCD_D    ((uint32_t)0x60020000)    //disp Data ADDR
#define Bank1_LCD_C    ((uint32_t)0x60000000)	 //disp Reg ADDR



void ILI9325_Init(void);
void LCD_WR_REG(unsigned int index);
void LCD_WR_CMD(unsigned int index,unsigned int val);

void LCD_WR_Data(unsigned int val);

void LCD_test(void);
void LCD_clear(unsigned int p);

void Delay(__IO uint32_t nCount);

unsigned short LCD_RD_data(void);
extern void lcd_rst(void);
extern void Delay(__IO uint32_t nCount);


/****************************************************************************
* 名    称：LCD_WR_REG(unsigned int index)
* 功    能：FSMC写显示器寄存器地址函数
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/ 
void LCD_WR_REG(unsigned int index)
{
	*(__IO uint16_t *) (Bank1_LCD_C)= index;

}			 

/****************************************************************************
* 名    称：void LCD_WR_CMD(unsigned int index,unsigned int val)
* 功    能：FSMC写显示器寄存器数据函数
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/ 
void LCD_WR_CMD(unsigned int index,unsigned int val)
{	
	*(__IO uint16_t *) (Bank1_LCD_C)= index;	
	*(__IO uint16_t *) (Bank1_LCD_D)= val;
}


/****************************************************************************
* 名    称：unsigned short LCD_RD_data(void)
* 功    能：FSMC读显示区16位数据函数
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/ 
unsigned short LCD_RD_data(void){
	unsigned int a=0;
	a=*(__IO uint16_t *) (Bank1_LCD_D);   //空操作
	a=*(__IO uint16_t *) (Bank1_LCD_D);   //读出的实际16位像素数据	  
	return(a);	
}



/****************************************************************************
* 名    称：LCD_WR_Data(unsigned int val)
* 功    能：FSMC写16位数据函数
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/ 
void LCD_WR_Data(unsigned int val)
{   
	*(__IO uint16_t *) (Bank1_LCD_D)= val; 	
}


/****************************************************************************
* 名    称：void Delay(__IO uint32_t nCount)
* 功    能：延时函数
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/ 
void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}
//

/****************************************************************************
* 名    称：void LCD_Init(void)
* 功    能：2.4 寸TFT 初始化函数
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/ 
void ILI9325_Init(void)
{	unsigned int i;
	//lcd_rst();	 
    GPIO_ResetBits(GPIOE, GPIO_Pin_1);	  //硬件复位
    Delay(0xAFFf);					   
    GPIO_SetBits(GPIOE, GPIO_Pin_1 );		 
	Delay(0xAFFf);	

	LCD_WR_CMD(0x0000, 0x0000);
	LCD_WR_CMD(0x0001, 0x0100);
	LCD_WR_CMD(0x0002, 0x0100);

	/*	R003H 扫描方向寄存器 决定了显示方向	*/			
	LCD_WR_CMD(0x0003, 0x1030); 

	LCD_WR_CMD(0x0008, 0x0808);
	LCD_WR_CMD(0x0009, 0x0001);
	LCD_WR_CMD(0x000B, 0x0010);
	LCD_WR_CMD(0x000C, 0x0000);
	LCD_WR_CMD(0x000F, 0x0000);
	LCD_WR_CMD(0x0007, 0x0001);
	LCD_WR_CMD(0x0010, 0x0013);
	LCD_WR_CMD(0x0011, 0x0501);
	LCD_WR_CMD(0x0012, 0x0300);
	LCD_WR_CMD(0x0020, 0x021E);
	LCD_WR_CMD(0x0021, 0x0202);
	LCD_WR_CMD(0x0090, 0x8000);
	LCD_WR_CMD(0x0100, 0x17B0);
	LCD_WR_CMD(0x0101, 0x0147);
	LCD_WR_CMD(0x0102, 0x0135);
	LCD_WR_CMD(0x0103, 0x0700);
	LCD_WR_CMD(0x0107, 0x0000);
	LCD_WR_CMD(0x0110, 0x0001);
	LCD_WR_CMD(0x0210, 0x0000);
	LCD_WR_CMD(0x0211, 0x00EF);
	LCD_WR_CMD(0x0212, 0x0000);
	LCD_WR_CMD(0x0213, 0x018F);
	LCD_WR_CMD(0x0280, 0x0000);
	//LCD_WR_CMD(0x0281, 0x0004);
	//LCD_WR_CMD(0x0282, 0x0000);

	/* 这2个寄存器可以改变显示的对比度 */
	LCD_WR_CMD(0x0281, 0x000f);
	LCD_WR_CMD(0x0282, 0x0000);

	LCD_WR_CMD(0x0300, 0x0101);
	LCD_WR_CMD(0x0301, 0x0B2C);
	LCD_WR_CMD(0x0302, 0x1030);
	LCD_WR_CMD(0x0303, 0x3010);
	LCD_WR_CMD(0x0304, 0x2C0B);
	LCD_WR_CMD(0x0305, 0x0101);
	LCD_WR_CMD(0x0306, 0x0807);
	LCD_WR_CMD(0x0307, 0x0708);
	LCD_WR_CMD(0x0308, 0x0107);
	LCD_WR_CMD(0x0309, 0x0105);
	LCD_WR_CMD(0x030A, 0x0F04);
	LCD_WR_CMD(0x030B, 0x0F00);
	LCD_WR_CMD(0x030C, 0x000F);
	LCD_WR_CMD(0x030D, 0x040F);
	LCD_WR_CMD(0x030E, 0x0300);
	LCD_WR_CMD(0x030F, 0x0701);
	LCD_WR_CMD(0x0400, 0x3500);
	LCD_WR_CMD(0x0401, 0x0001);
	LCD_WR_CMD(0x0404, 0x0000);
	LCD_WR_CMD(0x0500, 0x0000);
	LCD_WR_CMD(0x0501, 0x0000);
	LCD_WR_CMD(0x0502, 0x0000);
	LCD_WR_CMD(0x0503, 0x0000);
	LCD_WR_CMD(0x0504, 0x0000);
	LCD_WR_CMD(0x0505, 0x0000);
	LCD_WR_CMD(0x0600, 0x0000);
	LCD_WR_CMD(0x0606, 0x0000);
	LCD_WR_CMD(0x06F0, 0x0000);
	LCD_WR_CMD(0x07F0, 0x5420);
	LCD_WR_CMD(0x07DE, 0x0000);
	LCD_WR_CMD(0x07F2, 0x00DF);
	LCD_WR_CMD(0x07F3, 0x0810);
	LCD_WR_CMD(0x07F4, 0x0077);
	LCD_WR_CMD(0x07F5, 0x0021);
	LCD_WR_CMD(0x07F0, 0x0000);
	LCD_WR_CMD(0x0007, 0x0173);

	/* 设置显示窗口 WINDOWS */
	LCD_WR_CMD(0x0210, 0);	/* 水平起始地址 */
	LCD_WR_CMD(0x0211, 239);	/* 水平结束坐标 */
	LCD_WR_CMD(0x0212, 0);	/* 垂直起始地址 */
	LCD_WR_CMD(0x0213, 399);	/* 垂直结束地址 */

   
}

/******************* (C) COPYRIGHT 2011 奋斗STM32 *****END OF FILE****/
