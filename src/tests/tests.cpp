#include <filesystem>

#include "../brick_game/defines.h"
#include "../brick_game/snake/snake_model.h"
#include "../gui/input.h"
#include "gtest/gtest.h"

using namespace s21;

TEST(GameInfoTest1, defaultConstructor) {
  GameInfo_t statist;
  EXPECT_NE(nullptr, statist.field);
  EXPECT_NE(nullptr, statist.next);
  EXPECT_EQ(0, statist.score);
  EXPECT_EQ(0, statist.highScore);
  EXPECT_EQ(1, statist.level);
  EXPECT_EQ(0, statist.pause);
  EXPECT_EQ(1, statist.showStartScreen);
  EXPECT_EQ(0, statist.showGameOverScreen);
  EXPECT_EQ(0, statist.showWinScreen);
  for (int r = 0; r < MAP_ROWS; r++) {
    for (int c = 0; c < MAP_COLS; c++) {
      EXPECT_EQ(0, statist.field[r][c]);
    }
  }
  for (int r = 0; r < QUADR; r++) {
    for (int c = 0; c < QUADR; c++) {
      EXPECT_EQ(0, statist.next[r][c]);
    }
  }
}

TEST(GameInfoTest2, copyConstructor) {
  GameInfo_t statist;
  statist.score = 15;
  statist.level = 3;
  statist.pause = 0;
  statist.showStartScreen = 0;
  statist.showGameOverScreen = 0;
  statist.showWinScreen = 0;
  statist.highScore = 1000;
  statist(4, 9) = 1;
  GameInfo_t statistCopy(statist);

  EXPECT_NE(nullptr, statistCopy.field);
  EXPECT_NE(nullptr, statistCopy.next);
  EXPECT_EQ(15, statistCopy.score);
  EXPECT_EQ(3, statistCopy.level);
  EXPECT_EQ(0, statistCopy.pause);
  EXPECT_EQ(0, statistCopy.showStartScreen);
  EXPECT_EQ(0, statistCopy.showGameOverScreen);
  EXPECT_EQ(0, statistCopy.showWinScreen);
  EXPECT_EQ(1000, statistCopy.highScore);
  EXPECT_EQ(1, statistCopy(4, 9));
}

TEST(GameInfoTest3, moveConstructor) {
  GameInfo_t statist;
  statist.score = 20;
  statist.level = 4;
  statist.pause = 0;
  statist.showStartScreen = 0;
  statist.showGameOverScreen = 0;
  statist.showWinScreen = 0;
  statist.highScore = 40;
  statist(6, 8) = 1;
  GameInfo_t statistCopy(std::move(statist));

  EXPECT_NE(nullptr, statistCopy.field);
  EXPECT_NE(nullptr, statistCopy.next);
  EXPECT_EQ(20, statistCopy.score);
  EXPECT_EQ(4, statistCopy.level);
  EXPECT_EQ(0, statistCopy.pause);
  EXPECT_EQ(0, statistCopy.showStartScreen);
  EXPECT_EQ(0, statistCopy.showGameOverScreen);
  EXPECT_EQ(0, statistCopy.showWinScreen);
  EXPECT_EQ(40, statistCopy.highScore);
  EXPECT_EQ(1, statistCopy(6, 8));
}

TEST(GameInfoTest4, copyAssignOperator) {
  GameInfo_t statist;
  statist.score = 30;
  statist.level = 6;
  statist.pause = 0;
  statist.showStartScreen = 0;
  statist.showGameOverScreen = 0;
  statist.showWinScreen = 0;
  statist.highScore = 70;
  statist(22, 7) = 1;
  GameInfo_t statistCopy;
  statistCopy = statist;

  EXPECT_NE(nullptr, statistCopy.field);
  EXPECT_NE(nullptr, statistCopy.next);
  EXPECT_EQ(30, statistCopy.score);
  EXPECT_EQ(6, statistCopy.level);
  EXPECT_EQ(0, statistCopy.pause);
  EXPECT_EQ(0, statistCopy.showStartScreen);
  EXPECT_EQ(0, statistCopy.showGameOverScreen);
  EXPECT_EQ(0, statistCopy.showWinScreen);
  EXPECT_EQ(70, statistCopy.highScore);
  EXPECT_EQ(1, statistCopy(22, 7));
}

TEST(GameInfoTest5, moveAssignOperator) {
  GameInfo_t statist;
  statist.score = 100;
  statist.level = 10;
  statist.pause = 0;
  statist.showStartScreen = 0;
  statist.showGameOverScreen = 0;
  statist.showWinScreen = 0;
  statist.highScore = 150;
  statist(14, 9) = 1;
  GameInfo_t statistCopy;
  statistCopy = std::move(statist);

  EXPECT_NE(nullptr, statistCopy.field);
  EXPECT_NE(nullptr, statistCopy.next);
  EXPECT_EQ(100, statistCopy.score);
  EXPECT_EQ(10, statistCopy.level);
  EXPECT_EQ(0, statistCopy.pause);
  EXPECT_EQ(0, statistCopy.showStartScreen);
  EXPECT_EQ(0, statistCopy.showGameOverScreen);
  EXPECT_EQ(0, statistCopy.showWinScreen);
  EXPECT_EQ(150, statistCopy.highScore);
  EXPECT_EQ(1, statistCopy(14, 9));
}

