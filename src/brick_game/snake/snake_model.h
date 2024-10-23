#ifndef CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_SNAKE_SNAKE_MODEL_H_
#define CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_SNAKE_SNAKE_MODEL_H_

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

#include "../defines.h"

namespace s21 {

/**
 * @brief Структура, содержащая всевозможные состояния конечного автомата змейки
 */
enum class SnakeFsmState_t {
  START = 0,
  SPAWN,
  INPUT,
  SHIFTING,
  ADD,
  PAUSE,
  WIN,
  GAMEOVER,
  EXIT_STATE,
};

/**
 * @brief Направления движения змейки
 */
enum SnakeDirection { UP = 0, RIGHT, DOWN, LEFT, STRAIGHT };

/**
 * @brief Возможные состояния змейки при сдвиге на одну клетку
 */
enum ShiftState { MOVE = 0, PLUS, GMOVR };

/**
 * @brief Структура, содержащая информацию о текущем состоянии игры
 * @param field Указатель на массив, содержащий информацию о заполненности
 * игрового поля: 0 - пусто, 1 - заполнен текущей игровой фигурой, 2 - заполнен
 * упавшей фигурой, 3 - голова змейки, 4 - яблоко
 * @param next Указатель на массив, содержащий информацию о следующей игровой
 * фигуре (значеня 0 - пусто и 1 - заполнен)
 * @param score Текущий счет игры
 * @param high_score Максимально набранный счет за всё время игры
 * @param level Текущий игровой уровень
 * @param speed Текущая игровая скорость
 * @param pause Информация о состоянии режима паузы
 * @param showStartScreen Включено ли отображение стартового экрана
 * @param showGameOverScreen Включено ли отображение экрана проигрыша-конца игры
 * @param showWinScreen Включено ли отображение экран выигрыша игры
 */
struct GameInfo_t {
  int** field;
  int** next;
  int score;
  int highScore;
  int level;
  int speed;
  int pause;
  int showStartScreen;
  int showGameOverScreen;
  int showWinScreen;

  /**
   * @brief Базовый конструктор структуры с состоянием игры
   */
  GameInfo_t();

  /**
   * @brief Конструктор копирования структуры с состоянием игры
   * @param other Ссылка на структуру, с которой будем копировать
   */
  GameInfo_t(const GameInfo_t& other);

  /**
   * @brief Конструктор перемещения структуры с состоянием игры
   * @param other Ссылка на структуру, с которой будем осуществлять перемещение
   */
  GameInfo_t(GameInfo_t&& other) noexcept;

  /**
   * @brief Деструктор структуры с состоянием игры
   */
  ~GameInfo_t();

  /**
   * @brief Перегрузка оператора присваивания копирования структуры с состоянием
   * игры
   * @param other Ссылка на структуру, с которой будем копировать
   */
  GameInfo_t& operator=(const GameInfo_t& other);

  /**
   * @brief Перегрузка оператора присваивания перемещения структуры с состоянием
   * игры
   * @param other Ссылка на структуру, с которой будем осуществлять перемещение
   */
  GameInfo_t& operator=(GameInfo_t&& other);

  /**
   * @brief Перегрузка оператора скобочек для быстрого доступа к информации поля
   * игры
   * @param row Искомый ряд
   * @param col Искомый столбец
   */
  int& operator()(int row, int col);

  /**
   * @brief Метод для инициализации игрового поля - выделение памяти, заполнение
   * нулями, и запись рекорда
   */
  void statistInit();

  /**
   * @brief Заполнение нулями игрового поля-статистики
   */
  void cleanField();

  /**
   * @brief Заполнение нулями поля следующей фигуры
   */
  void cleanNext();

  /**
   * @brief Выделение памяти под игровое поле
   */
  void allocateField();

  /**
   * @brief Очищение памяти с игровым полем
   */
  void deallocateField();

  /**
   * @brief Выделение памяти под поле со следующей фигурой
   */
  void allocateNext();

  /**
   * @brief Выделение памяти под поле со следующей фигурой
   */
  void deallocateNext();

  /**
   * @brief Чтение счета-рекорда с файла
   */
  void readHighScore();

  /**
   * @brief Запись счета-рекорда в файл
   */
  void writeHighScore();

  /**
   * @brief Подготовка поля для повторной игры с начала, обнуление статистики
   */
  void restartInfo();

};  // struct GameInfo_t

/**
 * @brief Класс модели Змейки, основанный на базовом классе модели
 */
class SnakeModel {
  // class SnakeModel : public Model {
 public:
  /**
   * @brief Подкласс Змея с телом змейки
   */
  class Snake {
   public:
    using vecpair = std::vector<std::pair<int, int>>;
    using pair = std::pair<int, int>;

    /**
     * @brief Базовый конструктор тела змеи
     */
    Snake();

