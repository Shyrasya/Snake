#ifndef DESKTOPVIEW_H
#define DESKTOPVIEW_H

#include <QObject>
#include <QTimer>

#include "../../brick_game/defines.h"
#include "../../brick_game/snake/snake_controller.h"
#include "../../brick_game/tetris/tetris_desktop_translate.h"
#include "mainwindow.h"

#ifdef __cplusplus
extern "C" {
#include "../../brick_game/tetris/tetris_logic.h"
#include "../input.h"
}
#endif

namespace s21 {

struct GameInfo_t;
class SnakeController;
class MainWindow;

/**
 * @brief Класс десктопного представления(отрисовки) игр
 */
class DesktopView : public QObject {
  Q_OBJECT

 private:
  /**
   * @brief Указатель на главный класс-виджет, сочетающий в себя составляющие
   * десктопа - 3 окна-виджета и десктопную логику для интерфейса
   */
  MainWindow* mainWindow_;

  /**
   * @brief Указатель на игровой контроллер
   */
  SnakeController* controller_;

 signals:

  /**
   * @brief Сигнал для смены игрового режима - игры/вне игры
   */
  void modeChange();

  /**
   * @brief Сигнал для выхода из игрового цикла
   */
  void exitGame();

 public:
  /**
   * @brief Переменная, хранящая в себе значение выбранной игры (1 - змейка, 2 -
   * тетрис)
   */
  int selectedGame;

  /**
   * @brief Переменная, хранящая в себе пользовательское действие
   */
  UserAction_t action;

  /**
   * @brief Переменная, хранящая в себе сведение о нажатии на клавишу/кнопку
   */
  bool hold;

  /**
   * @brief Состояние конечного игрового автомата
   */
  TetrisFsmState_t fsmState;

  /**
   * @brief Таймер для игрового цикла вместо while для qt
   */
  QTimer* timer_;

  /**
   * @brief Дефолтный конструктор базового класса
   * @param controller Указатель на контроллер, взаимодействующий с
   * представлением
   */
  DesktopView(MainWindow* mainWindow, SnakeController* controller);

  /**
   * @brief Начальная подготовка к стартовому состоянию конечного игрового
   * автомата десктопной игры Змейка
   */
  void startDesktopSnakeEventLoop();

  /**
   * @brief Главный игровой цикл десктопной игры Змейка
   */
  void gameSnakeLoop();

  /**
   * @brief Начальная подготовка к стартовому состоянию конечного игрового
   * автомата десктопной игры Тетрис
   */
  void startDesktopTetrisEventLoop();

  /**
   * @brief Главный игровой цикл десктопной игры Тетрис
   */
  void gameTetrisLoop();

  /**
   * @brief Отрисовка игрового поля и дополнительной информации об игре в
   * соответствии с состоянием
   * @param gameInfo Структура с текущим состоянием поля, шаблоном следующей
   * фигуры, очков и т.п.
   */
  void printDesktopStatist(const s21::GameInfo_t& gameInfo);

  /**
   * @brief Вызов paintEvent для игрового поля и дополнительной информации
   */
  void updateView();

};  // class DesktopView

}  // namespace s21

#endif  // DESKTOPVIEW_H
