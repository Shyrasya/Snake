#ifndef GAME_H
#define GAME_H

#include <QPainter>
#include <QWidget>

#include "../../brick_game/snake/snake_controller.h"

namespace s21 {

class MainWindow;

/**
 * @brief Класс виджета-игрового поля
 */
class GameField : public QWidget {
  Q_OBJECT

 private:
  /**
   * @brief Переменная, хранящая в себе значение выбранной игры (1 - змейка, 2 -
   * тетрис)
   */
  int selectedGame;

  /**
   * @brief Переменная, указывающая, находимся ли мы в игровом режиме или в
   * главном меню (0 - в главном меню, 1 - в игре)
   */
  bool isInGame;

  /**
   * @brief Структура с текущим состоянием поля, шаблоном следующей
   * фигуры, очков и т.п.
   */
  s21::GameInfo_t gameInfo;

 protected:
  /**
   * @brief Отрисовка игрового поля в десктопной версии игр
   * @param e Указатель на объект QPaintEvent, содержащий информацию о том,
   * какие области виджета нужно перерисовать
   */
  void paintEvent(QPaintEvent *e) override;

 public:
  /**
   * @brief Конструктор класса GameField - игрового поля
   * @param parent указатель на родительский объект для текущего виджета
   */
  explicit GameField(QWidget *parent = nullptr);

 public:
  /**
   * @brief Функция для смены текущей игры на выбранную
   * @param game Выбранная игра
   */
  void setSelectedGame(int game);

  /**
   * @brief Функция для смены игрового режима на противоположный
   */
  void setInGame();

  /**
   * @brief Очистка/заливка всего игрового поля белым цветом
   * @param painter Ссылка на объект QPainter, который используется для
   * рисования на виджете
   */
  void clearField(QPainter &painter);

  /**
   * @brief Печать названий игр в главном меню
   * @param painter Ссылка на объект QPainter, который используется для
   * рисования на виджете
   */
  void printChoice(QPainter &painter);

  /**
   * @brief Стартовая печать названия выбранной игры в меню
   * @param painter Ссылка на объект QPainter, который используется для
   * рисования на виджете
   */
  void printNameStart(QPainter &painter);

  /**
   * @brief Печать подсказки на игровом поле для старта игры
   * @param painter Ссылка на объект QPainter, который используется для
   * рисования на виджете
   */
  void printStart(QPainter &painter);

  /**
   * @brief Печать надписи о проигрыше на игровом поле
   * @param painter Ссылка на объект QPainter, который используется для
   * рисования на виджете
   */
  void printGameOver(QPainter &painter);

  /**
   * @brief Печать надписи о выигрыше на игровом поле
   * @param painter Ссылка на объект QPainter, который используется для
   * рисования на виджете
   */
  void printWinScreen(QPainter &painter);

  /**
   * @brief Печать закрашенных кубов в соответствии с игровой статистикой на
   * поле
   * @param painter Ссылка на объект QPainter, который используется для
   * рисования на виджете
   */
  void printField(QPainter &painter);

  /**
   * @brief Установка информации об игровой статистике в атрибут класса игрового
   * поля
   * @param statist Структура с текущим состоянием поля, шаблоном следующей
   * фигуры, очков и т.п.
   */
  void gameSetGameInfo(const s21::GameInfo_t &viewGameInfo);

};  // class GameField

}  // namespace s21

#endif  // GAME_H