    /**
     * @brief Конструктор копирования тела змейки
     * @param other Ссылка на тело змейки, с которого будем копировать
     */
    Snake(const Snake& other);

    /**
     * @brief Конструктор перемещения тела змейки
     * @param other Ссылка на тело змейки, с которого будем осуществлять
     * перемещение
     */
    Snake(Snake&& other) noexcept;

    /**
     * @brief Перегрузка оператора присваивания копирования тела змейки
     * @param other Ссылка на тело змейки, с которого будем копировать
     */
    Snake& operator=(const Snake& other);

    /**
     * @brief Перегрузка оператора присваивания перемещения тела змейки
     * @param other Ссылка на тело змейки, с которого будем осуществлять
     * перемещение
     */
    Snake& operator=(Snake&& other) noexcept;

    /**
     * @brief Деструктор тела змеи
     */
    ~Snake();

    /**
     * @brief Получение ссылки на начало тела змейки
     */
    const vecpair& getBody() const;

    /**
     * @brief Установка ссылки на новое начало змейки
     * @param other Ссылка на другое тело змейки
     */
    void setBody(const vecpair& other);

    /**
     * @brief Получение ссылки на голову змейки
     */
    const pair& getHead() const;

    /**
     * @brief Получение ссылки на направление, в котором движется змейка в
     * настоящий момент
     */
    const SnakeDirection& getDirect() const;

    /**
     * @brief Задание нового направления движения змейки
     * @param direct Новое направление
     */
    void setDirect(SnakeDirection direct);

    /**
     * @brief Получение ссылки на текущий размер змейки
     */
    const size_t& getSize() const;

    /**
     * @brief Прибавление к текущему значению размера тела змейки еще одного
     * узла
     */
    void plusSize();

    /**
     * @brief Задание нового размера змейки
     * @param value Новый размер змейки
     */
    void setSize(size_t value);

    /**
     * @brief Движение змейки вверх
     */
    bool upSnake();

    /**
     * @brief Движение змейки вниз
     */
    bool downSnake();

    /**
     * @brief Движение змейки влево
     */
    bool leftSnake();

    /**
     * @brief Движение змейки вправо
     */
    bool rightSnake();

    /**
     * @brief Проверка нового положения змейки на проникание в своё тело
     * @param newHeadY Новая координата головы змейки по Y
     * @param newHeadX Новая координата головы змейки по X
     */
    bool checkBodyCollision(int newHeadY, int newHeadX);

    /**
     * @brief Движение змейки прямо вдоль заданной траектории
     */
    bool straightSnake();

    /**
     * @brief Возврат змейки в стартовую позицию и состояние
     */
    void restartSnake();

    /**
     * @brief Задание первоначальных координат телу змейки
     */
    void startBodySnake();

    /**
     * @brief Добавление нового узла змейки в тело
     * @param pair Пара с координатами нового узла
     */
    void addNodeSnake(const pair& pair);

    /**
     * @brief Ручная установка координат выбранного узла тела змейки
     * @param index Место в теле змейке, где предстоит заменить координаты
     * @param row Координата по Y
     * @param col Координата по X
     */
    void setBodyNode(int index, int row, int col);

   private:
    /**
     * @brief Указатель на тело змеи
     */
    vecpair body_;

    /**
     * @brief Рамзер тела змейки
     */
    size_t size_;

    /**
     * @brief Направление движения змейки
     */
    SnakeDirection direct_;

  };  // class Snake

  /**
   * @brief Класс яблока
   */
  class Apple {
   public:
    using pair = std::pair<int, int>;

    /**
     * @brief Базовый конструктор яблока
     */
    Apple();

    /**
     * @brief Конструктор копирования яблока
     * @param other Ссылка на яблока, с которого будем копировать
     */
    Apple(const Apple& other);

    /**
     * @brief Конструктор перемещения яблока
     * @param other Ссылка яблоко, с которого будем осуществлять перемещение
     */
    Apple(Apple&& other) noexcept;

    /**
     * @brief Перегрузка оператора присваивания копирования яблока
     * @param other Ссылка на яблоко, с которого будем копировать
     */
    Apple& operator=(const Apple& other);

    /**
     * @brief Перегрузка оператора присваивания перемещения яблока
     * @param other Ссылка на яблоко, с которого будем осуществлять перемещение
     */
    Apple& operator=(Apple&& other) noexcept;

    /**
     * @brief Деструктор яблока
     */
    ~Apple();

    /**
     * @brief Генерация нового положения яблока
     * @param snake Ссылка на тело змейки для проверки генерации яблока вне тела
     */
    void appleGen(const SnakeModel::Snake& snake);

    /**
     * @brief Получение координаты нахождения яблока
     */
    const pair& getPos() const;

