#include "mainwindow.h"

#include <clocale>

using namespace s21;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      snModel(nullptr),
      snController(nullptr),
      desktopView(nullptr),
      isInGame(false),
      game(SnakeG) {
  setFixedSize(524, 772);
  QPalette palette = this->palette();
  palette.setColor(QPalette::Window, QColor("#d0e17e"));
  this->setAutoFillBackground(true);
  this->setPalette(palette);

  m_centralWidget = new QWidget();
  m_gridLayout = new QGridLayout(m_centralWidget);
  m_gameField = new GameField();
  m_helpField = new HelpField();

  m_buttons = new Buttons(this);
  m_gridLayout->addWidget(m_gameField, 0, 0);
  m_gridLayout->addWidget(m_helpField, 0, 1);
  m_gridLayout->addWidget(m_buttons, 1, 0, 1, 2);
  m_centralWidget->setLayout(m_gridLayout);

  m_buttons->upButton->setFocusPolicy(Qt::NoFocus);
  m_buttons->downButton->setFocusPolicy(Qt::NoFocus);
  m_buttons->leftButton->setFocusPolicy(Qt::NoFocus);
  m_buttons->rightButton->setFocusPolicy(Qt::NoFocus);
  m_buttons->startButton->setFocusPolicy(Qt::NoFocus);
  m_buttons->exitButton->setFocusPolicy(Qt::NoFocus);
  m_buttons->pauseButton->setFocusPolicy(Qt::NoFocus);
  m_buttons->actionButton->setFocusPolicy(Qt::NoFocus);

  connect(m_buttons, &Buttons::gameChanged, m_gameField,
          &GameField::setSelectedGame);
  connect(m_buttons, &Buttons::gameChanged, m_helpField,
          &HelpField::setSelectedGame);
  connect(m_buttons, &Buttons::gameChanged, this, &MainWindow::setSelectedGame);
  connect(m_buttons, &Buttons::exitSelected, this, &MainWindow::close);
  connect(this, &MainWindow::modeChange, m_buttons, &Buttons::setInGame);
  connect(this, &MainWindow::modeChange, m_gameField, &GameField::setInGame);
  connect(this, &MainWindow::modeChange, m_helpField, &HelpField::setInGame);

  setCentralWidget(m_centralWidget);
  this->setFocus();
}

MainWindow::~MainWindow() { exitGame(); }

void MainWindow::setInGame() { isInGame = !isInGame; }

void MainWindow::keyPressEvent(QKeyEvent *e) {
  if (isInGame) {
    handleGameKeys(e);
  } else {
    handleMenuKeys(e);
  }
}

void MainWindow::handleMenuKeys(QKeyEvent *e) {
  if (e->key() == Qt::Key_Up)
    m_buttons->moveUp();
  else if (e->key() == Qt::Key_Down)
    m_buttons->moveDown();
  else if (e->key() == Qt::Key_Escape)
    m_buttons->exitGame();
  else if (e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return)
    startGame();
}

void MainWindow::handleGameKeys(QKeyEvent *e) {
  if (e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return) {
    desktopView->action = Start;
    desktopView->hold = true;
  } else if (e->key() == Qt::Key_Up) {
    desktopView->action = Up;
    desktopView->hold = true;
  } else if (e->key() == Qt::Key_Down) {
    desktopView->action = Down;
    desktopView->hold = true;
  } else if (e->key() == Qt::Key_Left) {
    desktopView->action = Left;
    desktopView->hold = true;
  } else if (e->key() == Qt::Key_Right) {
    desktopView->action = Right;
    desktopView->hold = true;
  } else if (e->key() == Qt::Key_Space) {
    desktopView->action = Action;
    desktopView->hold = true;
  } else if (e->key() == Qt::Key_P) {
    desktopView->action = Pause;
    desktopView->hold = true;
  } else if (e->key() == Qt::Key_Escape) {
    desktopView->action = Terminate;
    desktopView->hold = true;
  } else
    desktopView->hold = false;
}

void MainWindow::startGame() {
  if (game == SnakeG)
    startSnakeGame();
  else if (game == TetrisG)
    startTetrisGame();
}

void MainWindow::startSnakeGame() {
  snModel = new SnakeModel();
  snController = new SnakeController(snModel);
  desktopView = new DesktopView(this, snController);

  isInGame = true;
  emit modeChange();
  desktopView->startDesktopSnakeEventLoop();
}

void MainWindow::startTetrisGame() {
  desktopView = new DesktopView(this, nullptr);
  isInGame = true;
  emit modeChange();
  desktopView->startDesktopTetrisEventLoop();
}

void MainWindow::exitGame() {
  if (desktopView) {
    desktopView->timer_->stop();
    delete desktopView;
    desktopView = nullptr;
    if (snController) {
      delete snController;
      snController = nullptr;
    }
    if (snModel) {
      delete snModel;
      snModel = nullptr;
    }
  }
  isInGame = false;
  emit modeChange();
}

void MainWindow::actionUp() {
  desktopView->action = Up;
  desktopView->hold = true;
}

void MainWindow::actionDown() {
  desktopView->action = Down;
  desktopView->hold = true;
}

void MainWindow::actionLeft() {
  desktopView->action = Left;
  desktopView->hold = true;
}

void MainWindow::actionRight() {
  desktopView->action = Right;
  desktopView->hold = true;
}

void MainWindow::actionStart() {
  desktopView->action = Start;
  desktopView->hold = true;
}

void MainWindow::actionExit() {
  desktopView->action = Terminate;
  desktopView->hold = true;
  isInGame = false;
}

void MainWindow::actionPause() {
  desktopView->action = Pause;
  desktopView->hold = true;
}

void MainWindow::actionAction() {
  desktopView->action = Action;
  desktopView->hold = true;
}

void MainWindow::setSelectedGame(int selectedGame) { game = selectedGame; }
