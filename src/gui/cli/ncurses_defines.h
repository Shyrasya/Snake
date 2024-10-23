#ifndef CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_NCURSES_DEFINES_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_NCURSES_DEFINES_H_

#include <locale.h>
#include <ncurses.h>

#define GAME_INIT()       \
  {                       \
    initscr();            \
    noecho();             \
    curs_set(0);          \
    cbreak();             \
    keypad(stdscr, TRUE); \
  }

#define ESC_TO_EXIT "Press \"ESC\" to exit"
#define P_TO_PAUSE "Press \"P\" to pause"
#define NO_HIGH_SCORE \
  "Can\'t create/read high_score file. Press any button to exit"
#define NO_HIGH_SCORE_WRITE "Can\'t write high_score file"
#define INTRO_MESSAGE_LEN 21

#define GET_CLICK getch()

#define MVPRINTW(y, x, ...) mvprintw(y, x, __VA_ARGS__);
#define MVADDCH(y, x, c) mvaddch(y, x, c);

#endif  // CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_NCURSES_DEFINES_H_
