
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_Interface.h"
#include "LCD_Interface.h"
#include "KEYPAD_Interface.h"
#include "Game.h"
#include <avr/delay.h>
#include <avr/io.h>

void Game_Init(void)
{
    LCD_ClearDisplay();
    _delay_ms(2);
    LCD_VidSetPosition(0, 0);
    LCD_VidWriteString("paddle");
    LCD_VidSetPosition(1, 2);
    LCD_VidWriteString("1");
    LCD_VidSetPosition(0, 7);
    LCD_VidWriteString("Race");
    LCD_VidSetPosition(1, 8);
    LCD_VidWriteString("2");
    LCD_VidSetPosition(0, 12);
    LCD_VidWriteString("Sanke");
    LCD_VidSetPosition(1, 13);
    LCD_VidWriteString("3");
    _delay_ms(1000);

    do
    {
        ret = KPD_u8GetPressedKey();

    } while (KPD_NO_PRESSED_KEY == ret);
    _delay_ms(100);
    LCD_VidSendCommand(0b00000001);
}
u8 left_move(u8 row, u8 col)
{

    u8 i = 0;
    for (i = col;; i--)
    {
        LCD_spe_char(row, i, SNAK_CH1);
        _delay_ms(200);
        LCD_VidSendCommand(0b00000001);
        key_pressed = KPD_u8GetPressedKey();
        _delay_ms(100);

        if (key_pressed == '6' || key_pressed == '2' || key_pressed == '8')
        {

            break;
        }
        if (i <= 0)
        {
            i = 15;
        }
    }
    return i;
}

u8 right_move(u8 row, u8 col)
{

    u8 i = 0;
    for (i = col;; i++)
    {
        LCD_spe_char(row, i, SNAK_CH1);
        _delay_ms(200);
        LCD_VidSendCommand(0b00000001);
        key_pressed = KPD_u8GetPressedKey();
        _delay_ms(100);
        if (key_pressed == '4' || key_pressed == '2' || key_pressed == '8')
        {

            break;
        }
        if (i >= 15)
        {
            i = 0;
        }
    }
    return i;
}

u8 up_move(u8 row, u8 col)
{
    u8 i = 0;
    for (i = row;; i--)
    {
        LCD_spe_char(i, col, SNAK_CH2);
        _delay_ms(200);
        LCD_VidSendCommand(0b00000001);
        key_pressed = KPD_u8GetPressedKey();
        _delay_ms(100);

        if (key_pressed == '4' || key_pressed == '6' || key_pressed == '8')
        {

            break;
        }
        if (i <= 0)
        {
            i = 2;
        }
    }
    return i;
}

u8 down_move(u8 row, u8 col)
{
    u8 i = 0;
    for (i = row;; i--)
    {
        LCD_spe_char(i, col, SNAK_CH2);
        _delay_ms(200);
        LCD_VidSendCommand(0b00000001);
        key_pressed = KPD_u8GetPressedKey();
        _delay_ms(100);

        if (key_pressed == '4' || key_pressed == '6' || key_pressed == '2')
        {

            break;
        }
        if (i >= 1)
        {
            i = 0;
        }
    }
    return i;
}

void LCD_Clear_left_player(void)
{
    LCD_VidSetPosition(0, 0);
    LCD_VidWriteString(" "); // manually clear the display
                             // LCD_VidSendCommand(192);
    LCD_VidSetPosition(1, 0);
    LCD_VidWriteString(" ");
}

void LCD_Clear_right_player(void)
{
    LCD_VidSetPosition(0, 15);
    LCD_VidWriteString(" "); // manually clear the display
    LCD_VidSetPosition(1, 15);
    LCD_VidWriteString(" ");
}

u8 key_check_right_pl(u8 key)
{
    switch (key)
    {
    case '9':
        LCD_Clear_right_player();
        right_player_move_down();
        pre_move_right_pl = 0;
        break;
    case '3':
        LCD_Clear_right_player();
        right_player_move_up();
        pre_move_right_pl = 1;
        break;

    default:
        break;
    }
    return pre_move_right_pl;
}

u8 key_check_left_pl(u8 key)
{
    switch (key)
    {
    case '7':
        LCD_Clear_left_player();
        left_player_move_down();
        pre_move_left_pl = 0;
        break;
    case '1':
        LCD_Clear_left_player();
        left_player_move_up();
        pre_move_left_pl = 1;
        break;
    default:
        break;
    }
    return pre_move_left_pl;
}

u8 ball_right_move(u8 row, u8 col)
{
    u8 ret_row = 0;
    u8 ret_right_pl_pos = 0;
    for (; col <= 15; col++)
    {
        if (col < 15)
        {

            LCD_spe_char(row, col, BALL_CH);
            _delay_ms(80);
            LCD_ClearDisplay_game();
        }
        row = 1 - row;
        ret_row = row;
        key_pressed = KPD_u8GetPressedKey();
        _delay_ms(100);
        ret_right_pl_pos = key_check_right_pl(key_pressed);
    }

    if (row != ret_right_pl_pos)
    {
        row = 1 - row;
        LCD_spe_char(row, 15, BALL_CH);
        _delay_ms(2000);
        left_player_score++;
        Display_score();
    }

    return ret_row;
}

