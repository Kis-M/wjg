#include "led.h"
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

    //Usart1 NVIC 配置
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
    NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器

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


u8 tmp_min = 10;
u8 tmp_max = 45;
u8 hum_min = 22;
u8 hum_max = 23;
u8 key_up_flag = 0;//上按键被按下
u8 key_dn_flag = 0;//下按键被按下

char str[16];



/*定时器3用于串口接收超时*/
void TIM3_INIT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_ICInitTypeDef TIM_ICInitStructure; 
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;      
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    /* Enable the TIM3 global Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
         
    TIM_TimeBaseStructure.TIM_Period= 100;                          // 自动重装载寄存器的值
    TIM_TimeBaseStructure.TIM_Prescaler = 71;                         // 时钟预分频数
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;           // 采样分频
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;       //向上计数
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
    /* TIM enable counter */
 
   /* Enable the CC2 Interrupt Request */
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); 
    
    TIM_Cmd(TIM3, ENABLE);    
}

int uart_send_falg = 0;

void TIM3_IRQHandler(void)
{
	static int time =0;

	TIM3->SR = (uint16_t)~TIM_FLAG_Update;
    if(time<10000)
    {
        time++;
    }
    else
    {
        time = 0;
        uart_send_falg = 1;
        
    }
    
    
}

