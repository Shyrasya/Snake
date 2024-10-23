#ifndef CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_SNAKE_SNAKE_CONTROLLER_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_SNAKE_SNAKE_CONTROLLER_H_

#include <chrono>

#include "../../gui/input.h"
#include "snake_model.h"

namespace s21 {

class SnakeModel;

/**
 * @brief Класс контроллера Змейки, построенный на основе базового контроллера
 */
class SnakeController {
  using Clock = std::chrono::steady_clock;
  using TimePoint = std::chrono::time_point<Clock>;

 private:
  /**
   * @brief Указатель на класс модели Змейки
   */
  SnakeModel *model_;

 public:
  /**
   * @brief Базовый конструктор контроллера Змейки
   * @param model Указатель на модель с логикой игры
   */
  explicit SnakeController(SnakeModel *model) : model_(model) {
    preInputPress = false;
  }

  /**
   * @brief Флаг - была ли нажата клавиша вне fsm input (false - нет, true - да)
   */
  bool preInputPress;

  /**
   * @brief Главный метод контроллера змейки - передача в модель нажатой клавиши
   * и обработка состояния конечного автомата
   * @param action Нажатая клавиша виртуальной змейки
   * @param hold Была ли нажата какая-либо клавиша
   */
  void userInput(UserAction_t action, bool hold);

  /**
   * @brief Метод контроллера для проверки состояния выхода и старта игры по
   * нажатию на клавишу
   * @param action Нажатая клавиша виртуальной змейки
   * @param hold Была ли нажата какая-либо клавиша
   */
  void checkSwitch(UserAction_t action, bool hold);

  /**
   * @brief Метод перевода нажатой клавиши в направление движения змейки
   * @param action Нажатая клавиша виртуальной змейки
   */
  SnakeDirection exchange(UserAction_t action);

  /**
   * @brief Проверка на нажатие клавиши вне состояния fsm input
   * @param hold Была ли нажата какая-либо клавиша
   * @param state Текущее состояние конечного игрового автомата
   */
  void checkPreInput(bool hold, SnakeFsmState_t state);

  /**
   * @brief Метод контроллера для обработки состояния Spawn
   * @param shiftAction Направление движения виртуальной змейки
   * @param lastTime Временной указатель для засечения начала таймера, в течении
   * которого фигура получает возможный сигнал нажатия клавиши
   */
  void controlSpawn(SnakeDirection &shiftAction, TimePoint &lastTime);

  /**
   * @brief Метод контроллера для обработки состояния Input
   * @param shiftAction Направление движения виртуальной змейки
   * @param action Нажатая клавиша виртуальной змейки
   */
  void controlInput(SnakeDirection &shiftAction, UserAction_t action);

  /**
   * @brief Метод контроллера для обработки состояния Shifting
   * @param shiftAction Направление движения виртуальной змейки
   * @param lastTime Временной указатель для засечения начала таймера, в течении
   * которого фигура получает возможный сигнал нажатия клавиши
   */
  void controlShift(SnakeDirection &shiftAction, TimePoint &lastTime);

  /**
   * @brief Метод контроллера для обработки состояния Add
   */
  void controlAdd();

  /**
   * @brief Метод контроллера для обработки состояния Pause
   * @param action Нажатая клавиша виртуальной змейки
   * @param lastTime Временной указатель для засечения начала таймера, в течении
   * которого фигура получает возможный сигнал нажатия клавиши
   */
  void controlPause(UserAction_t action, TimePoint &lastTime);

  /**
   * @brief Метод контроллера для обработки состояния Win
   * @param action Нажатая клавиша виртуальной змейки
   * @param hold Была ли нажата какая-либо клавиша
   */
  void controlWin(UserAction_t action, bool hold);

  /**
   * @brief Метод контроллера для обработки состояния Game Over
   * @param action Нажатая клавиша виртуальной змейки
   * @param hold Была ли нажата какая-либо клавиша
   */
  void controlGameOver(UserAction_t action, bool hold);

  /**
   * @brief Метод для возврата информации об игровом процессе от модели в
   * представление
   */
  GameInfo_t updateCurrentState();

};  // class SnakeController

}  // namespace s21

#endif  // CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_SNAKE_SNAKE_CONTROLLER_H_
