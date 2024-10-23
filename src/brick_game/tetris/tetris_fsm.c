#define _POSIX_C_SOURCE 200809L

#include "tetris_fsm.h"

static struct timespec lastTime, curTime;

GameInfo_t updateCurrentState(TetrisFsmState_t *fsmState) {
  static GameInfo_t statist;
  static bool restartFlag = false;
  static int speedScore = 0;
  if (*fsmState == START) {
    if (!statistInit(&statist)) *fsmState = EXIT_STATE;
    speedScore = 0;
  } else if (*fsmState == SPAWN) {
    if (restartFlag) {
      statist.level = 1;
      statist.score = 0;
      statist.speed = 1;
    }
    checkFullLines(&statist, &speedScore);
  } else if (*fsmState == MOVING) {
    statist.showStartScreen = 0;
    statist.showGameOverScreen = 0;
    if (restartFlag) restartFlag = !restartFlag;
    statist.pause = 0;
  } else if (*fsmState == PAUSE) {
    statist.pause = 1;
  } else if (*fsmState == GAMEOVER) {
    if (!gameoverUpdCurSt(&statist)) *fsmState = EXIT_STATE;
    restartFlag = true;
    speedScore = 0;
  }
  return statist;
}

void userInput(TetrisFsmState_t *fsmState, GameInfo_t *statist,
               UserAction_t action, bool hold) {
  static HelpVar_t help;
  static PlayerPos_t figureInfo;
  static UserAction_t preaction;
  static bool preactionPress = false;
  switch (*fsmState) {
    case START:
      checkSwitch(statist, fsmState, &figureInfo, action, hold);
      break;
    case SPAWN:
      if (action && hold) {
        preaction = action;
        preactionPress = true;
      } else
        preactionPress = false;
      fsmSpawn(statist, &figureInfo, &help);
      *fsmState = MOVING;
      clock_gettime(CLOCK_MONOTONIC, &lastTime);
      break;
    case MOVING:
      if (preactionPress) {
        action = preaction;
        preactionPress = false;
      }
      fsmMoving(action, hold, fsmState, &figureInfo, statist, &help);
      break;
    case SHIFTING:
      if (action && hold) {
        preaction = action;
        preactionPress = true;
      }
      fsmShifting(fsmState, &figureInfo, statist, &help);
      break;
    case ATTACHING:
      if (action && hold) {
        preaction = action;
        preactionPress = true;
      }
      fsmAttaching(fsmState, &figureInfo, statist);
      break;
    case PAUSE:
      if (hold) {
        if (action == Terminate)
          *fsmState = EXIT_STATE;
        else if (action == Pause) {
          *fsmState = MOVING;
          clock_gettime(CLOCK_MONOTONIC, &lastTime);
        }
      }
      break;
    case GAMEOVER:
      checkSwitch(statist, fsmState, &figureInfo, action, hold);
      break;
    case EXIT_STATE:
      break;
  }
}

void checkSwitch(GameInfo_t *statist, TetrisFsmState_t *fsmState,
                 PlayerPos_t *figureInfo, UserAction_t action, bool hold) {
  if (action == Terminate && hold)
    *fsmState = EXIT_STATE;
  else if (action == Start && hold) {
    figureInfo->nextFigure = nextGen(statist);
    *fsmState = SPAWN;
  }
}

void fsmSpawn(GameInfo_t *statist, PlayerPos_t *figureInfo, HelpVar_t *help) {
  help->turn = 1;
  help->floor = 0;
  figureInfo->x = MAP_COLS / 2 - 2;
  figureInfo->y = 0;
  figureInfo->curFigure = figureInfo->nextFigure;
  patternFill(statist, figureInfo);
  figureInfo->nextFigure = nextGen(statist);
  cubeToField(statist, figureInfo, help);
}

