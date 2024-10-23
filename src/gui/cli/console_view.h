#ifndef CPP3_BRICKGAME_V2_0_1_SRC_GUI_CLI_CONSOLE_VIEW_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_GUI_CLI_CONSOLE_VIEW_H_

#include "../../brick_game/defines.h"
#include "../input.h"
#include "ncurses_defines.h"

/**
 * @brief Обработка нажатия клавиши и её перевод в структурный аналог для
 * дальнейших манипуляций
 * @param action Нажатая клавиша виртуальной змейки
 * @param hold Была ли нажата какая-либо клавиша
 */
bool getInput(int input, UserAction_t* action, bool hold);

#ifdef __cplusplus

#define CV ConsoleView::
#include "../../brick_game/snake/snake_controller.h"

namespace s21 {

struct GameInfo_t;
class SnakeController;

/**
 * @brief Класс консольного представления(отрисовки) игр
 */
class ConsoleView {
 private:
  /**
   * @brief Указатель на игровой контроллер
   */
  SnakeController* controller_;

 public:
  /**
   * @brief Дефолтный конструктор базового класса
   * @param controller Указатель на контроллер, взаимодействующий с
   * представлением
   */
  explicit ConsoleView(SnakeController* controller) : controller_(controller){};

  /**
   * @brief Дефолтный конструктор базового класса (пустышка) для отдельного
   * объявления представления без контроллера
   * @param controller Указатель (nullptr) на контроллер, взаимодействующий с
   * представлением
   */
  explicit ConsoleView(nullptr_t) : controller_(nullptr) {}

#else
#include "../../brick_game/tetris/objects.h"
#define CV
#endif  //__cplusplus

  /**
   * @brief Печать заставки для Змейки
   */
  void printSnakeStart();

  /**
   * @brief Печать заставки для Тетриса
   */
  void printTetrisStart();

  /**
   * @brief Печать в консоли "Press enter to start"
   */
  void printStart();

  /**
   * @brief Зачистка в консоли игрового поля пустотой
   */
  void clearField();

  /**
   * @brief Зачистка в консоли счета-рекорда, счета и уровня пустотой
   */
  void clearScoreLevel();

  /**
   * @brief Зачистка в консоли поля со следующей сгенерированной фигурой
   */
  void clearNext();

  /**
   * @brief Зачистка в консоли поля сообщения о паузе
   */
  void clearPause();

  /**
   * @brief Полная зачистка поля, следующей фигуры, статистики, паузы
   */
  void clearValues();

  /**
   * @brief Печать в консоли сообщения о текущей паузе
   * @param statist Структура с текущим состоянием поля, шаблоном следующей
   * фигуры, очков и т.п.
   */
  void printPause(GameInfo_t statist);

  /**
   * @brief Печать в консоли счета-рекорда
   * @param statist Структура с текущим состоянием поля, шаблоном следующей
   * фигуры, очков и т.п.
   */
  void printHighScore(GameInfo_t statist);

  /**
   * @brief Вывод в консоль информации о игре (поля, статистика, пауза)
   * @param statist Структура с текущим состоянием поля, шаблоном следующей
   * фигуры, очков и т.п.
   * @param game Название текущей игры в виде int
   */
  void printStatist(GameInfo_t statist, int game);

  /**
   * @brief Отрисовка в консоли фигур на игровом поле в соответствии с массивом
   * field, отрисовка значений статистики
   * @param statist Структура с текущим состоянием поля, шаблоном следующей
   * фигуры, очков и т.п.
   */
  void printField(GameInfo_t statist);

  /**
   * @brief Отрисовка в консоли следующей сгенерированной фигуры
   * @param statist Структура с текущим состоянием поля, шаблоном следующей
   * фигуры, очков и т.п.
   */
  void printNext(GameInfo_t statist);

  /**
   * @brief Печать в консоли сообщения с окончанием игры
   */
  void printGameOver();

  /**
   * @brief Печать в консоли сообщения о победе в игре Змейка
   */
  void printWinScreen();

#ifdef __cplusplus

  /**
   * @brief Главный игровой цикл игры Змейка
   */
  void startSnakeEventLoop();

};  // class ConsoleView

}  // namespace s21

#endif  // __cplusplus

#endif  // CPP3_BRICKGAME_V2_0_1_SRC_GUI_CLI_CONSOLE_VIEW_H_