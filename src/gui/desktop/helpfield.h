#ifndef HELPFIELD_H
#define HELPFIELD_H

#include <QPainter>
#include <QWidget>

#include "../../brick_game/snake/snake_controller.h"

#ifdef __cplusplus
extern "C" {
#include "../../brick_game/tetris/tetris_logic.h"
}
#endif

namespace s21 {

class MainWindow;

/**
 * @brief Класс виджета-дополнительной информации
 */
class HelpField : public QWidget {
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

 protected:
  /**
   * @brief Отрисовка дополнительной информации в десктопной версии игр
   * @param e Указатель на объект QPaintEvent, содержащий информацию о том,
   * какие области виджета нужно перерисовать
   */
  void paintEvent(QPaintEvent *e) override;

 public:
  /**
   * @brief Конструктор класса HelpField - дополнительной информации
   * @param parent указатель на родительский объект для текущего виджета
   */
  explicit HelpField(QWidget *parent = nullptr);

  /**
   * @brief Структура с текущим состоянием поля, шаблоном следующей
   * фигуры, очков и т.п.
   */
  s21::GameInfo_t gameInfo;

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
   * @brief Печать максимального счета
   * @param painter Ссылка на объект QPainter, который используется для
   * рисования на виджете
   */
  void printHighScore(QPainter &painter);

  /**
   * @brief Печать/затирка паузы
   * @param painter Ссылка на объект QPainter, который используется для
   * рисования на виджете
   */
  void printPause(QPainter &painter);

  /**
   * @brief Печать поля со следующей фигурой
   * @param painter Ссылка на объект QPainter, который используется для
   * рисования на виджете
   */
  void printNext(QPainter &painter);

  /**
   * @brief Затирка информации с текущим счетом, максимльным счетом, уровнем
   * @param painter Ссылка на объект QPainter, который используется для
   * рисования на виджете
   */
  void clearScoreLevel(QPainter &painter);

  /**
   * @brief Печать информации с текущим счетом, максимльным счетом, уровнем
   * @param painter Ссылка на объект QPainter, который используется для
   * рисования на виджете
   */
  void printScoreLevel(QPainter &painter);

  /**
   * @brief Затирка поля со следующей фигурой
   * @param painter Ссылка на объект QPainter, который используется для
   * рисования на виджете
   */
  void clearNext(QPainter &painter);

  /**
   * @brief Затирка паузы
   * @param painter Ссылка на объект QPainter, который используется для
   * рисования на виджете
   */
  void clearPause(QPainter &painter);

  /**
   * @brief Установка информации об игровой статистике в атрибут класса
   * дополнительной информации
   * @param statist Структура с текущим состоянием поля, шаблоном следующей
   * фигуры, очков и т.п.
   */
  void helpSetGameInfo(const s21::GameInfo_t &viewGameInfo);

};  // class HelpField

}  // namespace s21

#endif  // HELPFIELD_H
