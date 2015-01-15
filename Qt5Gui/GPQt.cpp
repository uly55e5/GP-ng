#include <qt5/QtWidgets/QApplication>
#include "mainwindow.h"
#include "../libGP/tiffimgset.h"
#include "../libGP/tiffimg.h"
#include <QImage>
#include <QGraphicsScene>

int main(int argc, char* argv[])
{
  QApplication * app = new QApplication(argc, argv);
  MainWindow mw;
  mw.show();


  return app->exec();
}
