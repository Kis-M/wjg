#include "key.h"
#include "delay.h"

void KEY_Init(void)
{
   GPIO_InitTypeDef  GPIO_InitStructure;
 	
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PB,PA�˿�ʱ��
	
   GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_12;			
	
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
   GPIO_Init(GPIOB, &GPIO_InitStructure);	

}

