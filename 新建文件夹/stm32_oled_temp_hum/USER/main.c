#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "key.h"
#include "adc.h"
#include "oled.h"
#include "dht11.h"

u8 S_temperature1=30,S_humidity1=15;// ������
u8 S_temperature2=40,S_humidity2=15;//���
u8 S_temperature3=35,S_humidity3=15;//�й���
u8 S_temperature4=45,S_humidity4=15;//Ұ����
u8 S_temperature5=40,S_humidity5=15;// �ն���


u8 S_temperature6=30,S_humidity6=20;//����
u8 S_temperature7=30,S_humidity7=15;// ���ݴ�
u8 S_temperature8=40,S_humidity8=15;//ë��

u8 S_temperature9=40,S_humidity9=15;//�Զ���

u8 S_temperature,S_humidity;

u8 temperature,humidity;  //�¶�/ʪ��

#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos ʹ��	  
#endif
 
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
  USART1->DR = (u8) ch;      
	return ch;
}
#endif 
 
#if EN_USART1_RX   //���ʹ���˽���

u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
u16 USART_RX_STA=0;       //����״̬���	  


void uart_init(u32 bound)
{
    //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��

    //USART1_TX   GPIOA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
    GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9

    //USART1_RX	  GPIOA.10��ʼ��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  

    //Usart1 NVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���

    //USART ��ʼ������

    USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

    USART_Init(USART1, &USART_InitStructure); //��ʼ������1
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
    USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 
}



#endif	


u8 tmp_min = 10;
u8 tmp_max = 45;
u8 hum_min = 22;
u8 hum_max = 23;
u8 key_up_flag = 0;//�ϰ���������
u8 key_dn_flag = 0;//�°���������

char str[16];



/*��ʱ��3���ڴ��ڽ��ճ�ʱ*/
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
         
    TIM_TimeBaseStructure.TIM_Period= 100;                          // �Զ���װ�ؼĴ�����ֵ
    TIM_TimeBaseStructure.TIM_Prescaler = 71;                         // ʱ��Ԥ��Ƶ��
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;           // ������Ƶ
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;       //���ϼ���
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
    delay_init();	    	 //��ʱ������ʼ��	  

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�

    while(DHT11_Init())	//DHT11��ʼ��	
    {
        delay_ms(200);
    }	
    Adc_Init(); 
    KEY_Init();

    OLED_Init();
    uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
    OLED_ColorTurn(0);//0������ʾ��1 ��ɫ��ʾ
    OLED_DisplayTurn(0);//0������ʾ 1 ��Ļ��ת��ʾ
    OLED_Refresh();
    OLED_Clear();
    
    OLED_ShowChinese(0,0,23,16);//��ʪ�ȼ��ϵͳ
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
             OLED_ShowString(0,40,"                ",16);//ð��
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
                OLED_ShowString(0,40,str,16);//ð��
                break;
			case 1:// ����¶�
					OLED_ShowChinese(0,40,30,16);//��
					OLED_ShowChinese(18,40,31,16);//��
					OLED_ShowChinese(36,40,23,16);//��
                    OLED_ShowChinese(54,40,25,16);//��
                    OLED_ShowString(72,40,":",16);//ð��
            
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
			case 2://����¶�
					OLED_ShowChinese(0,40,30,16);//��
					OLED_ShowChinese(18,40,32,16);//��
					OLED_ShowChinese(36,40,23,16);//��
                    OLED_ShowChinese(54,40,25,16);//��
                    OLED_ShowString(72,40,":",16);//ð��
            
            
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
			case 3://���ʪ��
					OLED_ShowChinese(0,40,30,16);//��
					OLED_ShowChinese(18,40,31,16);//��
					OLED_ShowChinese(36,40,24,16);//ʪ
                    OLED_ShowChinese(54,40,25,16);//��
                    OLED_ShowString(72,40,":",16);//ð��
            
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
			case 4:// ���ʪ��
					OLED_ShowChinese(0,40,30,16);//��
					OLED_ShowChinese(18,40,32,16);//��
					OLED_ShowChinese(36,40,24,16);//ʪ
                    OLED_ShowChinese(54,40,25,16);//��
                    OLED_ShowString(72,40,":",16);//ð��
            
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
			
        DHT11_Read_Data(&temperature,&humidity);	//��ȡ��ʪ��ֵ
        
        
        if(temperature > tmp_max)//�¶ȹ��߷���ת
        {
             Moto=0;
            
            
           
           
        }
        else 
        {

            
             Moto=1;
        }
        
        
        if(temperature<tmp_min)//�¶ȹ�����������
        {
            LED2  = 1;
        }
        else
        {
            LED2 = 0;
        }
        
        alarm_flag = 0;
                
        /*�����¶Ȼ�ʪ������һ����Χ�ͱ���*/
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

        
        OLED_ShowString(0,20,"T:",16);//��ǰ�¶�
        OLED_ShowNum(20,20,temperature,3,16);
        OLED_ShowString(50,20,"C",16);

        OLED_ShowString(72,20,"H:",16);//��ǰʪ��
        OLED_ShowNum(90,20,humidity,3,16);
        OLED_ShowString(120,20,"%",16);

//        OLED_ShowNum(55,40,S_temperature,3,16);//��ǰ�¶�
//        OLED_ShowString(80,40,"C",16);


//        OLED_ShowNum(90,40,S_humidity,3,16);//��ǰʪ��
//        OLED_ShowString(120,40,"%",16);

        OLED_Refresh();
        if(uart_send_falg)
        {
            uart_send_falg = 0;
            printf("%d,%d,%d,%d,%d,%d\r\n",temperature,humidity,tmp_min,tmp_max,hum_min,hum_max);
        }
        
	}
}
