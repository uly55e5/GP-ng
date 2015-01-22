#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../libGP/tiffimgset.h"
#include "../libGP/tiffimg.h"

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <iostream>
/*!
 * \brief MainWindow::MainWindow
 * \param parent
 */
MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  mPixmapItem(nullptr)
{
  ui->setupUi(this);
  ui->redGreenOperatorBox->insertItems(0,QStringList{"/","*","+","-"});

  connect(ui->brightnessSlider,&QSlider::valueChanged,this,&MainWindow::setBrightness);
  connect(ui->contrastSlider,&QSlider::valueChanged,this,&MainWindow::setContrast);
  connect(ui->redGreenOperatorBox,SIGNAL(currentIndexChanged(const QString&)),this,SLOT(setRGOperator(const QString&)));
  connect(ui->exchangeRedGreenButton,&QPushButton::clicked,this,&MainWindow::exchangeRG);
  connect(ui->selectGreenButton,&QRadioButton::toggled,this,&MainWindow::selectImage);
  connect(ui->selectRedButton,&QRadioButton::toggled,this,&MainWindow::selectImage);
  connect(ui->selectRedGreenButton,&QRadioButton::toggled,this,&MainWindow::selectImage);
  connect(ui->loadImageAction,&QAction::triggered,this,&MainWindow::loadImage);
  connect(ui->loadGalAction,&QAction::triggered,this,&MainWindow::loadGal);
  connect(ui->loadResultAction,&QAction::triggered,this,&MainWindow::loadGpr);



  mTiffView = new TiffGraphicsView(ui->ImageTab);
  mTiffView->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);

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

void MainWindow::setRGOperator(const QString &op)
{

}

void MainWindow::exchangeRG()
{

}

void MainWindow::selectImage()
{

}

void MainWindow::loadImage()
{

}

void MainWindow::loadGal()
{

}

void MainWindow::loadGpr()
{

}
