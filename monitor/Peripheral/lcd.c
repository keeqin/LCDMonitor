/*
 * lcd.c
 *
 *  Created on: Jan 1, 2022
 *      Author: Administrator
 */
#include "lcd.h"

void lcd_write_cmd(uint8_t cmd)
{
	HAL_GPIO_WritePin(GPIOB, LCD_DATA_CMD_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit_DMA(&hspi3, &cmd, 1);
	HAL_GPIO_WritePin(GPIOB, LCD_DATA_CMD_Pin, GPIO_PIN_SET);
}
void lcd_write_one_btye_data(uint8_t data)
{
	HAL_SPI_Transmit_DMA(&hspi3, &data, 1);
}


void lcd_init(void)
{
	HAL_GPIO_WritePin(GPIOB, LCD_CS_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, LCD_RESET_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, LCD_PWR_Pin, GPIO_PIN_RESET);
	HAL_Delay(10);
	HAL_GPIO_WritePin(GPIOB, LCD_RESET_Pin, GPIO_PIN_SET);
	HAL_Delay(12);
	/* Sleep Out */
	lcd_write_cmd(0x11);
	/* wait for power stability */
	HAL_Delay(12);

	/* Memory Data Access Control */
	lcd_write_cmd(0x36);
	lcd_write_one_btye_data(0x00);

	/* RGB 5-6-5-bit  */
	lcd_write_cmd(0x3A);
	lcd_write_one_btye_data(0x65);

	/* Porch Setting */
	lcd_write_cmd(0xB2);
	lcd_write_one_btye_data(0x0C);
	lcd_write_one_btye_data(0x0C);
	lcd_write_one_btye_data(0x00);
	lcd_write_one_btye_data(0x33);
	lcd_write_one_btye_data(0x33);

	/*  Gate Control */
	lcd_write_cmd(0xB7);
	lcd_write_one_btye_data(0x72);

	/* VCOM Setting */
	lcd_write_cmd(0xBB);
	lcd_write_one_btye_data(0x3D);   //Vcom=1.625V

	/* LCM Control */
	lcd_write_cmd(0xC0);
	lcd_write_one_btye_data(0x2C);

	/* VDV and VRH Command Enable */
	lcd_write_cmd(0xC2);
	lcd_write_one_btye_data(0x01);

	/* VRH Set */
	lcd_write_cmd(0xC3);
	lcd_write_one_btye_data(0x19);

	/* VDV Set */
	lcd_write_cmd(0xC4);
	lcd_write_one_btye_data(0x20);

	/* Frame Rate Control in Normal Mode */
	lcd_write_cmd(0xC6);
	lcd_write_one_btye_data(0x0F);	//60MHZ

	/* Power Control 1 */
	lcd_write_cmd(0xD0);
	lcd_write_one_btye_data(0xA4);
	lcd_write_one_btye_data(0xA1);

	/* Positive Voltage Gamma Control */
	lcd_write_cmd(0xE0);
	lcd_write_one_btye_data(0xD0);
	lcd_write_one_btye_data(0x04);
	lcd_write_one_btye_data(0x0D);
	lcd_write_one_btye_data(0x11);
	lcd_write_one_btye_data(0x13);
	lcd_write_one_btye_data(0x2B);
	lcd_write_one_btye_data(0x3F);
	lcd_write_one_btye_data(0x54);
	lcd_write_one_btye_data(0x4C);
	lcd_write_one_btye_data(0x18);
	lcd_write_one_btye_data(0x0D);
	lcd_write_one_btye_data(0x0B);
	lcd_write_one_btye_data(0x1F);
	lcd_write_one_btye_data(0x23);

	/* Negative Voltage Gamma Control */
	lcd_write_cmd(0xE1);
	lcd_write_one_btye_data(0xD0);
	lcd_write_one_btye_data(0x04);
	lcd_write_one_btye_data(0x0C);
	lcd_write_one_btye_data(0x11);
	lcd_write_one_btye_data(0x13);
	lcd_write_one_btye_data(0x2C);
	lcd_write_one_btye_data(0x3F);
	lcd_write_one_btye_data(0x44);
	lcd_write_one_btye_data(0x51);
	lcd_write_one_btye_data(0x2F);
	lcd_write_one_btye_data(0x1F);
	lcd_write_one_btye_data(0x1F);
	lcd_write_one_btye_data(0x20);
	lcd_write_one_btye_data(0x23);

	/* Display Inversion On */
	lcd_write_cmd(0x21);

	lcd_write_cmd(0x29);

}


void lcd_set_coordinate_area(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
//	uint8_t buf[11];
//	buf[0] = 0x2a;
//	buf[1] = (uint8_t)(x1>>8);
//	buf[2] = (uint8_t)x1;
//	buf[3] = (uint8_t)(x2>>8);
//	buf[4] = (uint8_t)x2;
//	buf[5] = 0x2b;
//	buf[6] = (uint8_t)(y1>>8);
//	buf[7] = (uint8_t)y1;
//	buf[8] = (uint8_t)(y2>>8);
//	buf[9] = (uint8_t)y2;
//	buf[10] = 0x2c;
//	HAL_GPIO_WritePin(GPIOB, LCD_DATA_CMD_Pin, GPIO_PIN_RESET);
//	HAL_SPI_Transmit(&hspi3, buf, 11,10);
//	HAL_GPIO_WritePin(GPIOB, LCD_DATA_CMD_Pin, GPIO_PIN_SET);


	lcd_write_cmd(0x2a);
	lcd_write_one_btye_data(x1>>8);
	lcd_write_one_btye_data(x1);
	lcd_write_one_btye_data(x2>>8);
	lcd_write_one_btye_data(x2);

	lcd_write_cmd(0x2b);
	lcd_write_one_btye_data(y1>>8);
	lcd_write_one_btye_data(y1);
	lcd_write_one_btye_data(y2>>8);
	lcd_write_one_btye_data(y2);

	lcd_write_cmd(0x2C);
}

void lcd_write_area_data(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t* color_p, int32_t num)
{
	lcd_set_coordinate_area(x1, y1, x2, y2);
	HAL_SPI_Transmit_DMA(&hspi3, (uint8_t*)color_p, num*2);
	LCD_PWR_ON;
}



