，#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "key.h"
#include "adc.h"
#include "oled.h"
#include "dht11.h"

u8 S_temperature1=30,S_humidity1=15;// 古树红
u8 S_temperature2=40,S_humidity2=15;//滇红
u8 S_temperature3=35,S_humidity3=15;//中国红
u8 S_temperature4=45,S_humidity4=15;//野生红
u8 S_temperature5=40,S_humidity5=15;// 普尔茶


u8 S_temperature6=30,S_humidity6=20;//龙井
u8 S_temperature7=30,S_humidity7=15;// 碧螺春
u8 S_temperature8=40,S_humidity8=15;//毛尖

u8 S_temperature9=40,S_humidity9=15;//自定义

u8 S_temperature,S_humidity;

u8 temperature,humidity;  //温度/湿度

#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos 使用	  
#endif
 
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
  USART1->DR = (u8) ch;      
	return ch;
}
#endif 
 
#if EN_USART1_RX   //如果使能了接收

u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
u16 USART_RX_STA=0;       //接收状态标记	  


void uart_init(u32 bound)
{
  //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
   
  //USART1_RX	  GPIOA.10初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  
  //配置TX，和RX两根线 
  
  //Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  //抢占优先级，低优先级的子程序可以被高优先级的子程序影像，优先级高的程序先执行

	
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART1, &USART_InitStructure); //初始化串口1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART1, ENABLE);                    //使能串口1 
}



#endif	

