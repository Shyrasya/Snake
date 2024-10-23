#include "../../brick_game/tetris/tetris_desktop_translate.h"

static GameInfo_t statist;

s21::GameInfo_t transBack(TetrisFsmState_t *fsmState) {
  getCInfo(fsmState);
  return translateInfoBack();
}

void getCInfo(TetrisFsmState_t *fsmState) {
  statist = updateCurrentState(fsmState);
}

s21::GameInfo_t translateInfoBack() {
  s21::GameInfo_t gameInfo;
  for (int r = 0; r < MAP_ROWS; r++) {
    for (int c = 0; c < MAP_COLS; c++) {
      gameInfo.field[r][c] = statist.field[r][c];
    }
  }
  for (int r = 0; r < QUADR; r++) {
    for (int c = 0; c < QUADR; c++) {
      gameInfo.next[r][c] = statist.next[r][c];
    }
  }
  gameInfo.score = statist.score;
  gameInfo.highScore = statist.highScore;
  gameInfo.level = statist.level;
  gameInfo.speed = statist.speed;
  gameInfo.pause = statist.pause;
  gameInfo.showStartScreen = statist.showStartScreen;
  gameInfo.showGameOverScreen = statist.showGameOverScreen;
  gameInfo.showWinScreen = statist.showWinScreen;
  return gameInfo;
}

s21::GameInfo_t translateInfoFront(TetrisFsmState_t *fsmState,
                                   UserAction_t *action, bool *hold) {
  userInput(fsmState, &statist, *action, *hold);
  return transBack(fsmState);
}

void statClose() { exitPrepare(&statist); }
