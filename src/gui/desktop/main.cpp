#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::MainWindow w;
  w.setWindowTitle("CPP3_BrickGame_v2.0 by s21_lemongrb");
  w.show();
  return a.exec();
}
