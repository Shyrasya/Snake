#include "tetris_logic.h"

int statistInit(GameInfo_t *statist) {
  int code = true;
  statist->field = (int **)calloc(MAP_ROWS, sizeof(int *));
  if (statist->field == NULL) code = false;
  for (int r = 0; r < MAP_ROWS && code; r++) {
    statist->field[r] = (int *)calloc(MAP_COLS, sizeof(int));
    if (statist->field[r] == NULL) code = false;
  }
  if (code) {
    statist->next = (int **)calloc(QUADR, sizeof(int *));
    if (statist->next == NULL) code = false;
    for (int r = 0; r < QUADR && code; r++) {
      statist->next[r] = (int *)calloc(QUADR, sizeof(int));
      if (statist->next[r] == NULL) code = false;
    }
  }
  if (code)
    if (!successInit(statist)) code = false;
  return code;
}

int successInit(GameInfo_t *statist) {
  int code = true;
  int high = SUCCESS;
  if (readHighScore(&high)) {
    statist->highScore = high;
    statist->score = 0;
    statist->level = 1;
    statist->speed = 1;
    statist->pause = 0;
    statist->showGameOverScreen = 0;
    statist->showStartScreen = 1;
    statist->showWinScreen = 0;
  } else
    code = false;
  return code;
}

int readHighScore(int *high) {
  int code = true;
  FILE *file = fopen("high_score_tetris.txt", "r");
  if (file) {
    if (fscanf(file, "%d", high) == 1)
      fclose(file);
    else {
      code = false;
      fclose(file);
    }
  } else {
    file = fopen("high_score_tetris.txt", "w");
    if (file) {
      fprintf(file, "0");
      fclose(file);
    } else
      code = false;
  }
  return code;
}

int nextGen(GameInfo_t *statist) {
  int nextFig = rand() % MAX_RAND;
  for (int r = 0; r < QUADR; r++) {
    for (int c = 0; c < QUADR; c++) {
      statist->next[r][c] = figures[nextFig][r][c];
    }
  }
  return nextFig;
}

void patternFill(GameInfo_t *statist, PlayerPos_t *figureInfo) {
  for (int r = 0; r < QUADR; r++) {
    for (int c = 0; c < QUADR; c++)
      figureInfo->cube[r][c] = statist->next[r][c];
  }
}

int cubeToField(GameInfo_t *statist, PlayerPos_t *figureInfo, HelpVar_t *help) {
  int code = SUCCESS;
  for (int r = 0; r < QUADR && code == SUCCESS; r++) {
    for (int c = 0; c < QUADR && code == SUCCESS; c++)
      code = checkCubeToField(statist, figureInfo, r, c, help);
  }
  return code;
}

int checkCubeToField(GameInfo_t *statist, PlayerPos_t *figureInfo, int r, int c,
                     HelpVar_t *help) {
  int code = SUCCESS;
  int cordy = r + figureInfo->y;
  int cordx = c + figureInfo->x;
  if (figureInfo->cube[r][c] == 1) {
    if ((cordy < MAP_ROWS) && (cordx >= MAP_START) && (cordx < MAP_COLS)) {
      if (statist->field[cordy][cordx] != 2)
        statist->field[cordy][cordx] = figureInfo->cube[r][c];
      else {
        code = ERROR;
        if (help->downClick) help->floor = 1;
      }
    } else
      code = ERROR;
  }
  return code;
}

void clearCubofield(GameInfo_t *statist, PlayerPos_t *figureInfo) {
  for (int r = 0; r < QUADR; r++) {
    for (int c = 0; c < QUADR; c++) {
      int cordy = r + figureInfo->y;
      int cordx = c + figureInfo->x;
      if (cordy < MAP_ROWS && cordx < MAP_COLS && cordx >= MAP_START) {
        if (statist->field[cordy][cordx] == 1) statist->field[cordy][cordx] = 0;
      }
    }
  }
}

void copyCubeToTemp(int (*tempCube)[QUADR], PlayerPos_t *figureInfo) {
  for (int r = 0; r < QUADR; r++) {
    for (int c = 0; c < QUADR; c++) {
      tempCube[r][c] = figureInfo->cube[r][c];
    }
  }
}

void copyTempToCube(PlayerPos_t *figureInfo, int (*tempCube)[QUADR]) {
  for (int r = 0; r < QUADR; r++) {
    for (int c = 0; c < QUADR; c++) {
      figureInfo->cube[r][c] = tempCube[r][c];
    }
  }
}

void matrixClockwise(PlayerPos_t *figureInfo) {
  int copy[TETR][TETR] = {0};
  for (int r = 1; r < TETR + 1; r++) {
    for (int c = 0; c < TETR; c++) {
      copy[r - 1][c] = figureInfo->cube[r][c];
    }
  }
  int temp[TETR][TETR] = {0};
  for (int r = 0; r < TETR; r++) {
    for (int c = 0; c < TETR; c++) {
      temp[r][c] = copy[TETR - c - 1][r];
    }
  }
  cleanCarryCube(figureInfo);
  for (int r = 0; r < TETR; r++) {
    for (int c = 0; c < TETR; c++) {
      figureInfo->cube[r + 1][c] = temp[r][c];
    }
  }
}

