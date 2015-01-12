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

  TiffImgSet * tiffs = new TiffImgSet("../../exdata/1738-16-hdac6.tif");
  TiffImg * tiff = tiffs->getImg(2);
  tiff->readRawValues();
  QImage im(tiff->rgbaData(),tiff->Width(),tiff->Height(),QImage::Format_RGB32);
  QPixmap pm = QPixmap::fromImage(im);
  QGraphicsScene scene;
  scene.addPixmap(pm);
  scene.setSceneRect(pm.rect());

  mw.setGraphicsScene(&scene);


  return app->exec();
}
