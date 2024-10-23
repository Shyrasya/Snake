#ifndef BUTTONS_H
#define BUTTONS_H

#include <QGridLayout>
#include <QObject>
#include <QPainter>
#include <QPushButton>
#include <QTimer>
#include <QWidget>

#include "../../brick_game/defines.h"
#include "mainwindow.h"

namespace s21 {

class MainWindow;

/**
 * @brief Класс виджета-кнопок
 */
class Buttons : public QWidget {
  Q_OBJECT

 private:
  /**
   * @brief Указатель на объект QGridLayout, который используется для управления
   * расположением виджетов
   */
  QGridLayout *layout;

  /**
   * @brief Переменная, хранящая в себе значение выбранной игры (1 - змейка, 2 -
   * тетрис)
   */
  int game;

  /**
   * @brief Переменная, указывающая, находимся ли мы в игровом режиме или в
   * главном меню (0 - в главном меню, 1 - в игре)
   */
  bool isInGame;

  /**
   * @brief Указатель на главный класс-виджет, сочетающий в себя составляющие
   * десктопа - 3 окна-виджета и десктопную логику для интерфейса
   */
  MainWindow *mainWindow_;

  /**
   * @brief Таймер для обработки задержки кнопок
   */
  QTimer *holdTimer;

 public:
  /**
   * @brief Конструктор класса Buttons - кнопок
   * @param mainWindow указатель на родительский объект для текущего виджета
   */
  explicit Buttons(MainWindow *mainWindow);

  /**
   * @brief Кнопка выхода
   */
  QPushButton *exitButton;

  /**
   * @brief Кнопка старта
   */
  QPushButton *startButton;

  /**
   * @brief Кнопка паузы
   */
  QPushButton *pauseButton;

  /**
   * @brief Кнопка вверх
   */
  QPushButton *upButton;

  /**
   * @brief Кнопка влево
   */
  QPushButton *leftButton;

  /**
   * @brief Кнопка вправо
   */
  QPushButton *rightButton;

  /**
   * @brief Кнопка действия
   */
  QPushButton *actionButton;

  /**
   * @brief Кнопка вниз
   */
  QPushButton *downButton;

 private:
  /**
   * @brief Стилевое оформление в бирюзовом стиле
   */
  QString buttonStyleBlue();

  /**
   * @brief Стилевое оформление в красном стиле
   */
  QString buttonStyleRed();

  /**
   * @brief Стилевое оформление в оранжевом стиле
   */
  QString buttonStyleOrange();

  /**
   * @brief Стилевое оформление в светло-голубом стиле
   */
  QString buttonStyleLightBlue();

  /**
   * @brief Стилевое оформление в розовом стиле
   */
  QString buttonStylePink();

 protected:
  /**
   * @brief Отрисовка кнопок в десктопной версии игр
   * @param e Указатель на объект QPaintEvent, содержащий информацию о том,
   * какие области виджета нужно перерисовать
   */
  void paintEvent(QPaintEvent *e) override;

 public slots:

  /**
   * @brief Функция для смены игрового режима на противоположный и сигналов от
   * кнопок
   */
  void setInGame();

  /**
   * @brief Функция для смены сигналов, посылаемых кнопками на виджете, на
   * игровой режим
   */
  void connectInGame();

  /**
   * @brief Функция для смены сигналов, посылаемых кнопками на виджете, на режим
   * главного меню
   */
  void connectNoGame();

  /**
   * @brief Функция для смены выбора игры (листание вверх) с помощью кнопок на
   * виджете
   */
  void moveUp();

  /**
   * @brief Функция для смены выбора игры (листание вниз) с помощью кнопок на
   * виджете
   */
  void moveDown();

  /**
   * @brief Функция для вызова сигнала выхода
   */
  void exitGame();

  /**
   * @brief Функция для начала отсчета удержания клавиши
   */
  void startHold();

  /**
   * @brief Функция для конца отсчета удержания клавиши
   */
  void stopHold();

 signals:

  /**
   * @brief Стигнал о смене игры на выбранную
   * @param game Выбранная игра
   */
  void gameChanged(int game);

  /**
   * @brief Передача сигнала выхода из игры в mainwindow
   */
  void exitSelected();

};  // class Buttons

}  // namespace s21

#endif  // BUTTONS_H
