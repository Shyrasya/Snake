#include "snake_controller.h"

using namespace s21;

void SnakeController::userInput(UserAction_t action, bool hold) {
  using SFS = SnakeFsmState_t;
  using Clock = std::chrono::steady_clock;
  using TimePoint = std::chrono::time_point<Clock>;
  static SnakeDirection shiftAction;
  static TimePoint lastTime = Clock::now(), curTime;
  SFS state = model_->getState();
  checkPreInput(hold, state);
  switch (state) {
    case SFS::START: {
      checkSwitch(action, hold);
      break;
    }
    case SFS::SPAWN: {
      controlSpawn(shiftAction, lastTime);
      break;
    }
    case SFS::INPUT: {
      curTime = Clock::now();
      std::chrono::duration<long double> elapsed = curTime - lastTime;
      if (hold || preInputPress) controlInput(shiftAction, action);
      double delay = SEC - SEC_DEC * model_->getGameInfo().speed + SEC_DEC;
      if (elapsed.count() >= delay) model_->setState(SFS::SHIFTING);
      break;
    }
    case SFS::SHIFTING: {
      controlShift(shiftAction, lastTime);
      break;
    }
    case SFS::ADD: {
      controlAdd();
      break;
    }
    case SFS::PAUSE: {
      if (hold) controlPause(action, lastTime);
      break;
    }
    case SFS::WIN: {
      controlWin(action, hold);
      break;
    }
    case SFS::GAMEOVER: {
      controlGameOver(action, hold);
      break;
    }
    case SFS::EXIT_STATE: {
      break;
    }
  }
}

void SnakeController::checkPreInput(bool hold, SnakeFsmState_t state) {
  using SFS = SnakeFsmState_t;
  if (hold &&
      (state == SFS::SPAWN || state == SFS::SHIFTING || state == SFS::ADD))
    preInputPress = true;
}

SnakeDirection SnakeController::exchange(UserAction_t action) {
  SnakeDirection exc = LEFT;
  if (action == Left)
    exc = LEFT;
  else if (action == Right)
    exc = RIGHT;
  else if (action == Up)
    exc = UP;
  else if (action == Down)
    exc = DOWN;
  return exc;
}

void SnakeController::checkSwitch(UserAction_t action, bool hold) {
  using SFS = SnakeFsmState_t;
  model_->getGameInfo().readHighScore();
  if (action == Terminate && hold)
    model_->setState(SFS::EXIT_STATE);
  else if (action == Start && hold) {
    model_->restartGame();
    model_->setState(SFS::SPAWN);
  }
}

void SnakeController::controlSpawn(SnakeDirection &shiftAction,
                                   TimePoint &lastTime) {
  using SFS = SnakeFsmState_t;
  model_->getGameInfo().writeHighScore();
  model_->fsmSpawn();
  shiftAction = STRAIGHT;
  model_->setState(SFS::INPUT);
  lastTime = Clock::now();
}

void SnakeController::controlInput(SnakeDirection &shiftAction,
                                   UserAction_t action) {
  using SFS = SnakeFsmState_t;
  if (action == Terminate)
    model_->setState(SFS::EXIT_STATE);
  else if (action == Pause) {
    model_->setPause();
    model_->setState(SFS::PAUSE);
  } else if (action == Action) {
    shiftAction = STRAIGHT;
    model_->setState(SFS::SHIFTING);
  } else if (action == Left || action == Right || action == Up ||
             action == Down) {
    SnakeDirection inputAction = exchange(action);
    if (model_->validInput(inputAction)) shiftAction = exchange(action);
  }
  preInputPress = false;
}

void SnakeController::controlShift(SnakeDirection &shiftAction,
                                   TimePoint &lastTime) {
  using SFS = SnakeFsmState_t;
  using SS = ShiftState;
  int shiftState = model_->fsmShifting(shiftAction);
  if (shiftState == SS::MOVE) {
    model_->setState(SFS::INPUT);
    shiftAction = STRAIGHT;
    lastTime = Clock::now();
  } else if (shiftState == SS::PLUS)
    model_->setState(SFS::ADD);
  else
    model_->setState(SFS::GAMEOVER);
}

void SnakeController::controlAdd() {
  using SFS = SnakeFsmState_t;
  if (model_->fsmAdd())
    model_->setState(SFS::SPAWN);
  else
    model_->setState(SFS::WIN);
}

void SnakeController::controlPause(UserAction_t action, TimePoint &lastTime) {
  using SFS = SnakeFsmState_t;
  if (action == Terminate)
    model_->setState(SFS::EXIT_STATE);
  else if (action == Pause) {
    model_->setNoPause();
    model_->setState(SFS::INPUT);
    lastTime = Clock::now();
  }
}

void SnakeController::controlWin(UserAction_t action, bool hold) {
  model_->fsmWin();
  checkSwitch(action, hold);
}

void SnakeController::controlGameOver(UserAction_t action, bool hold) {
  model_->fsmGameOver();
  checkSwitch(action, hold);
}

s21::GameInfo_t SnakeController::updateCurrentState() {
  return model_->getGameInfo();
}
