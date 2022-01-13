/*
 * lcd.h
 *
 *  Created on: Jan 1, 2022
 *      Author: Administrator
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

#include "main.h"
#include "spi.h"


#define LCD_PWR_ON	 HAL_GPIO_WritePin(GPIOB, LCD_PWR_Pin, GPIO_PIN_SET)
#define LCD_PWR_OFF	 HAL_GPIO_WritePin(GPIOB, LCD_PWR_Pin, GPIO_PIN_RESET)

#define LCD_Width 	240
#define LCD_Height 	240

#define WHITE         	 0xFFFF
#define BLACK         	 0x0000
#define BLUE         	 0x001F
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40
#define BRRED 			 0XFC07
#define GRAY  			 0X8430

#define DARKBLUE      	 0X01CF
#define LIGHTBLUE      	 0X7D7C
#define GRAYBLUE       	 0X5458

#define LIGHTGREEN     	 0X841F //Ç³ÂÌÉ«
//#define LIGHTGRAY        0XEF5B //Ç³»ÒÉ«(PANNEL)
#define LGRAY 			 0XC618 //Ç³»ÒÉ«(PANNEL),´°Ìå±³¾°É«

#define LGRAYBLUE        0XA651 //Ç³»ÒÀ¶É«(ÖÐ¼ä²ãÑÕÉ«)
#define LBBLUE           0X2B12 //Ç³×ØÀ¶É«(Ñ¡ÔñÌõÄ¿µÄ·´É«)


void lcd_set_coordinate_area(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void lcd_init(void);
void lcd_write_area_data(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t* color_p, int32_t num);



#endif /* INC_LCD_H_ */