TEST(GameInfoTest6, restartInfo) {
  GameInfo_t statist;
  statist.score = 60;
  statist.level = 10;
  statist.pause = 0;
  statist.showStartScreen = 0;
  statist.showGameOverScreen = 0;
  statist.showWinScreen = 0;
  statist.highScore = 159;
  statist(6, 4) = 1;
  if (std::filesystem::exists("high_score_snake.txt"))
    std::filesystem::remove("high_score_snake.txt");

  statist.restartInfo();

  EXPECT_NE(nullptr, statist.field);
  EXPECT_NE(nullptr, statist.next);
  EXPECT_EQ(0, statist.score);
  EXPECT_EQ(1, statist.level);
  EXPECT_EQ(1, statist.speed);
  EXPECT_EQ(0, statist.pause);
  EXPECT_EQ(0, statist.showStartScreen);
  EXPECT_EQ(0, statist.showGameOverScreen);
  EXPECT_EQ(0, statist.showWinScreen);
  EXPECT_EQ(0, statist.highScore);
  EXPECT_EQ(0, statist(6, 4));
}

TEST(SnakeTest1, defaultConstructor) {
  SnakeModel::Snake snake;
  EXPECT_EQ(4, snake.getSize());
  EXPECT_EQ(RIGHT, snake.getDirect());
  EXPECT_EQ(std::make_pair(MAP_ROWS - 1, MAP_COLS / 2 + 1), snake.getBody()[0]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 1, MAP_COLS / 2), snake.getBody()[1]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 1, MAP_COLS / 2 - 1), snake.getBody()[2]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 1, MAP_COLS / 2 - 2), snake.getBody()[3]);
}

TEST(SnakeTest2, copyConstructor) {
  SnakeModel::Snake snake;
  SnakeModel::Snake copySnake(snake);
  EXPECT_EQ(4, copySnake.getSize());
  EXPECT_EQ(RIGHT, copySnake.getDirect());
  EXPECT_EQ(std::make_pair(MAP_ROWS - 1, MAP_COLS / 2 + 1),
            copySnake.getBody()[0]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 1, MAP_COLS / 2), copySnake.getBody()[1]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 1, MAP_COLS / 2 - 1),
            copySnake.getBody()[2]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 1, MAP_COLS / 2 - 2),
            copySnake.getBody()[3]);
}

TEST(SnakeTest3, moveConstructor) {
  SnakeModel::Snake snake;
  SnakeModel::Snake copySnake(std::move(snake));
  EXPECT_EQ(4, copySnake.getSize());
  EXPECT_EQ(0, snake.getSize());
  EXPECT_EQ(RIGHT, copySnake.getDirect());
  EXPECT_EQ(std::make_pair(MAP_ROWS - 1, MAP_COLS / 2 + 1),
            copySnake.getBody()[0]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 1, MAP_COLS / 2), copySnake.getBody()[1]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 1, MAP_COLS / 2 - 1),
            copySnake.getBody()[2]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 1, MAP_COLS / 2 - 2),
            copySnake.getBody()[3]);
}

TEST(SnakeTest4, copyAssignOperator) {
  SnakeModel::Snake snake;
  snake.setDirect(UP);
  snake.addNodeSnake(std::make_pair(MAP_ROWS - 1, MAP_COLS / 2 + 2));
  SnakeModel::Snake copySnake;
  copySnake = snake;

  EXPECT_EQ(5, copySnake.getSize());
  EXPECT_EQ(UP, copySnake.getDirect());
  EXPECT_EQ(std::make_pair(MAP_ROWS - 1, MAP_COLS / 2 + 2),
            copySnake.getBody()[0]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 1, MAP_COLS / 2 + 1),
            copySnake.getBody()[1]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 1, MAP_COLS / 2), copySnake.getBody()[2]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 1, MAP_COLS / 2 - 1),
            copySnake.getBody()[3]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 1, MAP_COLS / 2 - 2),
            copySnake.getBody()[4]);
}

TEST(SnakeTest5, moveAssignOperator) {
  SnakeModel::Snake snake;
  snake.setDirect(LEFT);
  snake.addNodeSnake(std::make_pair(MAP_ROWS - 1, MAP_COLS / 2 + 2));
  SnakeModel::Snake copySnake;
  copySnake = std::move(snake);

  EXPECT_EQ(5, copySnake.getSize());
  EXPECT_EQ(0, snake.getSize());
  EXPECT_EQ(LEFT, copySnake.getDirect());
  EXPECT_EQ(std::make_pair(MAP_ROWS - 1, MAP_COLS / 2 + 2),
            copySnake.getBody()[0]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 1, MAP_COLS / 2 + 1),
            copySnake.getBody()[1]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 1, MAP_COLS / 2), copySnake.getBody()[2]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 1, MAP_COLS / 2 - 1),
            copySnake.getBody()[3]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 1, MAP_COLS / 2 - 2),
            copySnake.getBody()[4]);
}

TEST(SnakeTest6, getHead) {
  SnakeModel::Snake snake;
  EXPECT_EQ(std::make_pair(MAP_ROWS - 1, MAP_COLS / 2 + 1), snake.getHead());
}

TEST(SnakeTest7, plusSize) {
  SnakeModel::Snake snake;
  snake.plusSize();
  EXPECT_EQ(5, snake.getSize());
}

TEST(SnakeTest8, upSnake) {
  SnakeModel::Snake snake;
  snake.upSnake();
  EXPECT_EQ(std::make_pair(MAP_ROWS - 2, MAP_COLS / 2 + 1), snake.getBody()[0]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 1, MAP_COLS / 2 + 1), snake.getBody()[1]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 1, MAP_COLS / 2), snake.getBody()[2]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 1, MAP_COLS / 2 - 1), snake.getBody()[3]);
}

