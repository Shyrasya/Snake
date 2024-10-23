#ifndef CPP3_BRICKGAME_V2_0_1_SRC_GUI_CLI_CLI_MAIN_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_GUI_CLI_CLI_MAIN_H_

#include "../input.h"
#include "console_view.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "../../brick_game/tetris/tetris_main_cycle.h"

#ifdef __cplusplus
}
#endif

/**
 * @brief Главный цикл стартового меню выбора игры
 */
int mainMenu();

/**
 * @brief Вывод в консоль бортиков поля и дополнительной информации, названий
 * полей статистики, выхода
 */
void printBorders();

/**
 * @brief Печать прямоугольных бортиков
 * @param topY Верхняя координата прямоугольника по y
 * @param bottomY Нижняя координата прямоугольника по y
 * @param leftX Левая координата прямоугольника по x
 * @param rightX Правая координата прямоугольника по x
 */
void printRectangle(int topY, int bottomY, int leftX, int rightX);

/**
 * @brief Вывод в консоль названий игр: змейка и тетрис
 */
void printGameNames();

/**
 * @brief Очистка в консоли названий игр: змейка и тетрис
 */
void clearChoosing();

/**
 * @brief Отрисовка значка * слева от выбранной игры в консоли
 * @param game Выбранная ранее игра (змейка или тетрис)
 */
void printChoosing(int game);

#endif  // CPP3_BRICKGAME_V2_0_1_SRC_GUI_CLI_CLI_MAIN_H_