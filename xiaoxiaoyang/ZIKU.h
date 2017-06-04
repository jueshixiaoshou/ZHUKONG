#pragma once
#ifndef _ZIKU_H
#define _ZIKU_H
#ifdef __cplusplus
extern "C" {
#endif
#include <stm32f1xx_hal.h>  //���Ŷ���
#include <LCD_DRIVE.h>

	/* ����ѡ�� */
	//#define USE_FONT_UPDATE                   //ʹ���ֿ���º���
#define USE_FLASH_CHAR                    //ʹ��FLASH�ֿ�

	/* �ֿ��ļ���ַ */
#define GUI_ASCII_FILE  "????/FONT/ASCII?��8X16??.DZK"
#define GUI_12CHAR_FILE "????/FONT/12??��????��16X16??.DZK"
#define GUI_16CHAR_FILE "????/FONT/16??��????��24X21??.DZK"

	/* �����ֿ��ַ */
#define GUI_FLASH_ASCII_ADDR     6112846  //ϵͳ/FONT/ASCII(8X16).DZK
#define GUI_FLASH_12CHAR_ADDR    6114304  //ϵͳ/FONT/12������(16X16).DZK
#define GUI_FLASH_16CHAR_ADDR    6880386  //ϵͳ/FONT/16������(24*21).DZK

	/* �����ֿ�ѡ���� */
#define GUI_UPDATE_ASCII         0x01     
#define GUI_UPDATE_12CHAR        0x02
#define GUI_UPDATE_16CHAR        0x04
#define GUI_UPDATE_ALL           0x07

	/* ����ȫ�ֱ��� */
	void GUI_Dot(uint16_t x, uint16_t y, uint16_t color);
	void GUI_BigPoint(uint16_t x, uint16_t y, uint16_t color);
	void GUI_Box(uint16_t xState, uint16_t yState, uint16_t xEnd, uint16_t yEnd, uint16_t color);
	void GUI_DrowSign(uint16_t x, uint16_t y, uint16_t color);

	void GUI_FontUpdate(uint8_t updateState);
	void GUI_Show12ASCII(uint16_t x, uint16_t y, uint8_t *p,
		uint16_t wordColor, uint16_t backColor);
	void GUI_Show12Char(uint16_t x, uint16_t y, uint8_t *ch,
		uint16_t wordColor, uint16_t backColor);
	void GUI_Show16Chinese(uint16_t x, uint16_t y, uint8_t *cn,
		uint16_t  wordColor, uint16_t backColor);


#ifdef __cplusplus
}
#endif


#endif 