    /**
     * @brief Задача координаты яблока как (0,0)
     */
    void nulPos();

    /**
     * @brief Задание нового положения яблока на поле
     * @param row Координата по Y
     * @param col Координата по X
     */
    void setPos(int row, int col);

   private:
    /**
     * @brief Указатель с координатами яблока
     */
    pair position_;

  };  // class Apple

  /**
   * @brief Подкласс с телом змеи
   */
  Snake snake_;

  /**
   * @brief Подкласс с яблоком
   */
  Apple apple_;

  /**
   * @brief Подкласс для хранения состояния конечного автомата Змейки
   */
  SnakeFsmState_t fsmState_;

  /**
   * @brief Подкласс для хранения структуры-статистики игрового поля
   */
  // s21::GameInfo_t gameInfo_;
  GameInfo_t gameInfo_;

 public:
  /**
   * @brief Базовый конструктор модели Змейки
   */
  SnakeModel();

  /**
   * @brief Конструктор копирования модели змейки
   * @param other Ссылка на модель змейки, с которой будем копировать
   */
  SnakeModel(const SnakeModel& other);

  /**
   * @brief Конструктор перемещения модели змейки
   * @param other Ссылка на модель змейки, с которой будем осуществлять
   * перемещение
   */
  SnakeModel(SnakeModel&& other) noexcept;

  /**
   * @brief Перегрузка оператора присваивания копирования модели змейки
   * @param other Ссылка на модель змейки, с которой будем копировать
   */
  SnakeModel& operator=(const SnakeModel& other);

  /**
   * @brief Перегрузка оператора присваивания перемещения модели змейки
   * @param other Ссылка на модель змейки, с которой будем осуществлять
   * перемещение
   */
  SnakeModel& operator=(SnakeModel&& other) noexcept;

  /**
   * @brief Деструктор модели Змейки
   */
  ~SnakeModel();

  /**
   * @brief Получение ссылки на игровую структуру
   */
  GameInfo_t& getGameInfo();

  /**
   * @brief Получение ссылки на текущее состояние конечного автомата
   */
  const SnakeFsmState_t& getState() const;

  /**
   * @brief Получение ссылки на тело змейки
   */
  Snake& getSnake();

  /**
   * @brief Получение ссылки на координаты яблока
   */
  Apple& getApple();

  /**
   * @brief Установка нового состояния конечного автомата
   * @param state Новое состояние конечного автомата
   */
  void setState(SnakeFsmState_t state);

  /**
   * @brief Набор правил для обработки состояния конечного автомата Spawn
   */
  void fsmSpawn();

  /**
   * @brief Установка флага 1 с паузой в структуру-статистику
   */
  void setPause();

  /**
   * @brief Установка флага 0 с паузой в структуру-статистику
   */
  void setNoPause();

  /**
   * @brief Проверка на правильность ввода движения для управления змейкой на
   * текущий момент
   * @param inputAction Будущее введенное возможное направление движения змейки
   */
  bool validInput(SnakeDirection inputAction);

  /**
   * @brief Выдача контрнаправления текущего движения
   * @param inputAction Будущее введенное возможное направление движения змейки
   */
  SnakeDirection contrAction(SnakeDirection inputAction);

  /**
   * @brief Правила для состояния конечного автомата Shifting - сдвиг змеи после
   * истечения таймера
   * @param shiftAction Направление сдвига змейки
   */
  int fsmShifting(SnakeDirection shiftAction);

  /**
   * @brief Сдвиг змейки в соответствии с указанным направлением движения змейки
   * @param shiftAction Направление сдвига змейки
   */
  bool shiftSnake(SnakeDirection shiftAction);

  /**
   * @brief Проверка совпадания координат с голвой змейки и яблоком
   * @param shiftAction Направление сдвига змейки
   */
  bool appleCheck(SnakeDirection shiftAction);

  /**
   * @brief Правила для состояния конечного автомата Add - добавление нового
   * узла-яблока в тело змейки
   */
  bool fsmAdd();

  /**
   * @brief Правила для состояния конечного автомата Win - победа (набрано 200
   * очков)
   */
  void fsmWin();

  /**
   * @brief Правила для состояния конечного автомата Game Over
   */
  void fsmGameOver();

  /**
   * @brief Перезагрузка игры: змеи, яблока, игровой структуры-статистики
   */
  void restartGame();

  /**
   * @brief Зануление игрового поля-статистики от положения змейки и положения
   * яблока
   */
  void clearSnakeAppleField();

  /**
   * @brief Перевод координат змеи и яблока на игровое поле статистику
   */
  void snakeAppleToGameInfo();

};  // class SnakeModel

}  // namespace s21

#endif  // CPP3_BRICKGAME_V2_0_1_SRC_BRICK_GAME_SNAKE_SNAKE_MODEL_H_
