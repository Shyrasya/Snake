#include "game.h"

using namespace s21;

GameField::GameField(QWidget *parent)
    : QWidget(parent), selectedGame(SnakeG), isInGame(false) {
  setFixedSize(266, HEIGHT);
  QPalette palette = this->palette();
  palette.setColor(QPalette::Window, WHITE_COLOR);
  this->setAutoFillBackground(true);
  this->setPalette(palette);
}

void GameField::paintEvent(QPaintEvent *e) {
  Q_UNUSED(e)
  QPainter painter(this);
  QPen pen(SELECTED_COLOR);
  pen.setWidth(8);
  painter.setPen(pen);
  painter.drawRect(1, 1, width() - 2, HEIGHT - 2);

  if (!isInGame) {
    clearField(painter);
    printChoice(painter);

  } else {
    if (gameInfo.showStartScreen) {
      clearField(painter);
      printNameStart(painter);
      printStart(painter);
    } else if (gameInfo.showGameOverScreen) {
      clearField(painter);
      printGameOver(painter);
      printStart(painter);
    } else if (gameInfo.showWinScreen) {
      clearField(painter);
      printWinScreen(painter);
      printStart(painter);
    } else
      printField(painter);
  }
}

void GameField::clearField(QPainter &painter) {
  int widthInner = width() - 2 * borderThickness;
  int heightInner = HEIGHT - 2 * borderThickness;
  painter.setBrush(WHITE_COLOR);
  painter.fillRect(X_START, X_START, widthInner, heightInner, painter.brush());
}

void GameField::printChoice(QPainter &painter) {
  int ySnake = HEIGHT / 3;
  int yTetris = HEIGHT / 2;

  if (selectedGame == SnakeG) {
    painter.setFont(SELECTED_FONT);
    painter.setPen(SELECTED_COLOR);
    painter.drawText(QRect(0, ySnake, width(), 50), Qt::AlignCenter, "SNAKE");

    painter.setFont(NORMAL_FONT);
    painter.setPen(BLACK_COLOR);
    painter.drawText(QRect(0, yTetris, width(), 50), Qt::AlignCenter, "TETRIS");

  } else {
    painter.setFont(NORMAL_FONT);
    painter.setPen(BLACK_COLOR);
    painter.drawText(QRect(0, ySnake, width(), 50), Qt::AlignCenter, "SNAKE");
    painter.setFont(SELECTED_FONT);
    painter.setPen(SELECTED_COLOR);
    painter.drawText(QRect(0, yTetris, width(), 50), Qt::AlignCenter, "TETRIS");
  }
}

void GameField::printNameStart(QPainter &painter) {
  painter.setFont(SELECTED_FONT);
  painter.setPen(SELECTED_COLOR);
  if (selectedGame == SnakeG)
    painter.drawText(QRect(0, HEIGHT / 3, width(), 50), Qt::AlignCenter,
                     "SNAKE");
  else if (selectedGame == TetrisG)
    painter.drawText(QRect(0, HEIGHT / 3, width(), 50), Qt::AlignCenter,
                     "TETRIS");
}

void GameField::printStart(QPainter &painter) {
  painter.setFont(SMALL_FONT);
  painter.setPen(BLACK_COLOR);
  painter.drawText(QRect(0, HEIGHT / 1.8, width(), 50), Qt::AlignCenter,
                   "Press \"Enter\" to Start");
}

void GameField::printGameOver(QPainter &painter) {
  painter.setFont(SELECTED_FONT);
  painter.setPen(SELECTED_COLOR);
  painter.drawText(QRect(0, HEIGHT / 3, width(), 50), Qt::AlignCenter,
                   "Game Over");
  painter.drawText(QRect(0, HEIGHT / 2.3, width(), 50), Qt::AlignCenter, "o_O");
}

void GameField::printWinScreen(QPainter &painter) {
  painter.setFont(SELECTED_FONT);
  painter.setPen(SELECTED_COLOR);
  painter.drawText(QRect(0, HEIGHT / 3, width(), 50), Qt::AlignCenter,
                   "You Win");
  painter.drawText(QRect(0, HEIGHT / 2.3, width(), 50), Qt::AlignCenter, "^_^");
}

void GameField::printField(QPainter &painter) {
  int squareSize = 25;
  int startX = 8;
  int startY = 8;
  for (int r = 4; r < MAP_ROWS; r++) {
    for (int c = 0; c < MAP_COLS; c++) {
      int x = startX + c * squareSize;
      int y = startY + (r - 4) * squareSize;

      switch (gameInfo.field[r][c]) {
        case 0:
          painter.setBrush(WHITE_COLOR);
          break;
        case 1:
        case 2:
          painter.setBrush(SNAKEBODY_COLOR);
          break;
        case 3:
          painter.setBrush(SELECTED_COLOR);
          break;
        case 4:
          painter.setBrush(APPLE_COLOR);
          break;
      }
      painter.fillRect(x, y, squareSize, squareSize, painter.brush());
    }
  }
}

void GameField::setSelectedGame(int game) {
  selectedGame = game;
  update();
}

void GameField::setInGame() {
  isInGame = !isInGame;
  update();
}

void GameField::gameSetGameInfo(const s21::GameInfo_t &viewGameInfo) {
  gameInfo = viewGameInfo;
}