void fsmMoving(UserAction_t action, bool hold, TetrisFsmState_t *fsmState,
               PlayerPos_t *figureInfo, GameInfo_t *statist, HelpVar_t *help) {
  clock_gettime(CLOCK_MONOTONIC, &curTime);
  long double elapsed = (curTime.tv_sec - lastTime.tv_sec) +
                        (curTime.tv_nsec - lastTime.tv_nsec) * CONV_NSEC;
  if (hold) {
    switch (action) {
      case Terminate:
        *fsmState = EXIT_STATE;
        break;
      case Pause:
        *fsmState = PAUSE;
        break;
      case Down:
        while (*fsmState == MOVING)
          fsmDown(fsmState, figureInfo, statist, help);
        break;
      case Left:
        if (figureInfo->x > MAP_START - 2 * PADDING) {
          fsmLeftRight(action, figureInfo, statist, help);
        }
        break;
      case Right:
        if (figureInfo->x < MAP_COLS - 2 * PADDING) {
          fsmLeftRight(action, figureInfo, statist, help);
        }
        break;
      case Action:
        fsmRotate(figureInfo, statist, help);
        break;
      default:
        break;
    }
  }
  double delay = SEC - SEC_DEC * statist->speed + SEC_DEC;
  if (elapsed >= delay) *fsmState = SHIFTING;
}

void fsmLeftRight(UserAction_t action, PlayerPos_t *figureInfo,
                  GameInfo_t *statist, HelpVar_t *help) {
  clearCubofield(statist, figureInfo);
  if (action == Right)
    figureInfo->x++;
  else if (action == Left)
    figureInfo->x--;
  if (cubeToField(statist, figureInfo, help) == ERROR) {
    clearCubofield(statist, figureInfo);
    if (action == Right)
      figureInfo->x--;
    else if (action == Left)
      figureInfo->x++;
  }
  cubeToField(statist, figureInfo, help);
}

void fsmDown(TetrisFsmState_t *fsmState, PlayerPos_t *figureInfo,
             GameInfo_t *statist, HelpVar_t *help) {
  if (figureInfo->y < MAP_ROWS - QUADR + PADDING) {
    help->downClick = 1;
    clearCubofield(statist, figureInfo);
    figureInfo->y++;
    if (figureInfo->y + QUADR - 1 > MAP_ROWS ||
        cubeToField(statist, figureInfo, help) == ERROR) {
      help->floor = 1;
      *fsmState = ATTACHING;
      clearCubofield(statist, figureInfo);
      figureInfo->y--;
    } else
      *fsmState = MOVING;
    cubeToField(statist, figureInfo, help);
    help->downClick = 0;
  } else
    *fsmState = ATTACHING;
}

void fsmRotate(PlayerPos_t *figureInfo, GameInfo_t *statist, HelpVar_t *help) {
  int copyCubomatrix[QUADR][QUADR] = {0};
  copyCubeToTemp(copyCubomatrix, figureInfo);
  clearCubofield(statist, figureInfo);
  switch (figureInfo->curFigure) {
    case J:
    case L:
    case T:
    case S:
    case Z:
      matrixClockwise(figureInfo);
      break;
    case I:
      lineClockwise(statist, figureInfo, help);
      break;
    case O:
      break;
  }

  if (cubeToField(statist, figureInfo, help) == ERROR) {
    errorRotate(statist, figureInfo, help);
    cleanCarryCube(figureInfo);
    copyTempToCube(figureInfo, copyCubomatrix);
  }
  cubeToField(statist, figureInfo, help);
}

void fsmShifting(TetrisFsmState_t *fsmState, PlayerPos_t *figureInfo,
                 GameInfo_t *statist, HelpVar_t *help) {
  fsmDown(fsmState, figureInfo, statist, help);
  if (*fsmState == MOVING) {
    clock_gettime(CLOCK_MONOTONIC, &lastTime);
  }
}

void fsmAttaching(TetrisFsmState_t *fsmState, PlayerPos_t *figureInfo,
                  GameInfo_t *statist) {
  if (!checkAttach(statist, figureInfo)) {
    *fsmState = GAMEOVER;
    figureInfo->nextFigure = nextGen(statist);
  } else
    *fsmState = SPAWN;
}