TEST(SnakeTest9, downSnake) {
  SnakeModel::Snake snake;
  snake.setBodyNode(0, MAP_ROWS - 2, MAP_COLS / 2 + 1);
  snake.setBodyNode(1, MAP_ROWS - 2, MAP_COLS / 2);
  snake.setBodyNode(2, MAP_ROWS - 2, MAP_COLS / 2 - 1);
  snake.setBodyNode(3, MAP_ROWS - 2, MAP_COLS / 2 - 2);
  snake.downSnake();
  EXPECT_EQ(std::make_pair(MAP_ROWS - 1, MAP_COLS / 2 + 1), snake.getBody()[0]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 2, MAP_COLS / 2 + 1), snake.getBody()[1]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 2, MAP_COLS / 2), snake.getBody()[2]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 2, MAP_COLS / 2 - 1), snake.getBody()[3]);
}

TEST(SnakeTest10, leftSnake) {
  SnakeModel::Snake snake;
  snake.setBodyNode(0, MAP_ROWS - 4, 1);
  snake.setBodyNode(1, MAP_ROWS - 3, 1);
  snake.setBodyNode(2, MAP_ROWS - 2, 1);
  snake.setBodyNode(3, MAP_ROWS - 1, 1);
  snake.leftSnake();
  EXPECT_EQ(std::make_pair(MAP_ROWS - 4, 0), snake.getBody()[0]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 4, 1), snake.getBody()[1]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 3, 1), snake.getBody()[2]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 2, 1), snake.getBody()[3]);
}

TEST(SnakeTest11, rightSnake) {
  SnakeModel::Snake snake;
  snake.setBodyNode(0, MAP_ROWS - 4, 1);
  snake.setBodyNode(1, MAP_ROWS - 3, 1);
  snake.setBodyNode(2, MAP_ROWS - 2, 1);
  snake.setBodyNode(3, MAP_ROWS - 1, 1);
  snake.rightSnake();
  EXPECT_EQ(std::make_pair(MAP_ROWS - 4, 2), snake.getBody()[0]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 4, 1), snake.getBody()[1]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 3, 1), snake.getBody()[2]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 2, 1), snake.getBody()[3]);
}

TEST(SnakeTest12, straightSnakeUp) {
  SnakeModel::Snake snake;
  snake.setDirect(UP);
  snake.setBodyNode(0, MAP_ROWS - 4, 1);
  snake.setBodyNode(1, MAP_ROWS - 3, 1);
  snake.setBodyNode(2, MAP_ROWS - 2, 1);
  snake.setBodyNode(3, MAP_ROWS - 1, 1);
  EXPECT_EQ(1, snake.straightSnake());
  EXPECT_EQ(std::make_pair(MAP_ROWS - 5, 1), snake.getBody()[0]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 4, 1), snake.getBody()[1]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 3, 1), snake.getBody()[2]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 2, 1), snake.getBody()[3]);
}

TEST(SnakeTest13, straightSnakeDown) {
  SnakeModel::Snake snake;
  snake.setDirect(DOWN);
  snake.setBodyNode(0, MAP_ROWS - 2, 1);
  snake.setBodyNode(1, MAP_ROWS - 3, 1);
  snake.setBodyNode(2, MAP_ROWS - 4, 1);
  snake.setBodyNode(3, MAP_ROWS - 5, 1);
  EXPECT_EQ(1, snake.straightSnake());
  EXPECT_EQ(std::make_pair(MAP_ROWS - 1, 1), snake.getBody()[0]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 2, 1), snake.getBody()[1]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 3, 1), snake.getBody()[2]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 4, 1), snake.getBody()[3]);
}

TEST(SnakeTest13, straightSnakeLeft) {
  SnakeModel::Snake snake;
  snake.setDirect(LEFT);
  snake.setBodyNode(0, MAP_ROWS - 1, 1);
  snake.setBodyNode(1, MAP_ROWS - 1, 2);
  snake.setBodyNode(2, MAP_ROWS - 1, 3);
  snake.setBodyNode(3, MAP_ROWS - 1, 4);
  EXPECT_EQ(1, snake.straightSnake());
  EXPECT_EQ(std::make_pair(MAP_ROWS - 1, 0), snake.getBody()[0]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 1, 1), snake.getBody()[1]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 1, 2), snake.getBody()[2]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 1, 3), snake.getBody()[3]);
}

TEST(SnakeTest14, straightSnakeRight) {
  SnakeModel::Snake snake;
  snake.setDirect(RIGHT);
  snake.setBodyNode(0, MAP_ROWS - 1, 4);
  snake.setBodyNode(1, MAP_ROWS - 1, 3);
  snake.setBodyNode(2, MAP_ROWS - 1, 2);
  snake.setBodyNode(3, MAP_ROWS - 1, 1);
  EXPECT_EQ(1, snake.straightSnake());
  EXPECT_EQ(std::make_pair(MAP_ROWS - 1, 5), snake.getBody()[0]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 1, 4), snake.getBody()[1]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 1, 3), snake.getBody()[2]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 1, 2), snake.getBody()[3]);
}

