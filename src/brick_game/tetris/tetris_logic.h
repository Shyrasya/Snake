#ifndef CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_TETRIS_TETRIS_LOGIC_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_TETRIS_TETRIS_LOGIC_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../defines.h"
#include "objects.h"

/**
 * @brief Структура, содержащая всевозможные состояния конечного автомата
 * тетриса
 */
typedef enum {
  START = 0,
  SPAWN,
  MOVING,
  SHIFTING,
  ATTACHING,
  PAUSE,
  GAMEOVER,
  EXIT_STATE,
} TetrisFsmState_t;

/**
 * @brief Массив, содержащий шаблоны 4*4 всех возможных фигур в игре тетрис(0 -
 * пусто, 1 - заполнено)
 */
static const int figures[9][QUADR][QUADR] = {
    {{0, 0, 0, 0}, {1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}},  // J
    {{0, 0, 0, 0}, {0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}},  // L
    {{0, 0, 0, 0}, {0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}},  // T
    {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 1, 1, 0}, {1, 1, 0, 0}},  // S
    {{0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 0, 0}, {0, 1, 1, 0}},  // Z
    {{0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 0, 0}, {1, 1, 0, 0}},  // O
    {{0, 0, 0, 0}, {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}},  // I horiz 1
    {{0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}},  // I vert 2
    {{0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}}   // I vert 4
};

/**
 * @brief Структура, содержащая названия всех возможных фигур в игре
 */
typedef enum { J, L, T, S, Z, O, I, MAX_RAND } FigName_t;

/**
 * @brief Функция для начального выделения памяти под поле и следующую игровую
 * фигуру
 * @param statist Структура с текущим состоянием поля, шаблоном следующей
 * фигуры, очков и т.п.
 * @return Код выделения памяти (0 - успешно, 1 - нет)
 */
int statistInit(GameInfo_t *statist);

/**
 * @brief Функция для инициализации стартовой информации об игре (очки, уровень,
 * скорость, пауза)
 * @param statist Структура с текущим состоянием поля, шаблоном следующей
 * фигуры, очков и т.п.
 */
int successInit(GameInfo_t *statist);

/**
 * @brief Функция для чтения файла с максимально набранным счетом
 * @param high Переменная, куда запишется максимальный счет с файла
 * @return Код чтения файла со счетом-рекордом (0 - успешно, 1 - нет)
 */
int readHighScore(int *high);

/**
 * @brief Функция генерации новой фигуры
 * @param statist Структура с текущим состоянием поля, шаблоном следующей
 * фигуры, очков и т.п.
 * @return Номер новой сгенерированной фигуры из списка всех возможных фигур
 */
int nextGen(GameInfo_t *statist);

/**
 * @brief Функция для заполнения переноски шаблона 4*4 текущей фигуры следующей
 * фигурой
 * @param statist Структура с текущим состоянием поля, шаблоном следующей
 * фигуры, очков и т.п.
 * @param figureInfo Структура с состоянием игровой фигуры
 */
void patternFill(GameInfo_t *statist, PlayerPos_t *figureInfo);

/**
 * @brief Функция для переноса фигуры из переноски шаблона 4*4 в поле-массив
 * @param statist Структура с текущим состоянием поля, шаблоном следующей
 * фигуры, очков и т.п.
 * @param figureInfo Структура с состоянием игровой фигуры
 * @param help Вспомогательная структура для учета положения фигуры при событиях
 * @return Код переноса фигуры на поле (0 - успешно, 1 - нет)
 */
int cubeToField(GameInfo_t *statist, PlayerPos_t *figureInfo, HelpVar_t *help);

/**
 * @brief Вспомогательная функция cube_to_field для проверки поля перед
 * переносом
 * @param statist Структура с текущим состоянием поля, шаблоном следующей
 * фигуры, очков и т.п.
 * @param figureInfo Структура с состоянием игровой фигуры
 * @param r Текущий проверяемый ряд поля
 * @param c Текущий проверяемый столбец поля
 * @param help Вспомогательная структура для учета положения фигуры при событиях
 * @return Код проверки поля и дальнейшего переноса (0 - успешно, 1 - нет)
 */
int checkCubeToField(GameInfo_t *statist, PlayerPos_t *figureInfo, int r, int c,
                     HelpVar_t *help);

/**
 * @brief Функция проверки заполненности рядов после прикрепления фигуры
 * @param statist Структура с текущим состоянием поля, шаблоном следующей
 * фигуры, очков и т.п.
 * @param speedScore Переменная для хранения набранных очков на текущем уровне
 * для учета перехода на следующий уровень
 */
void checkFullLines(GameInfo_t *statist, int *speedScore);

