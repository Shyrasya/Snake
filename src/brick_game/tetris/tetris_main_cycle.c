#include "tetris_main_cycle.h"

void startTetrisEventLoop() {
  UserAction_t action = Start;
  TetrisFsmState_t fsmState = START;
  nodelay(stdscr, TRUE);
  srand(time(NULL));
  GameInfo_t statist = updateCurrentState(&fsmState);
  if (fsmState != EXIT_STATE) {
    int game = TetrisG;
    printStatist(statist, game);
    bool hold = false;
    while (action != Terminate) {
      hold = getInput(GET_CLICK, &action, hold);
      userInput(&fsmState, &statist, action, hold);
      statist = updateCurrentState(&fsmState);
      printStatist(statist, game);
      hold = false;
    }
  }
  exitPrepare(&statist);
  clearValues();
}