TEST(SnakeTest15, restartSnake) {
  SnakeModel::Snake snake;
  snake.setDirect(LEFT);
  snake.setBodyNode(0, MAP_ROWS - 2, 4);
  snake.setBodyNode(1, MAP_ROWS - 2, 3);
  snake.setBodyNode(2, MAP_ROWS - 2, 2);
  snake.setBodyNode(3, MAP_ROWS - 2, 1);
  snake.restartSnake();
  EXPECT_EQ(std::make_pair(MAP_ROWS - 1, MAP_COLS / 2 + 1), snake.getBody()[0]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 1, MAP_COLS / 2), snake.getBody()[1]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 1, MAP_COLS / 2 - 1), snake.getBody()[2]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 1, MAP_COLS / 2 - 2), snake.getBody()[3]);
  EXPECT_EQ(RIGHT, snake.getDirect());
}

TEST(SnakeTest16, checkBodyCollisionInside) {
  SnakeModel::Snake snake;
  snake.setDirect(LEFT);
  snake.plusSize();
  snake.setBodyNode(0, MAP_ROWS - 2, 1);
  snake.setBodyNode(1, MAP_ROWS - 3, 1);
  snake.setBodyNode(2, MAP_ROWS - 3, 0);
  snake.setBodyNode(3, MAP_ROWS - 2, 0);
  snake.setBodyNode(4, MAP_ROWS - 1, 0);
  EXPECT_FALSE(snake.checkBodyCollision(MAP_ROWS - 2, 0));
}

TEST(SnakeTest17, checkBodyCollisionInsideOutOfRange) {
  SnakeModel::Snake snake;
  snake.setDirect(LEFT);
  EXPECT_THROW(snake.setBodyNode(4, 15, 6), std::out_of_range);
}

TEST(AppleTest1, defaultConstructor) {
  SnakeModel::Apple apple;
  EXPECT_EQ(std::make_pair(0, 0), apple.getPos());
}

TEST(AppleTest2, copyConstructor) {
  SnakeModel::Apple apple;
  apple.setPos(15, 9);
  SnakeModel::Apple appleCopy(apple);
  EXPECT_EQ(std::make_pair(15, 9), appleCopy.getPos());
}

TEST(AppleTest3, moveConstructor) {
  SnakeModel::Apple apple;
  apple.setPos(11, 7);
  SnakeModel::Apple appleCopy(std::move(apple));
  EXPECT_EQ(std::make_pair(11, 7), appleCopy.getPos());
}

TEST(AppleTest4, copyAssignOperator) {
  SnakeModel::Apple apple;
  apple.setPos(6, 4);
  SnakeModel::Apple appleCopy;
  appleCopy = apple;
  EXPECT_EQ(std::make_pair(6, 4), appleCopy.getPos());
}

TEST(AppleTest5, moveAssignOperator) {
  SnakeModel::Apple apple;
  apple.setPos(7, 3);
  SnakeModel::Apple appleCopy;
  appleCopy = std::move(apple);
  EXPECT_EQ(std::make_pair(7, 3), appleCopy.getPos());
}

TEST(AppleTest6, appleGen) {
  SnakeModel::Snake snake;
  SnakeModel::Apple apple;
  apple.appleGen(snake);
  EXPECT_NE(std::make_pair(0, 0), apple.getPos());
  EXPECT_GE(apple.getPos().first, QUADR);
  EXPECT_GE(apple.getPos().second, 0);
  EXPECT_LT(apple.getPos().first, MAP_ROWS);
  EXPECT_LT(apple.getPos().second, MAP_COLS);
}

TEST(AppleTest7, nulPos) {
  SnakeModel::Apple apple;
  apple.setPos(6, 8);
  apple.nulPos();
  EXPECT_EQ(std::make_pair(0, 0), apple.getPos());
}

TEST(ModelTest1, defaultConstructor) {
  SnakeModel model;
  EXPECT_EQ(SnakeFsmState_t::START, model.getState());
  EXPECT_EQ(4, model.getSnake().getSize());
  EXPECT_EQ(RIGHT, model.getSnake().getDirect());
  EXPECT_EQ(std::make_pair(MAP_ROWS - 1, MAP_COLS / 2 + 1),
            model.getSnake().getBody()[0]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 1, MAP_COLS / 2),
            model.getSnake().getBody()[1]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 1, MAP_COLS / 2 - 1),
            model.getSnake().getBody()[2]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 1, MAP_COLS / 2 - 2),
            model.getSnake().getBody()[3]);
  EXPECT_EQ(std::make_pair(0, 0), model.getApple().getPos());
  EXPECT_NE(nullptr, model.getGameInfo().field);
  EXPECT_NE(nullptr, model.getGameInfo().next);
  EXPECT_EQ(0, model.getGameInfo().score);
  EXPECT_EQ(0, model.getGameInfo().highScore);
  EXPECT_EQ(1, model.getGameInfo().level);
  EXPECT_EQ(0, model.getGameInfo().pause);
  EXPECT_EQ(1, model.getGameInfo().showStartScreen);
  EXPECT_EQ(0, model.getGameInfo().showGameOverScreen);
  EXPECT_EQ(0, model.getGameInfo().showWinScreen);
  for (int r = 0; r < MAP_ROWS; r++) {
    for (int c = 0; c < MAP_COLS; c++) {
      EXPECT_EQ(0, model.getGameInfo().field[r][c]);
    }
  }
  for (int r = 0; r < QUADR; r++) {
    for (int c = 0; c < QUADR; c++) {
      EXPECT_EQ(0, model.getGameInfo().next[r][c]);
    }
  }
}

