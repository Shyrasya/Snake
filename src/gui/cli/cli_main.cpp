#include "cli_main.h"

int main() {
  GAME_INIT();
  setlocale(LC_ALL, "");
  int game = SnakeG;
  while (game != Exit) {
    game = mainMenu();
    if (game == SnakeG) {
      s21::SnakeModel snModel;
      s21::SnakeController snController(&snModel);
      s21::ConsoleView snView(&snController);
      snView.startSnakeEventLoop();
    } else if (game == TetrisG) {
      startTetrisEventLoop();
    }
  }
  endwin();
  return 0;
}

int mainMenu() {
  printBorders();
  printGameNames();
  bool hold = false;
  int game = SnakeG;
  bool code = true;
  UserAction_t action = Start;
  while (code) {
    clearChoosing();
    printChoosing(game);
    refresh();
    hold = getInput(GET_CLICK, &action, hold);
    if (action == Start && hold)
      code = false;
    else if (action == Down && hold) {
      if (game == GAMES_NUMB)
        game = SnakeG;
      else
        ++game;
    } else if (action == Up && hold) {
      if (game == SnakeG)
        game = GAMES_NUMB;
      else
        --game;
    } else if (action == Terminate) {
      code = false;
      game = Exit;
    }
  }
  return game;
}

void printBorders() {
  printRectangle(0, MAP_ROWS + PADDING - PLUG, 0, MAP_COLS + PADDING);
  printRectangle(0, MAP_ROWS + PADDING - PLUG, MAP_COLS + 2,
                 MAP_COLS + HUD_WIDTH + 3);
  MVPRINTW(1, MAP_COLS + 5, "HIGH");
  MVPRINTW(2, MAP_COLS + 5, "SCORE");
  MVPRINTW(5, MAP_COLS + 5, "LEVEL");
  MVPRINTW(10, MAP_COLS + 5, "NEXT");
  MVPRINTW(18, MAP_COLS + 5, "SCORE");
  MVPRINTW(MAP_ROWS + PADDING * 2 - PLUG, PADDING, ESC_TO_EXIT);
  MVPRINTW(MAP_ROWS + PADDING * 2 - PLUG + 1, PADDING, P_TO_PAUSE);
}

void printRectangle(int topY, int bottomY, int leftX, int rightX) {
  MVADDCH(topY, leftX, ACS_ULCORNER);
  int i = leftX + PADDING;
  for (; i < rightX; i++) MVADDCH(topY, i, ACS_HLINE);
  MVADDCH(topY, i, ACS_URCORNER);
  for (int j = topY + PADDING; j < bottomY; j++) {
    MVADDCH(j, leftX, ACS_VLINE);
    MVADDCH(j, rightX, ACS_VLINE);
  }
  MVADDCH(bottomY, leftX, ACS_LLCORNER);
  i = leftX + PADDING;
  for (; i < rightX; i++) MVADDCH(bottomY, i, ACS_HLINE);
  MVADDCH(bottomY, i, ACS_LRCORNER);
}

void printGameNames() {
  MVPRINTW((MAP_COLS / 2) + 4, (MAP_ROWS - INTRO_MESSAGE_LEN) / 2 + 3, "SNAKE");
  MVPRINTW((MAP_COLS / 2) + 6, (MAP_ROWS - INTRO_MESSAGE_LEN) / 2 + 3,
           "TETRIS");
}

void printChoosing(int game) {
  if (game == SnakeG) {
    MVPRINTW((MAP_COLS / 2) + 4, (MAP_ROWS - INTRO_MESSAGE_LEN) / 2 + 1, "*");
  } else if (game == TetrisG) {
    MVPRINTW((MAP_COLS / 2) + 6, (MAP_ROWS - INTRO_MESSAGE_LEN) / 2 + 1, "*");
  }
}

void clearChoosing() {
  MVPRINTW((MAP_COLS / 2) + 6, (MAP_ROWS - INTRO_MESSAGE_LEN) / 2 + 1, " ");
  MVPRINTW((MAP_COLS / 2) + 4, (MAP_ROWS - INTRO_MESSAGE_LEN) / 2 + 1, " ");
}
