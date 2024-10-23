#include "buttons.h"

using namespace s21;

Buttons::Buttons(MainWindow* mainWindow)
    : QWidget(mainWindow),
      game(SnakeG),
      isInGame(false),
      mainWindow_(mainWindow),
      holdTimer(new QTimer(this)) {
  setFixedSize(505, 230);
  exitButton = new QPushButton("Exit", this);
  startButton = new QPushButton("Start", this);
  pauseButton = new QPushButton("Pause", this);
  upButton = new QPushButton("Up", this);
  upButton->setText(QChar(0x25B2));
  leftButton = new QPushButton("Left", this);
  leftButton->setText(QChar(0x25C0));
  rightButton = new QPushButton("Right", this);
  rightButton->setText(QChar(0x25B6));
  downButton = new QPushButton("Down", this);
  downButton->setText(QChar(0x25BC));
  actionButton = new QPushButton("Action", this);
  holdTimer->setInterval(100);
  exitButton->setStyleSheet(buttonStyleRed());
  startButton->setStyleSheet(buttonStyleOrange());
  pauseButton->setStyleSheet(buttonStyleLightBlue());
  upButton->setStyleSheet(buttonStyleBlue());
  leftButton->setStyleSheet(buttonStyleBlue());
  rightButton->setStyleSheet(buttonStyleBlue());
  actionButton->setStyleSheet(buttonStylePink());
  downButton->setStyleSheet(buttonStyleBlue());
  layout = new QGridLayout(this);
  layout->addWidget(exitButton, 0, 0);
  layout->addWidget(startButton, 0, 1);
  layout->addWidget(pauseButton, 0, 2);
  int buttonHeight = startButton->sizeHint().height() / 4;
  QSpacerItem* verticalSpacer = new QSpacerItem(
      0, buttonHeight, QSizePolicy::Minimum, QSizePolicy::Fixed);
  layout->addItem(verticalSpacer, 1, 0, 1, 3);
  layout->addWidget(upButton, 2, 1);
  layout->addWidget(leftButton, 3, 0);
  layout->addWidget(rightButton, 3, 2);
  layout->addWidget(downButton, 4, 1);
  layout->addWidget(actionButton, 3, 3);
  setLayout(layout);
  connect(upButton, &QPushButton::clicked, this, &Buttons::moveUp);
  connect(downButton, &QPushButton::clicked, this, &Buttons::moveDown);
  connect(startButton, &QPushButton::clicked, mainWindow_,
          &MainWindow::startGame);
  connect(exitButton, &QPushButton::clicked, this, &Buttons::exitGame);
}

QString Buttons::buttonStyleBlue() {
  return R"(
    QPushButton {
        border:none;
        border-radius:15px;
        background-color:#00A7A0;
        color:#FFFFFF;
        min-width:25px;
        min-height:25px;
        max-width:100px;
        max-height:25px;
        text-align:center;
        font: 700 15pt "Chalkboard";
        border: 4px solid #00918b;
        border-bottom: 4px solid #00918b;
        border-right: 4px solid #00918b;
        padding: 5px;
    }

    QPushButton:hover {
        background-color:#00918b;
    }

    QPushButton:pressed {
        background-color:#006661;
    }
    )";
}

QString Buttons::buttonStyleRed() {
  return R"(
    QPushButton {
        border:none;
        border-radius:15px;
        background-color:#ff333d;
        color:#FFFFFF;
        min-width:25px;
        min-height:25px;
        max-width:100px;
        max-height:25px;
        text-align:center;
        font: 700 15pt "Chalkboard";
        border: 4px solid #de2b34;
        border-bottom: 4px solid #de2b34;
        border-right: 4px solid #de2b34;
        padding: 5px;
    }

    QPushButton:hover {
        background-color:#de2b34;
    }

    QPushButton:pressed {
        background-color:#9e1c22;
    }
    )";
}

QString Buttons::buttonStyleOrange() {
  return R"(
    QPushButton {
        border:none;
        border-radius:15px;
        background-color:#ffb072;
        color:#FFFFFF;
        min-width:25px;
        min-height:25px;
        max-width:100px;
        max-height:25px;
        text-align:center;
        font: 700 15pt "Chalkboard";
        border: 4px solid #de9962;
        border-bottom: 4px solid #de9962;
        border-right: 4px solid #de9962;
        padding: 5px;
    }

    QPushButton:hover {
        background-color:#de9962;
    }

    QPushButton:pressed {
        background-color:#9e6c44;
    }
    )";
}

QString Buttons::buttonStyleLightBlue() {
  return R"(
    QPushButton {
        border:none;
        border-radius:15px;
        background-color:#72c2ff;
        color:#FFFFFF;
        min-width:25px;
        min-height:25px;
        max-width:100px;
        max-height:25px;
        text-align:center;
        font: 700 15pt "Chalkboard";
        border: 4px solid #62a8de;
        border-bottom: 4px solid #62a8de;
        border-right: 4px solid #62a8de;
        padding: 5px;
    }

    QPushButton:hover {
        background-color:#53b5ff;
    }

    QPushButton:pressed {
        background-color:#008cf6;
    }
    )";
}

QString Buttons::buttonStylePink() {
  return R"(
    QPushButton {
        border:none;
        border-radius:15px;
        background-color:#ffb0b4;
        color:#FFFFFF;
        min-width:25px;
        min-height:25px;
        max-width:100px;
        max-height:25px;
        text-align:center;
        font: 700 15pt "Chalkboard";
        border: 4px solid #de999c;
        border-bottom: 4px solid #de999c;
        border-right: 4px solid #de999c;
        padding: 5px;
    }

    QPushButton:hover {
        background-color:#de999c;
    }

    QPushButton:pressed {
        background-color:#805658;
    }
    )";
}

