#ifndef __OLED_H
#define __OLED_H 

#include "sys.h"
#include "stdlib.h"	

//-----------------≤‚ ‘LED∂Àø⁄∂®“Â---------------- 

#define LED_ON GPIO_ResetBits(GPIOB,GPIO_Pin_8)
#define LED_OFF GPIO_SetBits(GPIOB,GPIO_Pin_8)

//-----------------OLED∂Àø⁄∂®“Â---------------- 

#define OLED_SCLK_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_8)
#define OLED_SCLK_Set() GPIO_SetBits(GPIOB,GPIO_Pin_8)//SCL

#define OLED_SDIN_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_9)//DIN
#define OLED_SDIN_Set() GPIO_SetBits(GPIOB,GPIO_Pin_9)

#define OLED_RST_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_0)//RES
#define OLED_RST_Set() GPIO_SetBits(GPIOB,GPIO_Pin_0)

#define OLED_DC_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_1)//RES


#define OLED_CMD  0	//–¥√¸¡Ó
#define OLED_DATA 1	//–¥ ˝æ›
#define u8 unsigned char
#define u32 unsigned int

void OLED_ClearPoint(u8 x,u8 y);
void OLED_ColorTurn(u8 i);
void OLED_DisplayTurn(u8 i);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_WaitAck(void);
void Send_Byte(u8 dat);
void OLED_WR_Byte(u8 dat,u8 mode);
void OLED_DisPlay_On(void);  //ÂºÄÂêØ
void OLED_DisPlay_Off(void); //ÂÖ≥Èó≠
void OLED_Refresh(void);  //Êõ¥Êñ∞
void OLED_Clear(void); //Ê∏ÖÂ±è 
void OLED_DrawPoint(u8 x,u8 y); //ÊòæÁ§∫‰ΩçÁΩÆ
void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2); //ÁîªÁ∫ø
void OLED_DrawCircle(u8 x,u8 y,u8 r);  //ÁîªÂúÜ
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 size1);  //ÈÄâÊã©Â≠ó‰Ωì
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 size1);  //ÊòæÁ§∫Â≠óÁ¨¶‰∏≤
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size1);
void OLED_ShowChinese(u8 x,u8 y,u8 num,u8 size1);
void OLED_ScrollDisplay(u8 num,u8 space);
void OLED_WR_BP(u8 x,u8 y);
void OLED_ShowPicture(u8 x0,u8 y0,u8 x1,u8 y1,u8 BMP[]);
void OLED_Init(void);

#endif