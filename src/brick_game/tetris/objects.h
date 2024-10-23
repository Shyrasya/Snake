#ifndef CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_TETRIS_OBJECTS_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_TETRIS_OBJECTS_H_

#include "../defines.h"

/**
 * @brief Структура, содержащая информацию о текущем состоянии игры
 * @param field Указатель на массив, содержащий информацию о заполненности
 * игрового поля: 0 - пусто, 1 - заполнен текущей игровой фигурой, 2 - заполнен
 * упавшей фигурой, 3 - голова змейки, 4 - яблоко
 * @param next Указатель на массив, содержащий информацию о следующей игровой
 * фигуре (значеня 0 - пусто и 1 - заполнен)
 * @param score Текущий счет игры
 * @param high_score Максимально набранный счет за всё время игры
 * @param level Текущий игровой уровень
 * @param speed Текущая игровая скорость
 * @param pause Информация о состоянии режима паузы
 * @param showStartScreen Включено ли отображение стартового экрана
 * @param showGameOverScreen Включено ли отображение экрана проигрыша-конца игры
 * @param showWinScreen Включено ли отображение экран выигрыша игры
 */
typedef struct {
  int **field;
  int **next;
  int score;
  int highScore;
  int level;
  int speed;
  int pause;
  int showStartScreen;
  int showGameOverScreen;
  int showWinScreen;
} GameInfo_t;

/**
 * @brief Структура, содержащая информацию о текущем состоянии игровой фигуры
 * @param y Вертикальная координата левого верхнего угла квадратной 4*4
 * переноски с шаблоном фигуры относительно поля
 * @param x Горизонтальная координата левого верхнего угла квадратной 4*4
 * переноски с шаблоном фигуры относительно поля
 * @param cur_figure Номер текущей фигуры из списка возможных шаблонов
 * @param cube Указатель на массив, содержащий информацию о текущем состоянии
 * шаблона с текущей фигурой
 * @param next_figure Номер следующей фигуры из списка возможных шаблонов
 */
typedef struct {
  int y;
  int x;
  int curFigure;
  int cube[QUADR][QUADR];
  int nextFigure;
} PlayerPos_t;

/**
 * @brief Вспомогательная структура для учета положения фигуры при событиях
 * @param turn Счетчик поворота фигуры для учета выбора шаблона положения фигуры
 * I при повороте по часовой стрелке
 * @param floor Флаг, указывающий достижения фигурой "пола" поля или другой
 * лежачей фигуры
 * @param down_click Флаг, содержащий информацию о нажатии клавиши "вниз"
 */
typedef struct {
  int turn;
  int floor;
  int downClick;
} HelpVar_t;

#endif  // CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_TETRIS_OBJECTS_H_