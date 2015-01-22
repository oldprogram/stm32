/****************************************************************************
*
* 文件名: Fun.c
* 内容简述:
*       本例程采用ucGUI3.90版本， 使用了对话框，列表框，点选框，文本框， 编辑框，按钮等部件
*
*/
#include <stddef.h>           /* needed for definition of NULL */
#include "..\GUIinc\GUI.h"
#include "..\GUIinc\WM.h"
#include "..\GUIinc\BUTTON.h"
#include "..\GUIinc\DIALOG.h"
#include "..\GUIinc\LISTBOX.h"
#include "..\GUIinc\EDIT.h"
#include "..\GUIinc\FRAMEWIN.h"	
#include "..\GUIinc\SLIDER.h"	
#include "demo.h"
#include "NRF24L01.h"

void Fun(void);
extern void RX_Mode(void);
extern void TX_Mode(void);	
extern void RX_Mode(void);
extern void TX_Mode(void);
extern void NRF24L01_TXBUF(uint8_t* data_buffer, uint8_t Nb_bytes);

extern void USART_SendChar(USART_TypeDef* USARTx,uint8_t data);
uint8_t control_data,speed_change_flag,i;
/* ucgui类型定义*/ 
WM_HWIN hWin;
WM_HWIN hListBox[8];
WM_HWIN text1,text2,text3,text4,text5,text6,bt[2],edit1,edit2,slider0,rd0,list1,slider1,slider2,slider3,slider4,slider5;
WM_HWIN text_speed1,text_speed2,text_speed3,text_speed4,text_speed5;	
GUI_COLOR DesktopColorOld;
const GUI_FONT* pFont = &GUI_FontComic24B_1;
const GUI_FONT* pFont18 = &GUI_FontComic18B_1;
 
int speed1,speed2,speed3,speed4,speed5;//几个步进电机的速度
char speed_show[3];//用来把speedx转换为char*然后显示用的
/* 定义了对话框资源列表 */
static const GUI_WIDGET_CREATE_INFO aDialogCreate[] = {
  //建立窗体， 大小是800X480  原点在0，0
  { FRAMEWIN_CreateIndirect, "http://beautifulzzzz", 0,0,0, 800, 480, FRAMEWIN_CF_ACTIVE },
  { BUTTON_CreateIndirect,   "SEND",    GUI_ID_BUTTON0,       0,    395,  200,  55 },
 
  { BUTTON_CreateIndirect,   "CLEAR", GUI_ID_BUTTON2,   200,    395, 200,  55 },
  { EDIT_CreateIndirect,     "",       GUI_ID_EDIT1,    0,   190, 400,  65, EDIT_CF_LEFT, 50 },
  { EDIT_CreateIndirect,     "",       GUI_ID_EDIT2,    0,   290, 400,  65, EDIT_CF_LEFT, 50 },
  
  //建立TEXT控件，起点是窗体的X，X，大小XXY  文字左对齐
  { TEXT_CreateIndirect,     "Send Text Area",  GUI_ID_TEXT0,   1,   160,  400,  25, TEXT_CF_LEFT },
  { TEXT_CreateIndirect,     "Receive Text Area ",  GUI_ID_TEXT1,     1,   263,  400, 25, TEXT_CF_LEFT },
 
  { TEXT_CreateIndirect,     "2M bps",  GUI_ID_TEXT2,   23,   22,  140,  25, TEXT_CF_LEFT },
  { TEXT_CreateIndirect,     "1M bps",  GUI_ID_TEXT3,     23,   42,  140,  25, TEXT_CF_LEFT },
  { TEXT_CreateIndirect,     "250K bps",  GUI_ID_TEXT5,     23,   62,  140,  25, TEXT_CF_LEFT },
  
  { TEXT_CreateIndirect,     "",  GUI_ID_TEXT4,     0,   120,  400,  25, TEXT_CF_LEFT },

  { RADIO_CreateIndirect,     "Receive Mode",  GUI_ID_RADIO0,     3,   33,  40,  52, RADIO_TEXTPOS_LEFT,3},

  { LISTBOX_CreateIndirect,  "",       GUI_ID_LISTBOX0,  134,    13,  130,  90, 0, 0 },

   //建立滑块
  { SLIDER_CreateIndirect,   NULL,     GUI_ID_SLIDER1,  440,  60, 320, 25, 0, 0 },
  { SLIDER_CreateIndirect,   NULL,     GUI_ID_SLIDER2,  440,  120, 320, 25, 0, 0 },
  { SLIDER_CreateIndirect,   NULL,     GUI_ID_SLIDER3,  440,  180, 320, 25, 0, 0 },
  { SLIDER_CreateIndirect,   NULL,     GUI_ID_SLIDER4,  440,  240, 320, 25, 0, 0 },
  { SLIDER_CreateIndirect,   NULL,     GUI_ID_SLIDER5,  440,  300, 320, 25, 0, 0 },
  //建立滑块对应的text
  { TEXT_CreateIndirect,     "0",  GUI_ID_TEXT_SPEED1,   770,   60,   25,  25, TEXT_CF_LEFT },
  { TEXT_CreateIndirect,     "0",  GUI_ID_TEXT_SPEED2,   770,   120,  25,  25, TEXT_CF_LEFT },
  { TEXT_CreateIndirect,     "0",  GUI_ID_TEXT_SPEED3,   770,   180,  25,  25, TEXT_CF_LEFT },
  { TEXT_CreateIndirect,     "0",  GUI_ID_TEXT_SPEED4,   770,   240,  25,  25, TEXT_CF_LEFT },
  { TEXT_CreateIndirect,     "0",  GUI_ID_TEXT_SPEED5,   770,   300,  25,  25, TEXT_CF_LEFT },
};