TEST(ModelTest2, setState) {
  SnakeModel model;
  model.setState(SnakeFsmState_t::SPAWN);
  EXPECT_EQ(SnakeFsmState_t::SPAWN, model.getState());
}

TEST(ModelTest3, fsmSpawn) {
  SnakeModel model;
  model.fsmSpawn();
  EXPECT_NE(std::make_pair(0, 0), model.getApple().getPos());
  EXPECT_EQ(0, model.getGameInfo().showGameOverScreen);
  EXPECT_EQ(0, model.getGameInfo().showWinScreen);
  EXPECT_EQ(0, model.getGameInfo().showStartScreen);
}

TEST(ModelTest4, setPause) {
  SnakeModel model;
  model.setPause();
  EXPECT_EQ(1, model.getGameInfo().pause);
}

TEST(ModelTest5, validInputUp) {
  SnakeModel model;
  EXPECT_TRUE(model.validInput(UP));
}

TEST(ModelTest6, validInputDown) {
  SnakeModel model;
  model.getSnake().setBodyNode(0, MAP_ROWS - 2, MAP_COLS / 2 + 1);
  model.getSnake().setBodyNode(1, MAP_ROWS - 2, MAP_COLS / 2);
  model.getSnake().setBodyNode(2, MAP_ROWS - 2, MAP_COLS / 2 - 1);
  model.getSnake().setBodyNode(3, MAP_ROWS - 2, MAP_COLS / 2 - 2);
  EXPECT_TRUE(model.validInput(DOWN));
}

TEST(ModelTest6, validInputLeft) {
  SnakeModel model;
  model.getSnake().setDirect(UP);
  model.getSnake().setBodyNode(0, MAP_ROWS - 4, 1);
  model.getSnake().setBodyNode(1, MAP_ROWS - 3, 1);
  model.getSnake().setBodyNode(2, MAP_ROWS - 2, 1);
  model.getSnake().setBodyNode(3, MAP_ROWS - 1, 1);
  EXPECT_TRUE(model.validInput(LEFT));
}

TEST(ModelTest7, validInputRight) {
  SnakeModel model;
  model.getSnake().setDirect(UP);
  model.getSnake().setBodyNode(0, MAP_ROWS - 4, 5);
  model.getSnake().setBodyNode(1, MAP_ROWS - 3, 5);
  model.getSnake().setBodyNode(2, MAP_ROWS - 2, 5);
  model.getSnake().setBodyNode(3, MAP_ROWS - 1, 5);
  EXPECT_TRUE(model.validInput(RIGHT));
}

TEST(ModelTest8, fsmShiftingStraight) {
  SnakeModel model;
  model.getApple().setPos(10, 1);
  model.getSnake().setDirect(UP);
  model.getSnake().setBodyNode(0, MAP_ROWS - 4, 8);
  model.getSnake().setBodyNode(1, MAP_ROWS - 3, 8);
  model.getSnake().setBodyNode(2, MAP_ROWS - 2, 8);
  model.getSnake().setBodyNode(3, MAP_ROWS - 1, 8);
  EXPECT_EQ(ShiftState::MOVE, model.fsmShifting(STRAIGHT));
}

TEST(ModelTest9, fsmShiftingLeft) {
  SnakeModel model;
  model.getApple().setPos(5, 4);
  model.getSnake().setDirect(UP);
  model.getSnake().setBodyNode(0, MAP_ROWS - 2, 2);
  model.getSnake().setBodyNode(1, MAP_ROWS - 3, 2);
  model.getSnake().setBodyNode(2, MAP_ROWS - 4, 2);
  model.getSnake().setBodyNode(3, MAP_ROWS - 5, 2);
  EXPECT_EQ(ShiftState::MOVE, model.fsmShifting(LEFT));
  EXPECT_EQ(LEFT, model.getSnake().getDirect());
}

TEST(ModelTest9, fsmShiftingRight) {
  SnakeModel model;
  model.getApple().setPos(16, 9);
  model.getSnake().setDirect(UP);
  model.getSnake().setBodyNode(0, MAP_ROWS - 2, 5);
  model.getSnake().setBodyNode(1, MAP_ROWS - 3, 5);
  model.getSnake().setBodyNode(2, MAP_ROWS - 4, 5);
  model.getSnake().setBodyNode(3, MAP_ROWS - 5, 5);
  EXPECT_EQ(ShiftState::MOVE, model.fsmShifting(RIGHT));
  EXPECT_EQ(RIGHT, model.getSnake().getDirect());
}

TEST(ModelTest9, fsmShiftingUp) {
  SnakeModel model;
  model.getApple().setPos(14, 2);
  model.getSnake().setDirect(LEFT);
  model.getSnake().setBodyNode(0, MAP_ROWS - 2, 4);
  model.getSnake().setBodyNode(1, MAP_ROWS - 2, 5);
  model.getSnake().setBodyNode(2, MAP_ROWS - 2, 6);
  model.getSnake().setBodyNode(3, MAP_ROWS - 2, 7);
  EXPECT_EQ(ShiftState::MOVE, model.fsmShifting(UP));
  EXPECT_EQ(UP, model.getSnake().getDirect());
}

TEST(ModelTest10, fsmShiftingDown) {
  SnakeModel model;
  model.getApple().setPos(4, 9);
  model.getSnake().setDirect(LEFT);
  model.getSnake().setBodyNode(0, MAP_ROWS - 8, 2);
  model.getSnake().setBodyNode(1, MAP_ROWS - 8, 3);
  model.getSnake().setBodyNode(2, MAP_ROWS - 8, 4);
  model.getSnake().setBodyNode(3, MAP_ROWS - 8, 5);
  EXPECT_EQ(ShiftState::MOVE, model.fsmShifting(DOWN));
  EXPECT_EQ(DOWN, model.getSnake().getDirect());
}