void Buttons::paintEvent(QPaintEvent* e) {
  Q_UNUSED(e)
  QPainter painter(this);
  QPen pen(SELECTED_COLOR);
  pen.setWidth(8);
  painter.setPen(pen);
  painter.drawRect(1, 1, width() - 2, height() - 2);
  painter.setPen(BLACK_COLOR);
  QFont smallFont("Chalkboard", 10, QFont::Bold);
  painter.setFont(smallFont);
  QFontMetrics fm(painter.font());
  int lineHeight = fm.height();

  int textWidth = fm.horizontalAdvance("\"Esc\" - exit");
  int textX = width() - textWidth * 1.65;
  int textY = pauseButton->y();

  painter.drawText(QRect(textX, textY, textWidth * 2, lineHeight),
                   "\"Esc\" - exit");
  painter.drawText(QRect(textX, textY + lineHeight, textWidth * 2, lineHeight),
                   "\"Enter\" - start");
  painter.drawText(
      QRect(textX, textY + lineHeight * 2, textWidth * 2, lineHeight),
      "\"P\" - pause");
  painter.drawText(
      QRect(textX, textY + lineHeight * 3, textWidth * 2, lineHeight),
      "\"Space\" - action");
}

void Buttons::setInGame() {
  isInGame = !isInGame;
  if (isInGame)
    connectInGame();
  else
    connectNoGame();
}

void Buttons::connectInGame() {
  disconnect(startButton, &QPushButton::clicked, mainWindow_,
             &MainWindow::startGame);
  connect(startButton, &QPushButton::clicked, mainWindow_,
          &MainWindow::actionStart);

  disconnect(upButton, &QPushButton::clicked, this, &Buttons::moveUp);
  connect(upButton, &QPushButton::clicked, mainWindow_, &MainWindow::actionUp);
  disconnect(downButton, &QPushButton::clicked, this, &Buttons::moveDown);
  if (game == SnakeG) {
    connect(downButton, &QPushButton::clicked, mainWindow_,
            &MainWindow::actionDown);
  } else if (game == TetrisG) {
    connect(holdTimer, &QTimer::timeout, mainWindow_, &MainWindow::actionDown);
    connect(downButton, &QPushButton::pressed, this, &Buttons::startHold);
    connect(downButton, &QPushButton::released, this, &Buttons::stopHold);
  }
  disconnect(exitButton, &QPushButton::clicked, this, &Buttons::exitGame);
  connect(exitButton, &QPushButton::clicked, mainWindow_,
          &MainWindow::actionExit);
  connect(leftButton, &QPushButton::clicked, mainWindow_,
          &MainWindow::actionLeft);
  connect(rightButton, &QPushButton::clicked, mainWindow_,
          &MainWindow::actionRight);
  connect(pauseButton, &QPushButton::clicked, mainWindow_,
          &MainWindow::actionPause);
  if (game == SnakeG) {
    connect(holdTimer, &QTimer::timeout, mainWindow_,
            &MainWindow::actionAction);
    connect(actionButton, &QPushButton::pressed, this, &Buttons::startHold);
    connect(actionButton, &QPushButton::released, this, &Buttons::stopHold);
  } else if (game == TetrisG) {
    connect(actionButton, &QPushButton::clicked, mainWindow_,
            &MainWindow::actionAction);
  }
}

void Buttons::connectNoGame() {
  disconnect(startButton, &QPushButton::clicked, mainWindow_,
             &MainWindow::actionStart);
  connect(startButton, &QPushButton::clicked, mainWindow_,
          &MainWindow::startGame);
  disconnect(upButton, &QPushButton::clicked, mainWindow_,
             &MainWindow::actionUp);
  connect(upButton, &QPushButton::clicked, this, &Buttons::moveUp);
  disconnect(holdTimer, &QTimer::timeout, mainWindow_, &MainWindow::actionDown);
  disconnect(downButton, &QPushButton::pressed, this, &Buttons::startHold);
  disconnect(downButton, &QPushButton::released, this, &Buttons::stopHold);
  disconnect(downButton, &QPushButton::clicked, mainWindow_,
             &MainWindow::actionDown);
  connect(downButton, &QPushButton::clicked, this, &Buttons::moveDown);
  disconnect(exitButton, &QPushButton::clicked, mainWindow_,
             &MainWindow::actionExit);
  connect(exitButton, &QPushButton::clicked, this, &Buttons::exitGame);
  disconnect(leftButton, &QPushButton::clicked, mainWindow_,
             &MainWindow::actionLeft);
  disconnect(rightButton, &QPushButton::clicked, mainWindow_,
             &MainWindow::actionRight);
  disconnect(pauseButton, &QPushButton::clicked, mainWindow_,
             &MainWindow::actionPause);
  disconnect(actionButton, &QPushButton::pressed, mainWindow_,
             &MainWindow::actionAction);
  disconnect(holdTimer, &QTimer::timeout, mainWindow_,
             &MainWindow::actionAction);
  disconnect(actionButton, &QPushButton::pressed, this, &Buttons::startHold);
  disconnect(actionButton, &QPushButton::released, this, &Buttons::stopHold);
}

void Buttons::moveUp() {
  if (game == SnakeG)
    game = GAMES_NUMB;
  else
    --game;
  emit gameChanged(game);
}

void Buttons::moveDown() {
  if (game == GAMES_NUMB)
    game = SnakeG;
  else
    ++game;
  emit gameChanged(game);
}

void Buttons::exitGame() { emit exitSelected(); }

void Buttons::startHold() { holdTimer->start(); }

void Buttons::stopHold() { holdTimer->stop(); }
