#include "desktopview.h"

using namespace s21;

DesktopView::DesktopView(MainWindow* mainWindow, SnakeController* controller)
    : mainWindow_(mainWindow), controller_(controller) {
  timer_ = new QTimer(this);
  connect(this, &DesktopView::modeChange, mainWindow_->m_gameField,
          &GameField::setInGame);
  connect(this, &DesktopView::modeChange, mainWindow_, &MainWindow::setInGame);
  connect(this, &DesktopView::modeChange, mainWindow_->m_helpField,
          &HelpField::setInGame);
  connect(this, &DesktopView::modeChange, mainWindow_->m_buttons,
          &Buttons::setInGame);
  connect(this, &DesktopView::exitGame, mainWindow_, &MainWindow::exitGame);
}

void DesktopView::startDesktopSnakeEventLoop() {
  disconnect(timer_, &QTimer::timeout, nullptr, nullptr);
  connect(timer_, &QTimer::timeout, this, &DesktopView::gameSnakeLoop);

  action = Start;
  hold = false;

  mainWindow_->m_helpField->gameInfo.readHighScore();

  printDesktopStatist(controller_->updateCurrentState());
  timer_->start(100);
}

void DesktopView::gameSnakeLoop() {
  controller_->userInput(action, hold);
  printDesktopStatist(controller_->updateCurrentState());
  hold = false;
  if (action == Terminate) {
    emit exitGame();
  }
}

void DesktopView::startDesktopTetrisEventLoop() {
  disconnect(timer_, &QTimer::timeout, nullptr, nullptr);
  connect(timer_, &QTimer::timeout, this, &DesktopView::gameTetrisLoop);
  action = Start;
  hold = false;
  fsmState = START;
  printDesktopStatist(transBack(&fsmState));
  timer_->start(100);
}

void DesktopView::gameTetrisLoop() {
  printDesktopStatist(translateInfoFront(&fsmState, &action, &hold));
  hold = false;
  if (action == Terminate) {
    statClose();
    emit exitGame();
  }
}

void DesktopView::printDesktopStatist(const s21::GameInfo_t& gameInfo) {
  mainWindow_->m_gameField->gameSetGameInfo(gameInfo);
  mainWindow_->m_helpField->helpSetGameInfo(gameInfo);
  updateView();
}

void DesktopView::updateView() {
  mainWindow_->m_gameField->update();
  mainWindow_->m_helpField->update();
}