TEST(ModelTest11, fsmShiftingGameOver) {
  SnakeModel model;
  model.getApple().setPos(5, 2);
  model.getSnake().setDirect(LEFT);
  model.getSnake().setBodyNode(0, MAP_ROWS - 8, 0);
  model.getSnake().setBodyNode(1, MAP_ROWS - 8, 1);
  model.getSnake().setBodyNode(2, MAP_ROWS - 8, 2);
  model.getSnake().setBodyNode(3, MAP_ROWS - 8, 3);
  EXPECT_EQ(ShiftState::GMOVR, model.fsmShifting(STRAIGHT));
}

TEST(ModelTest12, fsmShiftingPlusStraight) {
  SnakeModel model;
  model.getApple().setPos(18, 0);
  model.getSnake().setDirect(LEFT);
  model.getSnake().setBodyNode(0, MAP_ROWS - 6, 1);
  model.getSnake().setBodyNode(1, MAP_ROWS - 6, 2);
  model.getSnake().setBodyNode(2, MAP_ROWS - 6, 3);
  model.getSnake().setBodyNode(3, MAP_ROWS - 6, 4);
  EXPECT_EQ(ShiftState::PLUS, model.fsmShifting(STRAIGHT));
  EXPECT_TRUE(model.fsmAdd());
  EXPECT_EQ(1, model.getGameInfo().score);
  EXPECT_EQ(1, model.getGameInfo().highScore);
  EXPECT_EQ(5, model.getSnake().getSize());
}

TEST(ModelTest13, fsmShiftingPlusUp) {
  SnakeModel model;
  model.getApple().setPos(17, 1);
  model.getSnake().setDirect(LEFT);
  model.getSnake().setBodyNode(0, MAP_ROWS - 6, 1);
  model.getSnake().setBodyNode(1, MAP_ROWS - 6, 2);
  model.getSnake().setBodyNode(2, MAP_ROWS - 6, 3);
  model.getSnake().setBodyNode(3, MAP_ROWS - 6, 4);
  EXPECT_EQ(ShiftState::PLUS, model.fsmShifting(UP));
  EXPECT_TRUE(model.fsmAdd());
  EXPECT_EQ(1, model.getGameInfo().score);
  EXPECT_EQ(1, model.getGameInfo().highScore);
  EXPECT_EQ(5, model.getSnake().getSize());
  EXPECT_EQ(UP, model.getSnake().getDirect());
}

TEST(ModelTest14, fsmAdd) {
  SnakeModel model;
  model.getApple().setPos(MAP_ROWS - 19, 5);
  model.getSnake().setDirect(UP);
  model.getSnake().setBodyNode(0, MAP_ROWS - 18, 5);
  model.getSnake().setBodyNode(1, MAP_ROWS - 17, 5);
  model.getSnake().setBodyNode(2, MAP_ROWS - 16, 5);
  model.getSnake().setBodyNode(3, MAP_ROWS - 15, 5);
  model.getSnake().setBodyNode(3, MAP_ROWS - 14, 5);
  model.getSnake().setBodyNode(3, MAP_ROWS - 13, 5);
  model.getSnake().setBodyNode(3, MAP_ROWS - 12, 5);
  model.getSnake().setBodyNode(3, MAP_ROWS - 11, 5);
  model.getSnake().setBodyNode(3, MAP_ROWS - 10, 5);
  model.getGameInfo().score = 4;
  model.getGameInfo().highScore = 4;
  model.getSnake().setSize(9);
  EXPECT_EQ(ShiftState::PLUS, model.fsmShifting(STRAIGHT));
  EXPECT_TRUE(model.fsmAdd());
  EXPECT_EQ(5, model.getGameInfo().score);
  EXPECT_EQ(5, model.getGameInfo().highScore);
  EXPECT_EQ(2, model.getGameInfo().level);
  EXPECT_EQ(2, model.getGameInfo().speed);
  EXPECT_EQ(10, model.getSnake().getSize());
  EXPECT_EQ(UP, model.getSnake().getDirect());
}

TEST(ModelTest15, fsmWin) {
  SnakeModel model;
  model.fsmWin();
  EXPECT_EQ(0, model.getGameInfo().showGameOverScreen);
  EXPECT_EQ(1, model.getGameInfo().showWinScreen);
  EXPECT_EQ(0, model.getGameInfo().showStartScreen);
}

TEST(ModelTest16, fsmGameOver) {
  SnakeModel model;
  model.fsmGameOver();
  EXPECT_EQ(1, model.getGameInfo().showGameOverScreen);
  EXPECT_EQ(0, model.getGameInfo().showWinScreen);
  EXPECT_EQ(0, model.getGameInfo().showStartScreen);
}

