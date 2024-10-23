#ifndef CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_TETRIS_TETRIS_FSM_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_TETRIS_TETRIS_FSM_H_

#include "../../gui/input.h"
#include "../defines.h"
#include "objects.h"
#include "tetris_logic.h"

/**
 * @brief Функция с обработкой текущего состояния конечного автомата и игрового
 * процесса и передачи структуры состояния игрового поля для дальнейшей
 * отрисовки
 * @param fsmState Текущее состояние конечного автомата
 */
GameInfo_t updateCurrentState(TetrisFsmState_t *fsmState);

/**
 * @brief Функция определяющая дальнейшее развитие игры в зависимости от нажатой
 * клавиши и состояния конечного автомата
 * @param fsmState Текущее состояние конечного автомата
 * @param statist Структура с текущим состоянием поля, шаблоном следующей
 * фигуры, очков и т.п.
 * @param action Нажатая клавиша виртуального тетриса
 * @param hold Была ли нажата какая-либо клавиша
 */
void userInput(TetrisFsmState_t *fsmState, GameInfo_t *statist,
               UserAction_t action, bool hold);

/**
 * @brief Функция, проверяющая нажатие клавиши выхода или кнопки старта и
 * меняющая состояние конечного автомата
 * @param fsmState Текущее состояние конечного автомата
 * @param statist Структура с текущим состоянием поля, шаблоном следующей
 * фигуры, очков и т.п.
 * @param figureInfo Структура с состоянием игровой фигуры
 * @param action Нажатая клавиша виртуального тетриса
 * @param hold Была ли нажата какая-либо клавиша
 */
void checkSwitch(GameInfo_t *statist, TetrisFsmState_t *fsmState,
                 PlayerPos_t *figureInfo, UserAction_t action, bool hold);

/**
 * @brief Функция для исполнения действий при состоянии "спавн новой фигуры"
 * конечного автомата тетриса
 * @param statist Структура с текущим состоянием поля, шаблоном следующей
 * фигуры, очков и т.п.
 * @param figureInfo Структура с состоянием игровой фигуры
 * @param help Вспомогательная структура для учета положения фигуры при событиях
 */
void fsmSpawn(GameInfo_t *statist, PlayerPos_t *figureInfo, HelpVar_t *help);

/**
 * @brief Функция для исполнения действий при состоянии "движение фигуры"
 * конечного автомата
 * @param action Нажатая клавиша виртуального тетриса
 * @param hold Была ли нажата какая-либо клавиша
 * @param fsmState Текущее состояние конечного автомата
 * @param figureInfo Структура с состоянием игровой фигуры
 * @param statist Структура с текущим состоянием поля, шаблоном следующей
 * фигуры, очков и т.п.
 * @param help Вспомогательная структура для учета положения фигуры при событиях
 */
void fsmMoving(UserAction_t action, bool hold, TetrisFsmState_t *fsmState,
               PlayerPos_t *figureInfo, GameInfo_t *statist, HelpVar_t *help);

/**
 * @brief Функция для исполнения действий при движении фигуры влево/вправо
 * @param action Нажатая клавиша виртуального тетриса
 * @param figureInfo Структура с состоянием игровой фигуры
 * @param statist Структура с текущим состоянием поля, шаблоном следующей
 * фигуры, очков и т.п.
 * @param help Вспомогательная структура для учета положения фигуры при событиях
 */
void fsmLeftRight(UserAction_t action, PlayerPos_t *figureInfo,
                  GameInfo_t *statist, HelpVar_t *help);

/**
 * @brief Функция для исполнения действий при движении фигуры вниз
 * @param fsmState Текущее состояние конечного автомата
 * @param figureInfo Структура с состоянием игровой фигуры
 * @param statist Структура с текущим состоянием поля, шаблоном следующей
 * фигуры, очков и т.п.
 * @param help Вспомогательная структура для учета положения фигуры при событиях
 */
void fsmDown(TetrisFsmState_t *fsmState, PlayerPos_t *figureInfo,
             GameInfo_t *statist, HelpVar_t *help);

/**
 * @brief Функция для исполнения действий при повороте фигуры
 * @param figureInfo Структура с состоянием игровой фигуры
 * @param statist Структура с текущим состоянием поля, шаблоном следующей
 * фигуры, очков и т.п.
 * @param help Вспомогательная структура для учета положения фигуры при событиях
 */
void fsmRotate(PlayerPos_t *figureInfo, GameInfo_t *statist, HelpVar_t *help);

/**
 * @brief Функция для исполнения действий при состоянии "сдвиг" конечного
 * автомата
 * @param fsmState Текущее состояние конечного автомата
 * @param figureInfo Структура с состоянием игровой фигуры
 * @param statist Структура с текущим состоянием поля, шаблоном следующей
 * фигуры, очков и т.п.
 * @param help Вспомогательная структура для учета положения фигуры при событиях
 */
void fsmShifting(TetrisFsmState_t *fsmState, PlayerPos_t *figureInfo,
                 GameInfo_t *statist, HelpVar_t *help);

/**
 * @brief Функция для исполнения действий при состоянии "прикрепление" конечного
 * автомата
 * @param fsmState Текущее состояние конечного автомата
 * @param figureInfo Структура с состоянием игровой фигуры
 * @param statist Структура с текущим состоянием поля, шаблоном следующей
 * фигуры, очков и т.п.
 */
void fsmAttaching(TetrisFsmState_t *fsmState, PlayerPos_t *figureInfo,
                  GameInfo_t *statist);

#endif  // CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_TETRIS_TETRIS_FSM_H_