int main(void)//a1 a2
{ 	  
	
  u8 flg=0,i=0;  
	delay_init();	    	 //延时函数初始化	  
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	
	while(DHT11_Init())	//DHT11初始化	
	{
		delay_ms(200);
	}	
	Adc_Init(); 
	KEY_Init();
	LED_Init();
  OLED_Init();uart_init(4800);	 	//串口初始化为9600
	OLED_ColorTurn(0);//0正常显示，1 反色显示
  OLED_DisplayTurn(0);//0正常显示 1 屏幕翻转显示
	OLED_Refresh();OLED_Clear();
	while(1)
	{	 
		if(KEY1==0)
		{
			i++;if(i>10)i=0;
			while(KEY1==0);
		}
		switch(i)
		{
			case 1:// 古树红
					OLED_ShowChinese(0,40,2,16);
					OLED_ShowChinese(18,40,3,16);
					OLED_ShowChinese(36,40,0,16);
					S_temperature=S_temperature1;
					S_humidity=S_humidity1;
			
			    if(temperature>S_temperature1){BEEP=0;LED=~LED;}//温度过高报警
					else {BEEP=1;LED=1;}
					if(humidity<S_humidity1){Moto=0;}//湿度过低打开电机
					else {Moto=1;}
							break;
			case 2://滇红
					OLED_ShowChinese(0,40,5,16);
					OLED_ShowChinese(18,40,4,16);
          OLED_ShowString(36,40,"  ",16);
			    S_temperature=S_temperature2;
					S_humidity=S_humidity2;
					if(temperature>S_temperature2){BEEP=0;LED=~LED;}//温度过高报警
					else {BEEP=1;LED=1;}
					if(humidity<S_humidity2){Moto=0;}//湿度过低打开电机
					else {Moto=1;}
							break;
			case 3://中国红
					OLED_ShowChinese(0,40,6,16);
					OLED_ShowChinese(18,40,7,16);
					OLED_ShowChinese(36,40,0,16);
					S_temperature=S_temperature3;
					S_humidity=S_humidity3;
								
					if(temperature>S_temperature3){BEEP=0;LED=~LED;}//温度过高报警
					else {BEEP=1;LED=1;}
					if(humidity<S_humidity3){Moto=0;}//湿度过低打开电机
					else {Moto=1;}
							break;
			case 4:// 野生红 
					OLED_ShowChinese(0,40,8,16);
					OLED_ShowChinese(18,40,9,16);
					OLED_ShowChinese(36,40,0,16);
					S_temperature=S_temperature4;
					S_humidity=S_humidity4;
						
					if(temperature>S_temperature4){BEEP=0;LED=~LED;}//温度过高报警
					else {BEEP=1;LED=1;}
					if(humidity<S_humidity4){Moto=0;}//湿度过低打开电机
					else {Moto=1;}
							break;
			case 5://普尔茶
					OLED_ShowChinese(0,40,10,16);
					OLED_ShowChinese(18,40,11,16);
					OLED_ShowChinese(36,40,0,16);
					S_temperature=S_temperature5;
					S_humidity=S_humidity5;
						
					if(temperature>S_temperature5){BEEP=0;LED=~LED;}//温度过高报警
					else {BEEP=1;LED=1;}
					if(humidity<S_humidity5){Moto=0;}//湿度过低打开电机
					else {Moto=1;}
							break;
			case 6://龙井
					OLED_ShowChinese(0,40,13,16);
					OLED_ShowChinese(18,40,14,16);
					OLED_ShowChinese(36,40,0,16);
				  S_temperature=S_temperature6;
					S_humidity=S_humidity6;
						
					if(temperature>S_temperature6){BEEP=0;LED=~LED;}//温度过高报警
					else {BEEP=1;LED=1;}
					if(humidity<S_humidity6){Moto=0;}//湿度过低打开电机
					else {Moto=1;}
							break;
			case 7://碧螺春
					OLED_ShowChinese(0,40,15,16);
					OLED_ShowChinese(18,40,16,16);
					OLED_ShowChinese(36,40,17,16);
					S_temperature=S_temperature7;
					S_humidity=S_humidity7;
							
					if(temperature>S_temperature7){BEEP=0;LED=~LED;}//温度过高报警
					else {BEEP=1;LED=1;}
					if(humidity<S_humidity7){Moto=0;}//湿度过低打开电机
					else {Moto=1;}
							break;
			case 8://毛尖
					OLED_ShowChinese(0,40,18,16);
					OLED_ShowChinese(18,40,19,16);
          OLED_ShowString(36,40,"  ",16);
				  S_temperature=S_temperature8;
					S_humidity=S_humidity8;
							
					if(temperature>S_temperature8){BEEP=0;LED=~LED;}//温度过高报警
					else {BEEP=1;LED=1;}
					if(humidity<S_humidity8){Moto=0;}//湿度过低打开电机
					else {Moto=1;}
							break;
			case 9://自定义
					OLED_ShowChinese(0,40,20,16);
					OLED_ShowChinese(18,40,21,16);
          OLED_ShowChinese(36,40,22,16);
			if(KEY2==0)
			{
				S_temperature9++;
				delay_ms(100);
			}
			if(KEY3==0)
			{
				S_temperature9--;
				delay_ms(100);
			}
			    
				  S_temperature=S_temperature9;
					S_humidity=S_humidity9;
				
					if(temperature>S_temperature9){BEEP=0;LED=~LED;}//温度过高报警
					else {BEEP=1;LED=1;}
					if(humidity<S_humidity9){Moto=0;}//湿度过低打开电机
					else {Moto=1;}
							break;
			case 10://自定义
					OLED_ShowChinese(0,40,20,16);
					OLED_ShowChinese(18,40,21,16);
          OLED_ShowChinese(36,40,22,16);
			if(KEY2==0)
			{
				S_humidity9++;
				delay_ms(100);
			}
			if(KEY3==0)
			{
				S_humidity9--;
				delay_ms(100);
			}
			    
				  S_temperature=S_temperature9;
					S_humidity=S_humidity9;
			
					if(temperature>S_temperature9){BEEP=0;LED=~LED;}//温度过高报警
					else {BEEP=1;LED=1;}
					if(humidity<S_humidity9){Moto=0;}//湿度过低打开电机
					else {Moto=1;}
							break;
		}
		
		
		
    DHT11_Read_Data(&temperature,&humidity);	//读取温湿度值
		
		OLED_ShowChinese(0,0,23,16);//温湿度检测系统
		OLED_ShowChinese(18,0,24,16);
		OLED_ShowChinese(36,0,25,16);
		OLED_ShowChinese(54,0,26,16);
		OLED_ShowChinese(72,0,27,16);
		OLED_ShowChinese(90,0,28,16);
		OLED_ShowChinese(108,0,29,16);
		
		

		OLED_ShowString(0,20,"T:",16);//当前温度
		OLED_ShowNum(20,20,temperature,3,16);
		OLED_ShowString(50,20,"C",16);
		
	
    OLED_ShowString(72,20,"H:",16);//当前湿度
		OLED_ShowNum(90,20,humidity,3,16);
		OLED_ShowString(120,20,"%",16);
		
		

		
		
		OLED_ShowNum(55,40,S_temperature,3,16);//当前温度
		OLED_ShowString(80,40,"C",16);
		
	
   
		OLED_ShowNum(90,40,S_humidity,3,16);//当前湿度
		OLED_ShowString(120,40,"%",16);

		OLED_Refresh();


	}
}