/**
 * @brief Функция обновления счета и скорости в соответствии с количеством
 * заполненных строчек
 * @param statist Структура с текущим состоянием поля, шаблоном следующей
 * фигуры, очков и т.п.
 * @param rows Количество заполненных строчек из check_full_lines
 * @param speedScore Переменная для хранения набранных очков на текущем уровне
 * для учета перехода на следующий уровень
 */
void newScoreSet(GameInfo_t *statist, int rows, int *speedScore);

/**
 * @brief Функция очищения поля из 1 в 0
 * @param statist Структура с текущим состоянием поля, шаблоном следующей
 * фигуры, очков и т.п.
 * @param figureInfo Структура с состоянием игровой фигуры
 */
void clearCubofield(GameInfo_t *statist, PlayerPos_t *figureInfo);

/**
 * @brief Функция копирования переноски шаблона 4*4 во временный массив
 * @param tempCube Указатель на временный массив
 * @param figureInfo Структура с состоянием игровой фигуры
 */
void copyCubeToTemp(int (*tempCube)[QUADR], PlayerPos_t *figureInfo);

/**
 * @brief Функция копирования временного массива в переноску шаблон 4*4
 * @param figureInfo Структура с состоянием игровой фигуры
 * @param tempCube Указатель на временный массив
 */
void copyTempToCube(PlayerPos_t *figureInfo, int (*tempCube)[QUADR]);

/**
 * @brief Функция поворота по часовой стрелке переноски шаблона 4*4 (кроме
 * фигуры I)
 * @param figureInfo Структура с состоянием игровой фигуры
 */
void matrixClockwise(PlayerPos_t *figureInfo);

/**
 * @brief Функция поворота по часовой стрелке переноски шаблона 4*4 фигуры I
 * @param statist Структура с текущим состоянием поля, шаблоном следующей
 * фигуры, очков и т.п.
 * @param figureInfo Структура с состоянием игровой фигуры
 * @param help Вспомогательная структура для учета положения фигуры при событиях
 */
void lineClockwise(GameInfo_t *statist, PlayerPos_t *figureInfo,
                   HelpVar_t *help);

/**
 * @brief Функция очищения переноски шаблона 4*4 в 0
 * @param figureInfo Структура с состоянием игровой фигуры
 */
void cleanCarryCube(PlayerPos_t *figureInfo);

/**
 * @brief Функция переноса перевернутого шаблона-фигуры I в переноску шаблон 4*4
 * @param figureInfo Структура с состоянием игровой фигуры
 * @param lineFig Номер фигуры I (из 3х возможных: 6, 7, 8) в списке всех фигур
 */
void clockwiseFill(PlayerPos_t *figureInfo, int lineFig);

/**
 * @brief Функция возврата фигуры в прошлую координату и очистка поля от
 * переноски шаблона 4*4 при невозможном повороте
 * @param statist Структура с текущим состоянием поля, шаблоном следующей
 * фигуры, очков и т.п.
 * @param figureInfo Структура с состоянием игровой фигуры
 * @param help Вспомогательная структура для учета положения фигуры при событиях
 */
void errorRotate(GameInfo_t *statist, PlayerPos_t *figureInfo, HelpVar_t *help);

/**
 * @brief Функция проверки на возможность прикрепления фигуры и дальнейшего
 * продолжения игры
 * @param statist Структура с текущим состоянием поля, шаблоном следующей
 * фигуры, очков и т.п.
 * @param figureInfo Структура с состоянием игровой фигуры
 * @return Возможно ли продолжать дальше игру и генерировать следующую фигуру?
 * Нет помех? 0 - да, 1 - нет
 */
int checkAttach(GameInfo_t *statist, PlayerPos_t *figureInfo);

/**
 * @brief Вспомогательна функция updateCurrentState для обработки "GAME_OVER"
 * состояния конечного автомата
 * @param statist Структура с текущим состоянием поля, шаблоном следующей
 * фигуры, очков и т.п.
 */
int gameoverUpdCurSt(GameInfo_t *statist);

/**
 * @brief Функция финального очищения поля из 1 и 2 в 0
 * @param statist Структура с текущим состоянием поля, шаблоном следующей
 * фигуры, очков и т.п.
 */
void clearGameovrField(GameInfo_t *statist);

/**
 * @brief Функция для записи нового счета-рекорда в файл
 * @param statist Структура с текущим состоянием поля, шаблоном следующей
 * фигуры, очков и т.п.
 * @return Код перезаписи файла со счетом-рекордом (0 - успешно, 1 - нет)
 */
int writeHighScore(GameInfo_t *statist);

/**
 * @brief Функция для подготовки игровой статистики к выходу из игры тетрис в
 * главное меню
 * @param statist Структура с текущим состоянием поля, шаблоном следующей
 * фигуры, очков и т.п.
 */
void exitPrepare(GameInfo_t *statist);

#endif  // CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_TETRIS_TETRIS_LOGIC_H_