/*
 * Game_Pro.c
 *
 * Created: 10/26/2023
 *  Author: Mohamed Sami
 */
#define F_CPU 8000000
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_Interface.h"
#include "LCD_Interface.h"
#include "KEYPAD_Interface.h"
#include "Game.h"
#include <avr/delay.h>
#include <avr/io.h>


int main(void)
{
    u8 first_time_flag = 0;
    right_player_score = 0;
    left_player_score = 0;
    LCD_VidInit();
    KPD_VidInit();
    Game_Init();
    while (1)
    {
        Game_sys();
    }
}