TEST(ModelTest17, fsmRestartGame) {
  SnakeModel model;
  model.getApple().setPos(MAP_ROWS - 19, 1);
  model.getSnake().setDirect(UP);
  model.getSnake().setBodyNode(0, MAP_ROWS - 18, 1);
  model.getSnake().setBodyNode(1, MAP_ROWS - 17, 1);
  model.getSnake().setBodyNode(2, MAP_ROWS - 16, 1);
  model.getSnake().setBodyNode(3, MAP_ROWS - 15, 1);
  model.getSnake().setBodyNode(3, MAP_ROWS - 14, 1);
  model.getSnake().setBodyNode(3, MAP_ROWS - 13, 1);
  model.getSnake().setBodyNode(3, MAP_ROWS - 12, 1);
  model.getGameInfo().score = 2;
  model.getSnake().setSize(7);
  if (std::filesystem::exists("high_score_snake.txt"))
    std::filesystem::remove("high_score_snake.txt");
  model.restartGame();
  EXPECT_EQ(4, model.getSnake().getSize());
  EXPECT_EQ(RIGHT, model.getSnake().getDirect());
  EXPECT_EQ(std::make_pair(MAP_ROWS - 1, MAP_COLS / 2 + 1),
            model.getSnake().getBody()[0]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 1, MAP_COLS / 2),
            model.getSnake().getBody()[1]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 1, MAP_COLS / 2 - 1),
            model.getSnake().getBody()[2]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 1, MAP_COLS / 2 - 2),
            model.getSnake().getBody()[3]);
  EXPECT_EQ(std::make_pair(0, 0), model.getApple().getPos());
  EXPECT_NE(nullptr, model.getGameInfo().field);
  EXPECT_NE(nullptr, model.getGameInfo().next);
  EXPECT_EQ(0, model.getGameInfo().score);
  EXPECT_EQ(0, model.getGameInfo().highScore);
  EXPECT_EQ(1, model.getGameInfo().level);
  EXPECT_EQ(0, model.getGameInfo().pause);
  EXPECT_EQ(0, model.getGameInfo().showStartScreen);
  EXPECT_EQ(0, model.getGameInfo().showGameOverScreen);
  EXPECT_EQ(0, model.getGameInfo().showWinScreen);
  for (int r = 0; r < QUADR; r++) {
    for (int c = 0; c < QUADR; c++) {
      EXPECT_EQ(0, model.getGameInfo().next[r][c]);
    }
  }
}

TEST(ModelTest18, copyConstructor) {
  SnakeModel model;
  model.getApple().setPos(MAP_ROWS - 15, 6);
  model.getSnake().setDirect(RIGHT);
  model.setState(SnakeFsmState_t::INPUT);
  model.getSnake().setSize(5);
  model.getSnake().setBodyNode(0, MAP_ROWS - 18, 0);
  model.getSnake().setBodyNode(1, MAP_ROWS - 17, 0);
  model.getSnake().setBodyNode(2, MAP_ROWS - 16, 0);
  model.getSnake().setBodyNode(3, MAP_ROWS - 15, 0);
  model.getSnake().setBodyNode(4, MAP_ROWS - 14, 0);
  model.getGameInfo().showStartScreen = 0;
  model.getGameInfo().score = 1;
  model.getGameInfo().highScore = 0;
  SnakeModel copyModel(model);
  EXPECT_EQ(SnakeFsmState_t::INPUT, copyModel.getState());
  EXPECT_EQ(5, copyModel.getSnake().getSize());
  EXPECT_EQ(RIGHT, copyModel.getSnake().getDirect());
  EXPECT_EQ(std::make_pair(MAP_ROWS - 18, 0),
            copyModel.getSnake().getBody()[0]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 17, 0),
            copyModel.getSnake().getBody()[1]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 16, 0),
            copyModel.getSnake().getBody()[2]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 15, 0),
            copyModel.getSnake().getBody()[3]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 14, 0),
            copyModel.getSnake().getBody()[4]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 15, 6), copyModel.getApple().getPos());
  EXPECT_EQ(1, copyModel.getGameInfo().score);
  EXPECT_EQ(0, copyModel.getGameInfo().highScore);
  EXPECT_EQ(1, copyModel.getGameInfo().level);
  EXPECT_EQ(0, copyModel.getGameInfo().pause);
  EXPECT_EQ(0, copyModel.getGameInfo().showStartScreen);
  EXPECT_EQ(0, copyModel.getGameInfo().showGameOverScreen);
  EXPECT_EQ(0, copyModel.getGameInfo().showWinScreen);
}

TEST(ModelTest19, moveConstructor) {
  SnakeModel model;
  model.getApple().setPos(MAP_ROWS - 7, 6);
  model.getSnake().setDirect(RIGHT);
  model.setState(SnakeFsmState_t::INPUT);
  model.getSnake().setSize(5);
  model.getSnake().setBodyNode(0, MAP_ROWS - 14, 9);
  model.getSnake().setBodyNode(1, MAP_ROWS - 13, 9);
  model.getSnake().setBodyNode(2, MAP_ROWS - 12, 9);
  model.getSnake().setBodyNode(3, MAP_ROWS - 11, 9);
  model.getSnake().setBodyNode(4, MAP_ROWS - 10, 9);
  model.getGameInfo().showStartScreen = 0;
  model.getGameInfo().score = 1;
  SnakeModel copyModel(std::move(model));
  EXPECT_EQ(SnakeFsmState_t::INPUT, copyModel.getState());
  EXPECT_EQ(5, copyModel.getSnake().getSize());
  EXPECT_EQ(RIGHT, copyModel.getSnake().getDirect());
  EXPECT_EQ(std::make_pair(MAP_ROWS - 14, 9),
            copyModel.getSnake().getBody()[0]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 13, 9),
            copyModel.getSnake().getBody()[1]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 12, 9),
            copyModel.getSnake().getBody()[2]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 11, 9),
            copyModel.getSnake().getBody()[3]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 10, 9),
            copyModel.getSnake().getBody()[4]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 7, 6), copyModel.getApple().getPos());
  EXPECT_EQ(1, copyModel.getGameInfo().score);
  EXPECT_EQ(0, copyModel.getGameInfo().highScore);
  EXPECT_EQ(1, copyModel.getGameInfo().level);
  EXPECT_EQ(0, copyModel.getGameInfo().pause);
  EXPECT_EQ(0, copyModel.getGameInfo().showStartScreen);
  EXPECT_EQ(0, copyModel.getGameInfo().showGameOverScreen);
  EXPECT_EQ(0, copyModel.getGameInfo().showWinScreen);
}

