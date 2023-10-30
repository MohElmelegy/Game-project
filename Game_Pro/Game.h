
#ifndef GAME_H_
#define GAME_H_
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#define BOY_CH 8    /*Boy Char*/
#define BALL_CH 9   /*Ball Char*/
#define SNAK_CH1 10 /*snak  Char*/
#define SNAK_CH2 11 /*snak Char*/
#define LEFT_PL 12  /*Left player*/
#define RIGHT_PL 13 /*Right player*/
u8 key_pressed = 0;
u8 ret_pos_col = 0;
u8 ret_pos_row = 0;
u8 right_player_score = 0;
u8 left_player_score = 0;
u8 pre_move_right_pl = 0;
u8 pre_move_left_pl = 0;
u8 ret = 0;


/**************************  API Prototypes  *********************************/
u8 left_move(u8 row, u8 col);
u8 right_move(u8 row, u8 col);
u8 up_move(u8 row, u8 col);
u8 down_move(u8 row, u8 col);
void Game_Init(void);
void Game_sys(void);
u8 left_move(u8 row, u8 col);
u8 right_move(u8 row, u8 col);
u8 up_move(u8 row, u8 col);
u8 down_move(u8 row, u8 col);
u8 down_move(u8 row, u8 col);
void LCD_Clear_left_player(void);
void LCD_Clear_right_player(void);
u8 key_check_right_pl(u8 key);
u8 key_check_left_pl(u8 key);
u8 ball_right_move(u8 row, u8 col);
void Display_score(void);
u8 ball_left_move(u8 row, u8 col);
void right_player_move_up(void);
void right_player_move_down(void);
void left_player_move_up(void);
void left_player_move_down(void);
void LCD_ClearDisplay_game(void);
void LCD_clear_Row0(void);
void LCD_clear_Row1(void);
void race_game(void);
/************************************************************************/
#endif