u8 alarm_flag = 0;
int main(void)//a1 a2
{ 	  
	
    u8 flg=0,i=0;  
     LED_Init();
    delay_init();	    	 //延时函数初始化	  

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级

    while(DHT11_Init())	//DHT11初始化	
    {
        delay_ms(200);
    }	
    Adc_Init(); 
    KEY_Init();

    OLED_Init();
    uart_init(9600);	 	//串口初始化为9600
    OLED_ColorTurn(0);//0正常显示，1 反色显示
    OLED_DisplayTurn(0);//0正常显示 1 屏幕翻转显示
    OLED_Refresh();
    OLED_Clear();
    
    OLED_ShowChinese(0,0,23,16);//温湿度检测系统
    OLED_ShowChinese(18,0,24,16);
    OLED_ShowChinese(36,0,25,16);
    OLED_ShowChinese(54,0,26,16);
    OLED_ShowChinese(72,0,27,16);
    OLED_ShowChinese(90,0,28,16);
    OLED_ShowChinese(108,0,29,16);   

    TIM3_INIT();    
    
	while(1)
	{	 
		if(KEY1==0)
		{
			while(KEY1==0){};
            
			i++;
            if(i > 4)
            {
                i=0;
            } 
             OLED_ShowString(0,40,"                ",16);//冒号
		}
        
		if(KEY2==0)
		{
			while(KEY2==0){};  
            key_up_flag = 1;            
		}  

		if(KEY3==0)
		{
			while(KEY3==0){};  
            key_dn_flag = 1;            
		} 
        
        
		switch(i)
		{
            case 0:
                sprintf(str,"T:%02d-%02d H:%02d-%02d",tmp_min,tmp_max,hum_min,hum_max);
                OLED_ShowString(0,40,str,16);//冒号
                break;
			case 1:// 最高温度
					OLED_ShowChinese(0,40,30,16);//最
					OLED_ShowChinese(18,40,31,16);//高
					OLED_ShowChinese(36,40,23,16);//温
                    OLED_ShowChinese(54,40,25,16);//度
                    OLED_ShowString(72,40,":",16);//冒号
            
                    if(key_up_flag)
                    {
                        key_up_flag = 0;
                        
                        if(tmp_max<51)
                        {
                            tmp_max++;
                        }
                    }
                    
                    if(key_dn_flag)
                    {
                        key_dn_flag = 0;
                        
                        
                        if(tmp_max>0)
                        {
                            tmp_max--;
                        }
                    }

                    OLED_ShowNum(82,40,tmp_max,3,16);                    
                    break;
			case 2://最低温度
					OLED_ShowChinese(0,40,30,16);//最
					OLED_ShowChinese(18,40,32,16);//低
					OLED_ShowChinese(36,40,23,16);//温
                    OLED_ShowChinese(54,40,25,16);//度
                    OLED_ShowString(72,40,":",16);//冒号
            
            
                    if(key_up_flag)
                    {
                        key_up_flag = 0;
                        
                        if(tmp_min<51)
                        {
                            tmp_min++;
                        }
                    }
                    
                    if(key_dn_flag)
                    {
                        key_dn_flag = 0;
                        
                        
                        if(tmp_min>0)
                        {
                            tmp_min--;
                        }
                    }

                    OLED_ShowNum(82,40,tmp_min,3,16);        
					break;
			case 3://最高湿度
					OLED_ShowChinese(0,40,30,16);//最
					OLED_ShowChinese(18,40,31,16);//高
					OLED_ShowChinese(36,40,24,16);//湿
                    OLED_ShowChinese(54,40,25,16);//度
                    OLED_ShowString(72,40,":",16);//冒号
            
                    if(key_up_flag)
                    {
                        key_up_flag = 0;
                        
                        if(hum_max<101)
                        {
                            hum_max++;
                        }
                    }
                    
                    if(key_dn_flag)
                    {
                        key_dn_flag = 0;
                        
                        
                        if(hum_max>0)
                        {
                            hum_max--;
                        }
                    }

                    OLED_ShowNum(82,40,hum_max,3,16);               
            
            
					break;
			case 4:// 最低湿度
					OLED_ShowChinese(0,40,30,16);//最
					OLED_ShowChinese(18,40,32,16);//高
					OLED_ShowChinese(36,40,24,16);//湿
                    OLED_ShowChinese(54,40,25,16);//度
                    OLED_ShowString(72,40,":",16);//冒号
            
                    if(key_up_flag)
                    {
                        key_up_flag = 0;
                        
                        if(hum_min<101)
                        {
                            hum_min++;
                        }
                    }
                    
                    if(key_dn_flag)
                    {
                        key_dn_flag = 0;
                        
                        
                        if(hum_min>0)
                        {
                            hum_min--;
                        }
                    }

                    OLED_ShowNum(82,40,hum_min,3,16);            
            
				break;
                    
            default:
                break;
			}
			
        DHT11_Read_Data(&temperature,&humidity);	//读取温湿度值
        
        
        if(temperature > tmp_max)//温度过高风扇转
        {
             Moto=0;
            
            
           
           
        }
        else 
        {

            
             Moto=1;
        }
        
        
        if(temperature<tmp_min)//温度过低新增灯亮
        {
            LED2  = 1;
        }
        else
        {
            LED2 = 0;
        }
        
        alarm_flag = 0;
                
        /*超出温度或湿度任意一个范围就报警*/
        if((humidity < hum_min)||(humidity>hum_max)||(temperature < tmp_min)||(temperature>tmp_max))
        {
            alarm_flag = 1;
           
        }

        if(alarm_flag)
        {
            BEEP=0;
            LED=~LED;
        }
        else
        {
            LED = 1;
            BEEP =1;
        }

        
        OLED_ShowString(0,20,"T:",16);//当前温度
        OLED_ShowNum(20,20,temperature,3,16);
        OLED_ShowString(50,20,"C",16);

        OLED_ShowString(72,20,"H:",16);//当前湿度
        OLED_ShowNum(90,20,humidity,3,16);
        OLED_ShowString(120,20,"%",16);

//        OLED_ShowNum(55,40,S_temperature,3,16);//当前温度
//        OLED_ShowString(80,40,"C",16);


//        OLED_ShowNum(90,40,S_humidity,3,16);//当前湿度
//        OLED_ShowString(120,40,"%",16);

        OLED_Refresh();
        if(uart_send_falg)
        {
            uart_send_falg = 0;
            printf("%d,%d,%d,%d,%d,%d\r\n",temperature,humidity,tmp_min,tmp_max,hum_min,hum_max);
        }
        
	}
}
