#ifndef CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_TETRIS_TETRIS_DESKTOP_TRANSLATE_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_TETRIS_TETRIS_DESKTOP_TRANSLATE_H_

#include "../../gui/input.h"
#include "../snake/snake_model.h"

extern "C" {
#include "../tetris/objects.h"
#include "../tetris/tetris_fsm.h"
}

/**
 * @brief Функция для передачи состояния автомата в тетрисе из десктопа в модель
 * для получения информации об игровом процессе с целью использования для
 * дальнейшей прорисовки в интерфейсе
 * @param fsmState Текущее состояние конечного игрового автомата
 */
s21::GameInfo_t transBack(TetrisFsmState_t *fsmState);

/**
 * @brief Получение информации для прорисовки Тетриса в десктопном интерфейсе в
 * виде структуры GameInfo_t (C)
 * @param fsmState Текущее состояние конечного игрового автомата
 */
void getCInfo(TetrisFsmState_t *fsmState);

/**
 * @brief Перевод полученной информации об игровом процессе из GameInfo_t (C) в
 * s21::GameInfo_t (C++)
 */
s21::GameInfo_t translateInfoBack();

/**
 * @brief Обработка пользовательского нажатия в игре тетрис и совершение
 * логических операций в соответствии с состоянием автомата над игровой
 * статистикой с дальнейшим переводом GameInfo_t (C) в s21::GameInfo_t (C++)
 * @param fsmState Текущее состояние конечного игрового автомата
 * @param action Нажатая клавиша/кнопка виртуального тетриса
 * @param hold Была ли нажата какая-либо клавиша/кнопка
 */
s21::GameInfo_t translateInfoFront(TetrisFsmState_t *fsmState,
                                   UserAction_t *action, bool *hold);

/**
 * @brief Подготовка игровой структуры GameInfo_t к выходу из игры десктопного
 * тетриса
 */
void statClose();

#endif  // CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_TETRIS_TETRIS_DESKTOP_TRANSLATE_H_
