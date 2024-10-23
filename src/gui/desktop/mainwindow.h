#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGridLayout>
#include <QKeyEvent>
#include <QMainWindow>
#include <QPainter>
#include <QPalette>

#include "../../brick_game/snake/snake_controller.h"
#include "buttons.h"
#include "desktopview.h"
#include "game.h"
#include "helpfield.h"

namespace s21 {

class GameField;
class HelpField;
class Buttons;
class SnakeModel;
class SnakeController;
class DesktopView;

/**
 * @brief Главный класс-виджет, сочетающий в себя составляющие десктопа - 3
 * окна-виджета и десктопную логику для интерфейса
 */
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  /**
   * @brief Конструктор класса MainWindow
   * @param parent указатель на родительский объект для текущего виджета
   */
  MainWindow(QWidget *parent = nullptr);

  /**
   * @brief Деструктор класса MainWindow
   */
  ~MainWindow();

  /**
   * @brief Указатель на виджет игрового поля
   */
  GameField *m_gameField;

  /**
   * @brief Указатель на виджет вспомогательного поля с игровой статистикой
   */
  HelpField *m_helpField;

  /**
   * @brief Указатель на виджет с кнопками
   */
  Buttons *m_buttons;

  /**
   * @brief Указатель на класс модели Змейки
   */
  SnakeModel *snModel;

  /**
   * @brief Указатель на игровой контроллер
   */
  SnakeController *snController;

  /**
   * @brief Указатель на десктопное представление
   */
  DesktopView *desktopView;

  /**
   * @brief Переменная, указывающая, находимся ли мы в игровом режиме или в
   * главном меню (0 - в главном меню, 1 - в игре)
   */
  bool isInGame;

  /**
   * @brief Переменная, хранящая в себе значение выбранной игры (1 - змейка, 2 -
   * тетрис)
   */
  int game;

 protected:
  /**
   * @brief Обработка событий, которые происходят после нажатия на клавиши с
   * клавиатуры
   * @param e Указатель на объект, который представляет событие нажатия клавиши
   * на клавиатуре в Qt
   */
  void keyPressEvent(QKeyEvent *e) override;

  /**
   * @brief Обработка событий, которые происходят после нажатия на клавиши с
   * клавиатуры в игровом меню
   * @param e Указатель на объект, который представляет событие нажатия клавиши
   * на клавиатуре в Qt
   */
  void handleMenuKeys(QKeyEvent *e);

  /**
   * @brief Обработка событий, которые происходят после нажатия на клавиши с
   * клавиатуры в игре
   * @param e Указатель на объект, который представляет событие нажатия клавиши
   * на клавиатуре в Qt
   */
  void handleGameKeys(QKeyEvent *e);

  /**
   * @brief Функция для создания представления и подготовки к игровому циклу
   * выбранной игры Змейка
   */
  void startSnakeGame();

  /**
   * @brief Функция для создания представления и подготовки к игровому циклу
   * выбранной игры Тетрис
   */
  void startTetrisGame();

 private:
  /**
   * @brief Указатель на центральный виджет в главном окне (MainWindow)
   * приложения
   */
  QWidget *m_centralWidget;

  /**
   * @brief Указатель на объект QGridLayout, который используется для управления
   * расположением виджетов
   */
  QGridLayout *m_gridLayout;

 public:
  /**
   * @brief Функция для старта десктопной игры в зависимости от выбора в главном
   * меню
   */
  void startGame();

  /**
   * @brief Функция для смены игрового режима на противоположный
   */
  void setInGame();

  /**
   * @brief Функция для остановки игрового цикла, удаления представления, и
   * перехода в главное меню
   */
  void exitGame();

  /**
   * @brief Функция для смены переменной пользовательского нажатия на "вверх"
   */
  void actionUp();

  /**
   * @brief Функция для смены переменной пользовательского нажатия на "вниз"
   */
  void actionDown();

  /**
   * @brief Функция для смены переменной пользовательского нажатия на "влево"
   */
  void actionLeft();

  /**
   * @brief Функция для смены переменной пользовательского нажатия на "вправо"
   */
  void actionRight();

  /**
   * @brief Функция для смены переменной пользовательского нажатия на "старт"
   */
  void actionStart();

  /**
   * @brief Функция для смены переменной пользовательского нажатия на "выход"
   */
  void actionExit();

  /**
   * @brief Функция для смены переменной пользовательского нажатия на "пауза"
   */
  void actionPause();

  /**
   * @brief Функция для смены переменной пользовательского нажатия на "действие"
   */
  void actionAction();

  /**
   * @brief Функция для смены текущей игры на выбранную
   * @param selectedGame Выбранная игра
   */
  void setSelectedGame(int selectedGame);

 signals:

  /**
   * @brief Сигнал для смены режима - игра/вне игры
   */
  void modeChange();

};  // class MainWindow

}  // namespace s21

#endif  // MAINWINDOW_H
