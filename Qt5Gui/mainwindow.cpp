#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../libGP/tiffimgset.h"
#include "../libGP/tiffimg.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  mPixmapItem(nullptr)
{
  ui->setupUi(this);
  connect(ui->brightnessSlider,&QSlider::valueChanged,this,&MainWindow::setBrightness);
  connect(ui->contrastSlider,&QSlider::valueChanged,this,&MainWindow::setContrast);
   mTiffView = new TiffGraphicsView(ui->ImageTab);
   mTiffView->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);

  mTiffView->adjustSize();
  mTiffView->adjustSize();
  mTiffScene = new QGraphicsScene(mTiffView);

  mTiffView->setScene(mTiffScene);
  setTifImage();
  updateImage();
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::setGraphicsScene(QGraphicsScene *scene)
{

}

void MainWindow::setTifImage()
{
    TiffImgSet * tiffs = new TiffImgSet("1769-31-D12.tif");
    mTifImg = tiffs->getImg(2);
    updateImage();
    mTiffView->adjustSize();
}

void MainWindow::updateImage()
{
    QImage im{mTifImg->rgbaData(),mTifImg->Width(),mTifImg->Height(),QImage::Format_RGB32};
    QPixmap pm = QPixmap::fromImage(im);
    if(mPixmapItem)
        mTiffScene->removeItem(dynamic_cast<QGraphicsItem*> (mPixmapItem));
    mPixmapItem = mTiffScene->addPixmap(pm);
    mTiffScene->setSceneRect(pm.rect());
    mTiffView->update();
}

void MainWindow::setBrightness(int brightness)
{
    mTifImg->setBrightness(double(brightness)/256);
    updateImage();
}

void MainWindow::setContrast(int contrast)
{
    mTifImg->setContrast(double(contrast)/200);
    updateImage();
}
