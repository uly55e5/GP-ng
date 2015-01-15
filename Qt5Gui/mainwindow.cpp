#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../libGP/tiffimgset.h"
#include "../libGP/tiffimg.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  connect(ui->brightnessSlider,&QSlider::valueChanged,this,&MainWindow::setBrightness);
  connect(ui->contrastSlider,&QSlider::valueChanged,this,&MainWindow::setContrast);
  mTiffScene = new QGraphicsScene;
  ui->tifImageView->setScene(mTiffScene);
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
}

void MainWindow::updateImage()
{
    QImage im{mTifImg->rgbaData(),mTifImg->Width(),mTifImg->Height(),QImage::Format_RGB32};
    QPixmap pm = QPixmap::fromImage(im);
    mTiffScene->clear();
    mTiffScene->addPixmap(pm);
    mTiffScene->setSceneRect(pm.rect());
    ui->tifImageView->update();
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