void Display_score(void)
{
    LCD_ClearDisplay_game();
    // right_player_score++;
    LCD_VidSendCommand(0b00000001);
    LCD_VidSetPosition(0, 0);
    LCD_VidWriteString("PL1: ");
    LCD_VidSetPosition(0, 5);
    LCD_VidWriteNumber(left_player_score);
    LCD_VidSetPosition(1, 0);
    LCD_VidWriteString("PL2: ");
    LCD_VidSetPosition(1, 5);
    LCD_VidWriteNumber(right_player_score);
    _delay_ms(4000);
    LCD_VidSendCommand(0b00000001);
}

u8 ball_left_move(u8 row, u8 col)
{
    u8 ret_row = 0;
    u8 ret_left_pl_pos = 0;
    for (; col >= 1; col--)
    {
        if (col > 0)
        {
            LCD_spe_char(row, col, BALL_CH);
            _delay_ms(80);
            LCD_ClearDisplay_game();
        }
        row = 1 - row;
        ret_row = row;
        key_pressed = KPD_u8GetPressedKey();
        _delay_ms(100);
        ret_left_pl_pos = key_check_left_pl(key_pressed);
    }

    if (row != ret_left_pl_pos)
    {
        row = 1 - row;
        LCD_spe_char(row, 0, BALL_CH);
        _delay_ms(2000);
        right_player_score++;
        Display_score();
    }

    return ret_row;
}

void right_player_move_up(void)
{

    LCD_spe_char(0, 15, RIGHT_PL);
    _delay_ms(200);
}

void right_player_move_down(void)
{

    LCD_spe_char(1, 15, RIGHT_PL);
    _delay_ms(200);
}

void left_player_move_up(void)
{

    LCD_spe_char(0, 0, LEFT_PL);
    _delay_ms(200);
}

void left_player_move_down(void)
{
    LCD_spe_char(1, 0, LEFT_PL);
    _delay_ms(200);
}

void LCD_ClearDisplay_game(void)
{
    // LCD_VidSendCommand(128);
    LCD_VidSetPosition(0, 1);
    LCD_VidWriteString("              "); // manually clear the display
                                          // LCD_VidSendCommand(192);
    LCD_VidSetPosition(1, 1);
    LCD_VidWriteString("              ");
    // LCD_VidSendCommand(128);
}
void LCD_clear_Row0(void)
{
    LCD_VidSetPosition(0, 0);
    LCD_VidWriteString("               ");
}

void LCD_clear_Row1(void)
{
    LCD_VidSetPosition(1, 0);
    LCD_VidWriteString("               ");
}

void race_game(void)
{
    u8 key_pre = 0;
    u8 pl1_pos = 0;
    u8 pl2_pos = 0;

    LCD_ClearDisplay();
    _delay_ms(2);
    LCD_VidSetPosition(0, 4);
    LCD_VidWriteString("Ready 3 ");

    _delay_ms(1000);
    LCD_ClearDisplay();
    _delay_ms(2);
    LCD_VidSetPosition(0, 4);
    LCD_VidWriteString("Steady 2 ");
    _delay_ms(1000);
    LCD_ClearDisplay();
    _delay_ms(2);
    LCD_VidSetPosition(0, 4);
    LCD_VidWriteString("  Go 1 ");
    _delay_ms(1000);
    LCD_ClearDisplay();
    _delay_ms(2);
    _delay_ms(1000);
    LCD_spe_char(0, 0, BOY_CH);
    LCD_spe_char(1, 0, BOY_CH);
    _delay_ms(1000);

    while (1)
    {

        do
        {
            key_pre = KPD_u8GetPressedKey();

        } while (KPD_NO_PRESSED_KEY == key_pre);

        if (key_pre == '1')
        {
            pl1_pos++;
            LCD_clear_Row0();
            LCD_spe_char(0, pl1_pos, BOY_CH);
        }
        else if (key_pre == '3')
        {
            pl2_pos++;
            LCD_clear_Row1();
            LCD_spe_char(1, pl2_pos, BOY_CH);
        }

        if (pl1_pos == 15 || pl2_pos == 15)
        {
            break;
        }
    }

    if (pl1_pos == 15)
    {
        LCD_ClearDisplay();
        _delay_ms(2);
        LCD_VidSetPosition(0, 3);
        LCD_VidWriteString("Number 1 is ");
        LCD_VidSetPosition(1, 5);
        LCD_VidWriteString("Winner ");
        _delay_ms(10000);
        LCD_ClearDisplay();
        _delay_ms(2);
    }
    else if (pl2_pos == 15)
    {
        LCD_ClearDisplay();
        _delay_ms(2);
        LCD_VidSetPosition(0, 3);
        LCD_VidWriteString("Number 2 is ");
        LCD_VidSetPosition(1, 5);
        LCD_VidWriteString("Winner ");
        _delay_ms(10000);
        LCD_ClearDisplay();
        _delay_ms(2);
    }
}