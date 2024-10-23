#include "helpfield.h"

using namespace s21;

HelpField::HelpField(QWidget *parent)
    : QWidget(parent), selectedGame(SnakeG), isInGame(false) {
  setFixedSize(230, HEIGHT);
}

void HelpField::paintEvent(QPaintEvent *e) {
  Q_UNUSED(e)
  QPainter painter(this);
  painter.fillRect(rect(), BACKGROUND_COLOR);
  painter.setFont(NORMAL_FONT);
  painter.setPen(BLACK_COLOR);
  QFontMetrics fm(painter.font());
  int lineHeight = fm.height();

  painter.drawText(QRect(0, yHighScore, width(), lineHeight), Qt::AlignHCenter,
                   "High Score");
  painter.drawText(QRect(0, yLevel, width(), lineHeight), Qt::AlignHCenter,
                   "Level");
  painter.drawText(QRect(0, yNext, width(), lineHeight), Qt::AlignHCenter,
                   "Next");
  painter.drawText(QRect(0, yScore, width(), lineHeight), Qt::AlignHCenter,
                   "Score");

  QPen pen(SELECTED_COLOR);
  pen.setWidth(8);
  painter.setPen(pen);
  painter.drawRect(1, 1, width() - 2, HEIGHT - 2);

  if (isInGame) {
    if (gameInfo.showStartScreen) {
      if (selectedGame == SnakeG) {
        gameInfo.readHighScore();
        printHighScore(painter);
      } else if (selectedGame == TetrisG) {
        readHighScore(&gameInfo.highScore);
        printHighScore(painter);
      }
    } else {
      if (gameInfo.showStartScreen == 0 && gameInfo.showGameOverScreen == 0)
        printNext(painter);
      printPause(painter);
      clearScoreLevel(painter);
      printScoreLevel(painter);
    }
  } else {
    clearNext(painter);
    clearScoreLevel(painter);
    clearPause(painter);
  }
}

void HelpField::printHighScore(QPainter &painter) {
  painter.setFont(SMALL_FONT);
  QFontMetrics fm(painter.font());
  int smallLineHeight = fm.height();
  painter.setPen(BLACK_COLOR);
  painter.drawText(
      QRect(0, yHighScore + smallLineHeight * 2.5, width(), smallLineHeight),
      Qt::AlignHCenter, QString::number(gameInfo.highScore));
}

void HelpField::printPause(QPainter &painter) {
  painter.setFont(SMALL_FONT);
  QFontMetrics fmSmall(painter.font());
  int smallLineHeight = fmSmall.height();
  int widthInner = width() - 2 * borderThickness;

  if (gameInfo.pause == 0) {
    painter.setBrush(BACKGROUND_COLOR);
    painter.fillRect(X_START, yPause, widthInner, smallLineHeight,
                     painter.brush());
  } else if (gameInfo.pause == 1) {
    painter.setPen(BLACK_COLOR);
    painter.drawText(QRect(X_START, yPause, widthInner, smallLineHeight),
                     Qt::AlignHCenter, "PAUSE");
  }
}

void HelpField::clearPause(QPainter &painter) {
  QFontMetrics fmSmall(painter.font());
  int smallLineHeight = fmSmall.height();
  painter.setBrush(BACKGROUND_COLOR);
  int widthInner = width() - 2 * borderThickness;
  painter.fillRect(X_START, yPause, widthInner, smallLineHeight,
                   painter.brush());
}

void HelpField::printNext(QPainter &painter) {
  int squareSize = 20;
  int spacing = 5;
  int xNextField = ((QUADR * (squareSize + spacing)) - squareSize);

  if (gameInfo.next != nullptr) {
    for (int r = 0; r < QUADR; ++r) {
      for (int c = 0; c < QUADR; ++c) {
        int x = xNextField + c * (squareSize + spacing);
        int y = yNextField + r * (squareSize + spacing);

        if (gameInfo.next[r][c] == 1)
          painter.setBrush(SELECTED_COLOR);
        else
          painter.setBrush(BACKGROUND_COLOR);
        painter.fillRect(x, y, squareSize, squareSize, painter.brush());
      }
    }
  }
}

void HelpField::clearNext(QPainter &painter) {
  painter.setBrush(BACKGROUND_COLOR);
  int squareSize = 20;
  int spacing = 5;
  int xNextField = ((QUADR * (squareSize + spacing)) - squareSize);

  for (int r = 0; r < QUADR; r++) {
    for (int c = 0; c < QUADR; c++) {
      int x = xNextField + c * (squareSize + spacing);
      int y = yNextField + r * (squareSize + spacing);
      painter.fillRect(x, y, squareSize, squareSize, painter.brush());
    }
  }
}

void HelpField::printScoreLevel(QPainter &painter) {
  painter.setFont(SMALL_FONT);
  QFontMetrics fm(painter.font());
  int smallLineHeight = fm.height();
  painter.setPen(BLACK_COLOR);
  painter.drawText(
      QRect(0, yLevel + smallLineHeight * 2.5, width(), smallLineHeight),
      Qt::AlignHCenter, QString::number(gameInfo.level));
  painter.drawText(
      QRect(0, yScore + smallLineHeight * 2.5, width(), smallLineHeight),
      Qt::AlignHCenter, QString::number(gameInfo.score));
  printHighScore(painter);
}

void HelpField::clearScoreLevel(QPainter &painter) {
  painter.setFont(SMALL_FONT);
  painter.setBrush(BACKGROUND_COLOR);
  int widthInner = width() - 2 * borderThickness;
  QFontMetrics fm(painter.font());
  int smallLineHeight = fm.height();
  painter.fillRect(X_START, yHighScore + smallLineHeight * 2.5, widthInner,
                   smallLineHeight, painter.brush());
  painter.fillRect(X_START, yLevel + smallLineHeight * 2.5, widthInner,
                   smallLineHeight, painter.brush());
  painter.fillRect(X_START, yScore + smallLineHeight * 2.5, widthInner,
                   smallLineHeight, painter.brush());
}

void HelpField::setInGame() { isInGame = !isInGame; }

void HelpField::helpSetGameInfo(const s21::GameInfo_t &viewGameInfo) {
  gameInfo = viewGameInfo;
}

void HelpField::setSelectedGame(int game) { selectedGame = game; }
