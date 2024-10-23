#ifndef CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_DEFINES_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_DEFINES_H_

#define SnakeG 1
#define TetrisG 2
#define Exit 3

#define GAMES_NUMB 2
#define MAP_ROWS 24
#define MAP_COLS 10
#define MAP_START 0
#define QUADR 4
#define TETR 3
#define PADDING 1
#define PLUG 4

#define HORIZ_I_1 6
#define VERTIC_I_2 7
#define VERTIC_I_4 8

#define HUD_WIDTH 8
#define HUD_HEIGHT 20

#define LINE1_SCORE 100
#define LINE2_SCORE 300
#define LINE3_SCORE 700
#define LINE4_SCORE 1500

#define SEC 0.7
#define SEC_DEC 0.07
#define CONV_NSEC 1e-9

#define SUCCESS 0
#define ERROR 1

#define ESCAPE_BTN 27
#define ENTER_KEY 10
#define PAUSE_KEY 112
#define SPACE_KEY 32

#define borderThickness 8
#define X_START 8
#define HEIGHT 516
#define yHighScore (HEIGHT * 0.017)
#define yLevel (HEIGHT / 6)
#define yNext (HEIGHT / 3)
#define yScore (HEIGHT * 0.85)
#define yPause (HEIGHT * 0.77)
#define yNextField (HEIGHT * 0.4)
#define SELECTED_COLOR QColor("#00918b")
#define BACKGROUND_COLOR QColor("#d0e17e")
#define SNAKEBODY_COLOR QColor("#5ba700")
#define APPLE_COLOR QColor("#ff333d")
#define BLACK_COLOR QColor(Qt::black)
#define WHITE_COLOR QColor(Qt::white)
#define SELECTED_FONT QFont("Chalkboard", 25, QFont::Bold)
#define NORMAL_FONT QFont("Chalkboard", 20, QFont::Bold)
#define SMALL_FONT QFont("Chalkboard", 10, QFont::Bold)

#endif  // CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_DEFINES_H_
