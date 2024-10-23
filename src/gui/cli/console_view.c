#include "console_view.h"

bool getInput(int input, UserAction_t *action, bool hold) {
  if (input == ENTER_KEY) {
    *action = Start;
    hold = true;
  } else if (input == KEY_UP) {
    *action = Up;
    hold = true;
  } else if (input == KEY_DOWN) {
    *action = Down;
    hold = true;
  } else if (input == KEY_LEFT) {
    *action = Left;
    hold = true;
  } else if (input == KEY_RIGHT) {
    *action = Right;
    hold = true;
  } else if (input == SPACE_KEY) {
    *action = Action;
    hold = true;
  } else if (input == PAUSE_KEY) {
    *action = Pause;
    hold = true;
  } else if (input == ESCAPE_BTN) {
    *action = Terminate;
    hold = true;
  } else {
    hold = false;
  }
  return hold;
}

#ifdef __cplusplus
using namespace s21;
#endif

void CV printSnakeStart() {
  MVPRINTW((MAP_COLS / 2) + 2, (MAP_ROWS - INTRO_MESSAGE_LEN) / 2 + 3, "SNAKE");
  printStart();
}

void CV printTetrisStart() {
  MVPRINTW((MAP_COLS / 2) + 2, (MAP_ROWS - INTRO_MESSAGE_LEN) / 2 + 3,
           "TETRIS");
  printStart();
}

void CV printStart() {
  MVPRINTW((MAP_COLS / 2) + 4, (MAP_ROWS - INTRO_MESSAGE_LEN) / 2 + 3, "Press");
  MVPRINTW((MAP_COLS / 2) + 5, (MAP_ROWS - INTRO_MESSAGE_LEN) / 2 + 2,
           "\"ENTER\"");
  MVPRINTW((MAP_COLS / 2) + 6, (MAP_ROWS - INTRO_MESSAGE_LEN) / 2 + 5, "to");
  MVPRINTW((MAP_COLS / 2) + 7, (MAP_ROWS - INTRO_MESSAGE_LEN) / 2 + 3, "START");
}

void CV clearField() {
  for (int r = 0; r < MAP_ROWS - QUADR; r++) {
    for (int c = 0; c < MAP_COLS; c++) MVADDCH(r + PADDING, c + PADDING, ' ');
  }
}

void CV clearScoreLevel() {
  MVPRINTW(3, MAP_COLS + 5, "      ");
  MVPRINTW(6, MAP_COLS + 7, "  ");
  MVPRINTW(19, MAP_COLS + 5, "      ");
}

void CV clearNext() {
  for (int r = 1; r < QUADR; r++) {
    for (int c = 0; c < QUADR; c++) MVADDCH(10 + r, MAP_COLS + 5 + c, ' ');
  }
}

void CV clearPause() { MVPRINTW(8, MAP_COLS + 5, "     "); }

void CV clearValues() {
  clearNext();
  clearScoreLevel();
  clearField();
  clearPause();
}

void CV printPause(GameInfo_t statist) {
  if (statist.pause == 0) {
    MVPRINTW(8, MAP_COLS + 5, "     ");
  } else if (statist.pause == 1)
    MVPRINTW(8, MAP_COLS + 5, "PAUSE");
}

void CV printHighScore(GameInfo_t statist) {
  MVPRINTW(3, MAP_COLS + 5, "%d", statist.highScore);
}

void CV printField(GameInfo_t statist) {
  for (int r = 4; r < MAP_ROWS; r++) {
    for (int c = 0; c < MAP_COLS; c++) {
      if (statist.field[r][c] == 0) {
        MVADDCH(r + PADDING - PLUG, c + PADDING, ' ');
      } else if ((statist.field[r][c] == 1 || statist.field[r][c] == 2)) {
        MVADDCH(r + PADDING - PLUG, c + PADDING, 'O');
      } else if ((statist.field[r][c] == 3)) {
        MVADDCH(r + PADDING - PLUG, c + PADDING, 'U');
      } else if ((statist.field[r][c] == 4))
        MVADDCH(r + PADDING - PLUG, c + PADDING, '@');
    }
  }
  clearScoreLevel();
  MVPRINTW(3, MAP_COLS + 5, "%d", statist.highScore);
  MVPRINTW(6, MAP_COLS + 7, "%d", statist.level);
  MVPRINTW(19, MAP_COLS + 5, "%d", statist.score);
}

void CV printNext(GameInfo_t statist) {
  if (
#ifdef __cplusplus
      statist.next != nullptr
#else
      statist.next != NULL
#endif
  ) {
    for (int r = 1; r < QUADR; r++) {
      for (int c = 0; c < QUADR; c++) {
        if (statist.next[r][c] == 1) {
          MVADDCH(10 + r, MAP_COLS + 5 + c, '0');
        } else if (statist.next[r][c] == 0)
          MVADDCH(10 + r, MAP_COLS + 5 + c, ' ');
      }
    }
  }
}

void CV printGameOver() {
  MVPRINTW(2, 5, "GAME");
  MVPRINTW(3, 5, "OVER");
  MVPRINTW(5, 5, "o_O");
}

void CV printWinScreen() {
  MVPRINTW(2, 5, "YOU");
  MVPRINTW(3, 5, "WIN");
  MVPRINTW(5, 5, "^_^");
}

void CV printStatist(GameInfo_t statist, int game) {
  if (statist.showStartScreen) {
    clearField();
    printHighScore(statist);
    if (game == SnakeG)
      printSnakeStart();
    else if (game == TetrisG)
      printTetrisStart();
  } else if (statist.showGameOverScreen) {
    clearField();
    printGameOver();
    printStart();
  } else if (statist.showWinScreen) {
    clearField();
    printWinScreen();
    printStart();
  } else {
    printNext(statist);
    printPause(statist);
    printField(statist);
  }
  refresh();
}

#ifdef __cplusplus

void s21::ConsoleView::startSnakeEventLoop() {
  UserAction_t action = Start;
  bool hold = false;
  int game = SnakeG;
  nodelay(stdscr, TRUE);
  printStatist(controller_->updateCurrentState(), game);
  while (action != Terminate) {
    hold = getInput(GET_CLICK, &action, hold);
    controller_->userInput(action, hold);
    printStatist(controller_->updateCurrentState(), game);
  }
  clearValues();
}

#endif  //__cplusplus