void lineClockwise(GameInfo_t *statist, PlayerPos_t *figureInfo,
                   HelpVar_t *help) {
  int lineFig = HORIZ_I_1;
  clearCubofield(statist, figureInfo);
  cleanCarryCube(figureInfo);
  if (help->turn % 4 == 1) {
    lineFig = VERTIC_I_2;
  } else if (help->turn % 4 == 3) {
    lineFig = VERTIC_I_4;
  }
  clockwiseFill(figureInfo, lineFig);
  if (help->turn % 4 == 2)
    figureInfo->x++;
  else if (help->turn % 4 == 3)
    figureInfo->y++;
  else if (help->turn % 4 == 0) {
    figureInfo->x--;
    figureInfo->y--;
  }
  help->turn++;
}

void cleanCarryCube(PlayerPos_t *figureInfo) {
  for (int r = 0; r < QUADR; r++) {
    for (int c = 0; c < QUADR; c++) {
      figureInfo->cube[r][c] = 0;
    }
  }
}

void clockwiseFill(PlayerPos_t *figureInfo, int lineFig) {
  for (int r = 0; r < QUADR; r++) {
    for (int c = 0; c < QUADR; c++) {
      figureInfo->cube[r][c] = figures[lineFig][r][c];
    }
  }
}

void errorRotate(GameInfo_t *statist, PlayerPos_t *figureInfo,
                 HelpVar_t *help) {
  clearCubofield(statist, figureInfo);
  if (figureInfo->curFigure == I) {
    help->turn--;
    if (help->turn % QUADR == 2)
      figureInfo->x--;
    else if (help->turn % QUADR == 3)
      figureInfo->y--;
    else if (help->turn % QUADR == 0) {
      figureInfo->x++;
      figureInfo->y++;
    }
  }
}

int checkAttach(GameInfo_t *statist, PlayerPos_t *figureInfo) {
  int code = true;
  for (int r = 0; r < QUADR; r++) {
    for (int c = 0; c < QUADR; c++) {
      int cordy = r + figureInfo->y;
      int cordx = c + figureInfo->x;
      if (cordy < MAP_ROWS) {
        if (statist->field[cordy][cordx] == 1 && (cordy) > QUADR) {
          statist->field[cordy][cordx] = 2;
        } else if (statist->field[cordy][cordx] == 1 && (cordy) <= QUADR)
          code = false;
      }
    }
  }
  return code;
}

void checkFullLines(GameInfo_t *statist, int *speedScore) {
  int rows = 0, r = MAP_ROWS - PADDING;
  for (; r > QUADR - PADDING; r--) {
    int flag = 0;
    for (int c = 0; !flag && c < MAP_COLS; c++) {
      if (statist->field[r][c] == 0) flag = 1;
    }
    if (!flag) {
      rows++;
      for (int rm = r; rm > QUADR - PADDING; rm--) {
        for (int cm = 0; cm < MAP_COLS; cm++) {
          statist->field[rm][cm] = statist->field[rm - 1][cm];
        }
      }
      r++;
    }
  }
  newScoreSet(statist, rows, speedScore);
  if (statist->score > statist->highScore) {
    statist->highScore = statist->score;
  }
}

void newScoreSet(GameInfo_t *statist, int rows, int *speedScore) {
  const int linesScore[5] = {0, 100, 300, 700, 1500};
  statist->score += linesScore[rows];
  *speedScore += linesScore[rows];
  if (*speedScore >= 600) {
    if (statist->level < 10) {
      statist->level++;
      statist->speed++;
      *speedScore = 0;
    }
  }
}

int gameoverUpdCurSt(GameInfo_t *statist) {
  int code = true;
  clearGameovrField(statist);
  if (!writeHighScore(statist)) code = false;
  statist->showGameOverScreen = 1;
  return code;
}

void clearGameovrField(GameInfo_t *statist) {
  for (int r = 0; r < MAP_ROWS; r++) {
    for (int c = 0; c < MAP_COLS; c++) {
      statist->field[r][c] = 0;
    }
  }
}

int writeHighScore(GameInfo_t *statist) {
  int code = true;
  FILE *file = fopen("high_score_tetris.txt", "w");
  if (file) {
    fprintf(file, "%d", statist->highScore);
    fclose(file);
  } else
    code = false;
  return code;
}

void exitPrepare(GameInfo_t *statist) {
  clearGameovrField(statist);
  writeHighScore(statist);

  statist->level = 1;
  statist->score = 0;
  statist->highScore = 0;
  statist->speed = 1;
  statist->pause = 0;
  statist->showStartScreen = 1;
  statist->showGameOverScreen = 0;
  statist->showWinScreen = 0;

  if (statist->field != NULL) {
    for (int i = 0; i < MAP_ROWS; i++) {
      free(statist->field[i]);
    }
    free(statist->field);
    statist->field = NULL;
  }
  if (statist->next != NULL) {
    for (int i = 0; i < QUADR; i++) {
      free(statist->next[i]);
    }
    free(statist->next);
    statist->next = NULL;
  }
}