/*  定义了NRF24L01通道选择列表框的初始项目 */
static const GUI_ConstString _apListBox[] = {
  "Pipe 0", "Pipe 1","Pipe 2","Pipe 3","Pipe 4","Pipe 5", NULL
};


/****************************************************************************
* 名    称：static void _cbCallback(WM_MESSAGE * pMsg)
* 功    能：ucgui回调函数，是作为对话框动作响应的函数
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：
****************************************************************************/  
static void _cbCallback(WM_MESSAGE * pMsg) {
  int NCode, Id;
  switch (pMsg->MsgId) {
    case WM_NOTIFY_PARENT:				  		//通知父窗口有事件在窗口部件上发生
      Id    = WM_GetId(pMsg->hWinSrc);    		//获得对话框窗口里发生事件的部件的ID
      NCode = pMsg->Data.v;               		//通知代码
      switch (NCode) {
        case WM_NOTIFICATION_RELEASED:    		//窗体部件动作被释放             
          if (Id == GUI_ID_BUTTON2) {     		//按键CLEAR被松开
            memcpy(status_buf, "", 20);	  		//清空状态文本缓冲区 
			memcpy(rx_buf, "", 32);		  		//清空接收文本缓冲区 		
			TEXT_SetText(text5,(const char *)status_buf);	   	//清空状态文本框	
			EDIT_SetText(edit2,(const char *)rx_buf);			//清空接收字符编辑框
			memcpy(tx_buf, "", 32);				//清空发送文本缓冲区
			NRF24L01_TXBUF(tx_buf,32);			//将发送字符缓冲区的字符通过NRF24L01发送出去		
          }          
		  else if (Id == GUI_ID_BUTTON0) {      //按键SEND 被松开
		  	memcpy(tx_buf, "1234567890abcdefghij!@#$%^&*()-=", 32);	  //将32字节的文本拷贝到发送文本缓冲区
			memcpy(rx_buf, "", 32);				//清空接收文本缓冲区 	
			memcpy(status_buf, "", 20);			//清空状态文本缓冲区 
			EDIT_SetText(edit2,(const char *)rx_buf);			//清空接收字符编辑框	
			NRF24L01_TXBUF(tx_buf,32);			//将发送字符缓冲区的字符通过NRF24L01发送出去
			memcpy(tx_buf, "", 32);				//清空发送文本缓冲区
			TEXT_SetText(text5,(const char *)status_buf);		//清空状态文本框   			
          }
		  else if (Id == GUI_ID_RADIO0) {       //NRF24L01无线速率点选框点选动作完成
		  	nrf_baud= RADIO_GetValue(rd0);		//获得速率表示值
		    RX_Mode();							//进入接收模式			
          }
		  else if (Id == GUI_ID_LISTBOX0){      //NRF24L01无线通道选择动作
			nrf_Pipe= LISTBOX_GetSel(list1);	//获得NRF24LL01无线通道表示值 			
		    RX_Mode();   						//进入接收模式 	
		  }else if(Id == GUI_ID_SLIDER1){       //slider1 的值被改变
			speed1=SLIDER_GetValue(slider1);//获得slider1的值
			if(speed1>0){
			   speed_show[0]='+';
			   speed_show[1]='0'+speed1;
			   control_data=8+speed1;
			}else if(speed1<0){
			   speed_show[0]='-';
			   speed_show[1]='0'-speed1;
			   control_data=16-speed1;
			}else{
			   speed_show[0]=' ';
			   speed_show[1]='0';
			   control_data=0;
			}
//			USART_SendChar(USART1,control_data);
			TEXT_SetText(text_speed1,speed_show);
			speed_change_flag=1;	                 
		  }else if(Id == GUI_ID_SLIDER2){       //slider2 的值被改变
			speed2=SLIDER_GetValue(slider2);//获得slider2的值
			if(speed2>0){
			   speed_show[0]='+';
			   speed_show[1]='0'+speed2;
			   control_data=32+8+speed2;
			}else if(speed2<0){
			   speed_show[0]='-';
			   speed_show[1]='0'-speed2;
			   control_data=32+16-speed2;
			}else{
			   speed_show[0]=' ';
			   speed_show[1]='0';
			   control_data=0;
			}
			TEXT_SetText(text_speed2,speed_show);
			speed_change_flag=1;	  	  
		  }else if(Id == GUI_ID_SLIDER3){       //slider3 的值被改变
			speed3=SLIDER_GetValue(slider3);//获得slider3的值
			if(speed3>0){
			   speed_show[0]='+';
			   speed_show[1]='0'+speed3;
			   control_data=64+8+speed3;
			}else if(speed3<0){
			   speed_show[0]='-';
			   speed_show[1]='0'-speed3;
			   control_data=64+16-speed3;
			}else{
			   speed_show[0]=' ';
			   speed_show[1]='0';
			   control_data=0;
			}
			TEXT_SetText(text_speed3,speed_show);
			speed_change_flag=1;	  
		  }else if(Id == GUI_ID_SLIDER4){       //slider4 的值被改变
		    speed4=SLIDER_GetValue(slider4);//获得slider4的值
			if(speed4>0){
			   speed_show[0]='+';
			   speed_show[1]='0'+speed4;
			   control_data=96+8+speed4;
			}else if(speed4<0){
			   speed_show[0]='-';	  
			   speed_show[1]='0'-speed4;
			   control_data=96+16-speed4;
			}else{
			   speed_show[0]=' ';
			   speed_show[1]='0';
			   control_data=0;
			}
			TEXT_SetText(text_speed4,speed_show);
			speed_change_flag=1;	  
		  }else if(Id == GUI_ID_SLIDER5){       //slider5 的值被改变
			speed5=SLIDER_GetValue(slider5);//获得slider5的值
			if(speed5>0){
			   speed_show[0]='+';
			   speed_show[1]='0'+speed5;
			   control_data=128+8+speed5;
			}else if(speed5<0){
			   speed_show[0]='-';
			   speed_show[1]='0'-speed5;
			   control_data=128+16-speed5;
			}else{
			   speed_show[0]=' ';
			   speed_show[1]='0';
			   control_data=0;
			}
			TEXT_SetText(text_speed5,speed_show);
			speed_change_flag=1;	  
		  }
		 break;
		 default: break;
      }	    
    default:
      WM_DefaultProc(pMsg);						//默认程序来处理消息
	  break;
  }
}