TEST(ModelTest20, copyAssignOperator) {
  SnakeModel model;
  model.getApple().setPos(MAP_ROWS - 18, 7);
  model.getSnake().setDirect(LEFT);
  model.setState(SnakeFsmState_t::INPUT);
  model.getSnake().setSize(6);
  model.getSnake().setBodyNode(0, MAP_ROWS - 14, 4);
  model.getSnake().setBodyNode(1, MAP_ROWS - 13, 4);
  model.getSnake().setBodyNode(2, MAP_ROWS - 12, 4);
  model.getSnake().setBodyNode(3, MAP_ROWS - 11, 4);
  model.getSnake().setBodyNode(4, MAP_ROWS - 10, 4);
  model.getSnake().setBodyNode(5, MAP_ROWS - 9, 4);
  model.getGameInfo().showStartScreen = 0;
  model.getGameInfo().score = 1;
  model.getGameInfo().highScore = 1;
  SnakeModel copyModel;
  copyModel = model;
  EXPECT_EQ(SnakeFsmState_t::INPUT, copyModel.getState());
  EXPECT_EQ(6, copyModel.getSnake().getSize());
  EXPECT_EQ(LEFT, copyModel.getSnake().getDirect());
  EXPECT_EQ(std::make_pair(MAP_ROWS - 14, 4),
            copyModel.getSnake().getBody()[0]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 13, 4),
            copyModel.getSnake().getBody()[1]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 12, 4),
            copyModel.getSnake().getBody()[2]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 11, 4),
            copyModel.getSnake().getBody()[3]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 10, 4),
            copyModel.getSnake().getBody()[4]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 9, 4), copyModel.getSnake().getBody()[5]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 18, 7), copyModel.getApple().getPos());
  EXPECT_EQ(1, copyModel.getGameInfo().score);
  EXPECT_EQ(1, copyModel.getGameInfo().highScore);
  EXPECT_EQ(1, copyModel.getGameInfo().level);
  EXPECT_EQ(0, copyModel.getGameInfo().pause);
  EXPECT_EQ(0, copyModel.getGameInfo().showStartScreen);
  EXPECT_EQ(0, copyModel.getGameInfo().showGameOverScreen);
  EXPECT_EQ(0, copyModel.getGameInfo().showWinScreen);
}

TEST(ModelTest21, moveAssignOperator) {
  SnakeModel model;
  model.getApple().setPos(MAP_ROWS - 4, 3);
  model.getSnake().setDirect(UP);
  model.setState(SnakeFsmState_t::INPUT);
  model.getSnake().setSize(5);
  model.getSnake().setBodyNode(0, MAP_ROWS - 10, 4);
  model.getSnake().setBodyNode(1, MAP_ROWS - 9, 4);
  model.getSnake().setBodyNode(2, MAP_ROWS - 8, 4);
  model.getSnake().setBodyNode(3, MAP_ROWS - 7, 4);
  model.getSnake().setBodyNode(4, MAP_ROWS - 6, 4);
  model.getGameInfo().showStartScreen = 0;
  model.getGameInfo().score = 1;
  SnakeModel copyModel;
  copyModel = std::move(model);
  EXPECT_EQ(SnakeFsmState_t::INPUT, copyModel.getState());
  EXPECT_EQ(5, copyModel.getSnake().getSize());
  EXPECT_EQ(UP, copyModel.getSnake().getDirect());
  EXPECT_EQ(std::make_pair(MAP_ROWS - 10, 4),
            copyModel.getSnake().getBody()[0]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 9, 4), copyModel.getSnake().getBody()[1]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 8, 4), copyModel.getSnake().getBody()[2]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 7, 4), copyModel.getSnake().getBody()[3]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 6, 4), copyModel.getSnake().getBody()[4]);
  EXPECT_EQ(std::make_pair(MAP_ROWS - 4, 3), copyModel.getApple().getPos());
  EXPECT_EQ(1, copyModel.getGameInfo().score);
  EXPECT_EQ(0, copyModel.getGameInfo().highScore);
  EXPECT_EQ(1, copyModel.getGameInfo().level);
  EXPECT_EQ(0, copyModel.getGameInfo().pause);
  EXPECT_EQ(0, copyModel.getGameInfo().showStartScreen);
  EXPECT_EQ(0, copyModel.getGameInfo().showGameOverScreen);
  EXPECT_EQ(0, copyModel.getGameInfo().showWinScreen);

  if (std::filesystem::exists("high_score_snake.txt"))
    std::filesystem::remove("high_score_snake.txt");
}

TEST(ModelTest22, setNoPause) {
  SnakeModel model;
  model.gameInfo_.pause = 1;
  model.setNoPause();
  EXPECT_EQ(0, model.getGameInfo().pause);
}