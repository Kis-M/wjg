��#include "led.h"
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
  //����TX����RX������ 
  
  //Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  //��ռ���ȼ��������ȼ����ӳ�����Ա������ȼ����ӳ���Ӱ�����ȼ��ߵĳ�����ִ��

	
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

int main(void)//a1 a2
{ 	  
	
  u8 flg=0,i=0;  
	delay_init();	    	 //��ʱ������ʼ��	  
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	
	while(DHT11_Init())	//DHT11��ʼ��	
	{
		delay_ms(200);
	}	
	Adc_Init(); 
	KEY_Init();
	LED_Init();
  OLED_Init();uart_init(4800);	 	//���ڳ�ʼ��Ϊ9600
	OLED_ColorTurn(0);//0������ʾ��1 ��ɫ��ʾ
  OLED_DisplayTurn(0);//0������ʾ 1 ��Ļ��ת��ʾ
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
			case 1:// ������
					OLED_ShowChinese(0,40,2,16);
					OLED_ShowChinese(18,40,3,16);
					OLED_ShowChinese(36,40,0,16);
					S_temperature=S_temperature1;
					S_humidity=S_humidity1;
			
			    if(temperature>S_temperature1){BEEP=0;LED=~LED;}//�¶ȹ��߱���
					else {BEEP=1;LED=1;}
					if(humidity<S_humidity1){Moto=0;}//ʪ�ȹ��ʹ򿪵��
					else {Moto=1;}
							break;
			case 2://���
					OLED_ShowChinese(0,40,5,16);
					OLED_ShowChinese(18,40,4,16);
          OLED_ShowString(36,40,"  ",16);
			    S_temperature=S_temperature2;
					S_humidity=S_humidity2;
					if(temperature>S_temperature2){BEEP=0;LED=~LED;}//�¶ȹ��߱���
					else {BEEP=1;LED=1;}
					if(humidity<S_humidity2){Moto=0;}//ʪ�ȹ��ʹ򿪵��
					else {Moto=1;}
							break;
			case 3://�й���
					OLED_ShowChinese(0,40,6,16);
					OLED_ShowChinese(18,40,7,16);
					OLED_ShowChinese(36,40,0,16);
					S_temperature=S_temperature3;
					S_humidity=S_humidity3;
								
					if(temperature>S_temperature3){BEEP=0;LED=~LED;}//�¶ȹ��߱���
					else {BEEP=1;LED=1;}
					if(humidity<S_humidity3){Moto=0;}//ʪ�ȹ��ʹ򿪵��
					else {Moto=1;}
							break;
			case 4:// Ұ���� 
					OLED_ShowChinese(0,40,8,16);
					OLED_ShowChinese(18,40,9,16);
					OLED_ShowChinese(36,40,0,16);
					S_temperature=S_temperature4;
					S_humidity=S_humidity4;
						
					if(temperature>S_temperature4){BEEP=0;LED=~LED;}//�¶ȹ��߱���
					else {BEEP=1;LED=1;}
					if(humidity<S_humidity4){Moto=0;}//ʪ�ȹ��ʹ򿪵��
					else {Moto=1;}
							break;
			case 5://�ն���
					OLED_ShowChinese(0,40,10,16);
					OLED_ShowChinese(18,40,11,16);
					OLED_ShowChinese(36,40,0,16);
					S_temperature=S_temperature5;
					S_humidity=S_humidity5;
						
					if(temperature>S_temperature5){BEEP=0;LED=~LED;}//�¶ȹ��߱���
					else {BEEP=1;LED=1;}
					if(humidity<S_humidity5){Moto=0;}//ʪ�ȹ��ʹ򿪵��
					else {Moto=1;}
							break;
			case 6://����
					OLED_ShowChinese(0,40,13,16);
					OLED_ShowChinese(18,40,14,16);
					OLED_ShowChinese(36,40,0,16);
				  S_temperature=S_temperature6;
					S_humidity=S_humidity6;
						
					if(temperature>S_temperature6){BEEP=0;LED=~LED;}//�¶ȹ��߱���
					else {BEEP=1;LED=1;}
					if(humidity<S_humidity6){Moto=0;}//ʪ�ȹ��ʹ򿪵��
					else {Moto=1;}
							break;
			case 7://���ݴ�
					OLED_ShowChinese(0,40,15,16);
					OLED_ShowChinese(18,40,16,16);
					OLED_ShowChinese(36,40,17,16);
					S_temperature=S_temperature7;
					S_humidity=S_humidity7;
							
					if(temperature>S_temperature7){BEEP=0;LED=~LED;}//�¶ȹ��߱���
					else {BEEP=1;LED=1;}
					if(humidity<S_humidity7){Moto=0;}//ʪ�ȹ��ʹ򿪵��
					else {Moto=1;}
							break;
			case 8://ë��
					OLED_ShowChinese(0,40,18,16);
					OLED_ShowChinese(18,40,19,16);
          OLED_ShowString(36,40,"  ",16);
				  S_temperature=S_temperature8;
					S_humidity=S_humidity8;
							
					if(temperature>S_temperature8){BEEP=0;LED=~LED;}//�¶ȹ��߱���
					else {BEEP=1;LED=1;}
					if(humidity<S_humidity8){Moto=0;}//ʪ�ȹ��ʹ򿪵��
					else {Moto=1;}
							break;
			case 9://�Զ���
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
				
					if(temperature>S_temperature9){BEEP=0;LED=~LED;}//�¶ȹ��߱���
					else {BEEP=1;LED=1;}
					if(humidity<S_humidity9){Moto=0;}//ʪ�ȹ��ʹ򿪵��
					else {Moto=1;}
							break;
			case 10://�Զ���
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
			
					if(temperature>S_temperature9){BEEP=0;LED=~LED;}//�¶ȹ��߱���
					else {BEEP=1;LED=1;}
					if(humidity<S_humidity9){Moto=0;}//ʪ�ȹ��ʹ򿪵��
					else {Moto=1;}
							break;
		}
		
		
		
    DHT11_Read_Data(&temperature,&humidity);	//��ȡ��ʪ��ֵ
		
		OLED_ShowChinese(0,0,23,16);//��ʪ�ȼ��ϵͳ
		OLED_ShowChinese(18,0,24,16);
		OLED_ShowChinese(36,0,25,16);
		OLED_ShowChinese(54,0,26,16);
		OLED_ShowChinese(72,0,27,16);
		OLED_ShowChinese(90,0,28,16);
		OLED_ShowChinese(108,0,29,16);
		
		

		OLED_ShowString(0,20,"T:",16);//��ǰ�¶�
		OLED_ShowNum(20,20,temperature,3,16);
		OLED_ShowString(50,20,"C",16);
		
	
    OLED_ShowString(72,20,"H:",16);//��ǰʪ��
		OLED_ShowNum(90,20,humidity,3,16);
		OLED_ShowString(120,20,"%",16);
		
		

		
		
		OLED_ShowNum(55,40,S_temperature,3,16);//��ǰ�¶�
		OLED_ShowString(80,40,"C",16);
		
	
   
		OLED_ShowNum(90,40,S_humidity,3,16);//��ǰʪ��
		OLED_ShowString(120,40,"%",16);

		OLED_Refresh();


	}
}