/****************************************************************************
* 名    称：void Fun(void)
* 功    能：显示及处理界面
* 入口参数：无
* 出口参数：无
* 说    明：
* 调用方法：无 
****************************************************************************/
void Fun(void) {   
  GUI_CURSOR_Show();                                        //打开鼠标图形显示  
  
  /* 建立对话框时，包含了资源列表，资源数目， 并且指定了用于动作响应的回调函数  */
  hWin = GUI_CreateDialogBox(aDialogCreate, GUI_COUNTOF(aDialogCreate), _cbCallback, 0, 0, 0);

  FRAMEWIN_SetFont(hWin, &GUI_FontComic18B_1);	  			//对话框字体设置 
  FRAMEWIN_SetClientColor(hWin, GUI_BLACK);		  			//对话框的窗体颜色是黑色
  memcpy(tx_buf, "1234567890abcdefghij!@#$%^&*()-=", 32);   //将长度为32字节的发送字符串拷贝到发送缓冲区，
  memcpy(rx_buf, "", 32);									//将接收缓存区清空
 
  /* 获得文本框句柄 */		
  text1 = WM_GetDialogItem(hWin, GUI_ID_TEXT0);				//获得对话框里GUI_ID_TEXT0项目(文本框Send Text Area)的句柄
  text2 = WM_GetDialogItem(hWin, GUI_ID_TEXT1);				//获得对话框里GUI_ID_TEXT1项目(文本框Receive Text Area)的句柄
  text3 = WM_GetDialogItem(hWin, GUI_ID_TEXT2);				//获得对话框里GUI_ID_TEXT2项目(文本框2M BPS)的句柄
  text4 = WM_GetDialogItem(hWin, GUI_ID_TEXT3);				//获得对话框里GUI_ID_TEXT3项目(文本框1M BPS)的句柄
  text6 = WM_GetDialogItem(hWin, GUI_ID_TEXT5);				//获得对话框里GUI_ID_TEXT5项目(文本框250K BPS)的句柄
  text5 = WM_GetDialogItem(hWin, GUI_ID_TEXT4);				//获得对话框里GUI_ID_TEXT4项目(状态字符文本框)的句柄  
  /* 设置文本框字体 */
  TEXT_SetFont(text1,pFont);							    //设置对话框里文本框Send Text Area的字体
  TEXT_SetFont(text2,pFont);								//设置对话框里文本框Receive Text Area的字体
  TEXT_SetFont(text3,pFont18);								//设置对话框里文本框2M BPS的字体
  TEXT_SetFont(text4,pFont18);								//设置对话框里文本框1M BPS的字体
  TEXT_SetFont(text6,pFont18);								//设置对话框里文本框250K BPS的字体
  TEXT_SetFont(text5,pFont);								//设置对话框里状态字符文本框的字体
  /* 设置文本框颜色 */
  TEXT_SetTextColor(text1,GUI_GREEN);						//设置对话框里文本框Send Text Area的字体颜色
  TEXT_SetTextColor(text2,GUI_GREEN );						//设置对话框里文本框Receive Text Area的字体颜色
  TEXT_SetTextColor(text3,GUI_YELLOW);						//设置对话框里文本框2M BPS的字体颜色
  TEXT_SetTextColor(text4,GUI_YELLOW);						//设置对话框里文本框1M BPS的字体颜色
  TEXT_SetTextColor(text6,GUI_YELLOW);   					//设置对话框里文本框250K BPS的字体颜色
  TEXT_SetTextColor(text5,GUI_YELLOW);						//设置对话框里状态字符文本框的字体颜色
  TEXT_SetBkColor(text5,GUI_BLUE);							//设置对话框里状态字符文本框的背景颜色

  /* 编辑框相关 */
  edit1 = WM_GetDialogItem(hWin, GUI_ID_EDIT1);				//获得对话框里GUI_ID_EDIT1项目(编辑框 发送字符串显示区)的句柄
  EDIT_SetFont(edit1,pFont18);								//设置对话框里编辑框 发送字符串显示区的字体
  EDIT_SetText(edit1,(const char *)tx_buf);					//设置对话框里编辑框 发送字符串显示区的字符串
  edit2 = WM_GetDialogItem(hWin, GUI_ID_EDIT2);			    //获得对话框里GUI_ID_EDIT2项目(编辑框 接收字符串显示区)的句柄
  EDIT_SetFont(edit2,pFont18);								//设置对话框里编辑框 接收字符串显示区的字体
  EDIT_SetText(edit2,(const char *)rx_buf);					//设置对话框里编辑框 接收字符串显示区的字符串

  /* 按钮相关 */
  bt[0]=WM_GetDialogItem(hWin,GUI_ID_BUTTON0);				//获得对话框里GUI_ID_BUTTON0项目(按键SEND)的句柄
  bt[1]=WM_GetDialogItem(hWin, GUI_ID_BUTTON2);				//获得对话框里GUI_ID_BUTTON2项目(按键CLEAR)的句柄
  BUTTON_SetFont(bt[0],pFont);								//设置对话框里按键SEND的字体
  BUTTON_SetFont(bt[1],pFont);								//设置对话框里按键CLEAR的字体
  BUTTON_SetTextColor(bt[0],0,GUI_WHITE); 					//设置对话框里按键SEND未被按下的字体颜色
  BUTTON_SetTextColor(bt[1],0,GUI_WHITE);					//设置对话框里按键CLEAR未被按下的字体颜色

  /* List相关 */			
  nrf_Pipe=0;												//NRF24L01初始发射通道设置为0
  list1 = WM_GetDialogItem(hWin, GUI_ID_LISTBOX0);			//获得对话框里GUI_ID_LISTBOX0项目(列表框-通道选择)的句柄     
  LISTBOX_SetText(list1, _apListBox);						//设置对话框里列表框-通道选择里的条目
  LISTBOX_SetFont(list1,pFont18);							//设置对话框里列表框-通道选择的字体
  LISTBOX_SetSel(list1,nrf_Pipe);							//设置对话框里列表框-通道选择的焦点选择
  SCROLLBAR_CreateAttached(list1, SCROLLBAR_CF_VERTICAL);	//设置对话框里列表框-通道选择的卷动方向为下拉		

  /* Radio按钮相关 */		
  rd0 = WM_GetDialogItem(hWin, GUI_ID_RADIO0);				//获得对话框里GUI_ID_RADIO0项目(点选框-速率选择)的句柄
  nrf_baud=0;												//NRF24L01速率 初始为2MPS
  RADIO_SetValue(rd0,0);									//设置对话框里点选框-速率选择的焦点选择
  RX_Mode();												//NRF24L01进入接收模式 
 
  /* 获得slider部件的句柄 */    
  slider1 = WM_GetDialogItem(hWin, GUI_ID_SLIDER1);
  slider2 = WM_GetDialogItem(hWin, GUI_ID_SLIDER2);
  slider3 = WM_GetDialogItem(hWin, GUI_ID_SLIDER3);
  slider4 = WM_GetDialogItem(hWin, GUI_ID_SLIDER4);
  slider5 = WM_GetDialogItem(hWin, GUI_ID_SLIDER5);
  /* 设置slider部件的取值范围-8-8*/  
  SLIDER_SetRange(slider1,-8,8);	
  SLIDER_SetRange(slider2,-8,8);
  SLIDER_SetRange(slider3,-8,8);
  SLIDER_SetRange(slider4,-8,8);
  SLIDER_SetRange(slider5,-8,8);
  /* 设置slider部件的值*/      
  SLIDER_SetValue(slider1,0);  
  SLIDER_SetValue(slider2,0);    
  SLIDER_SetValue(slider3,0);  
  SLIDER_SetValue(slider4,0);  
  SLIDER_SetValue(slider5,0);  
  /* 获取文本框句柄 */
  text_speed1 = WM_GetDialogItem(hWin, GUI_ID_TEXT_SPEED1);	
  text_speed2 = WM_GetDialogItem(hWin, GUI_ID_TEXT_SPEED2);	
  text_speed3 = WM_GetDialogItem(hWin, GUI_ID_TEXT_SPEED3);	
  text_speed4 = WM_GetDialogItem(hWin, GUI_ID_TEXT_SPEED4);	
  text_speed5 = WM_GetDialogItem(hWin, GUI_ID_TEXT_SPEED5);	
  /* 设置文本框字体 */
  TEXT_SetFont(text_speed1,pFont18);
  TEXT_SetFont(text_speed2,pFont18);
  TEXT_SetFont(text_speed3,pFont18);
  TEXT_SetFont(text_speed4,pFont18);
  TEXT_SetFont(text_speed5,pFont18);									
  /* 设置文本框颜色 */
  TEXT_SetTextColor(text_speed1,GUI_YELLOW);		
  TEXT_SetTextColor(text_speed2,GUI_YELLOW);		
  TEXT_SetTextColor(text_speed3,GUI_YELLOW);		
  TEXT_SetTextColor(text_speed4,GUI_YELLOW);		
  TEXT_SetTextColor(text_speed5,GUI_YELLOW);		

  speed_change_flag=0;

  while (1)
  {	   		
	if(Rx_Succ==1){	                                        //当NRF24L01接收到有效数据
		EDIT_SetText(edit2,(const char *)rx_buf);		    //将接收缓冲区的字符写入到接收字符编辑框内
		TEXT_SetText(text5,(const char *)status_buf);		//将状态文本缓冲区的字符写入到状态文本框内
		Rx_Succ=0; 
//		for(i=0;i<sizeof(rx_buf);i++)		
//			USART_SendChar(USART1,rx_buf[i]);
	}
	if(speed_change_flag!=0)
	{
	   speed_change_flag=0;
	   USART_SendChar(USART1,control_data);
	}
	WM_Exec();									            //刷新屏幕
  }	  
}