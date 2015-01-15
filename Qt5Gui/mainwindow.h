#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

#include "../libGP/tiffimg.h"

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  TiffImg * mTifImg;
  void setGraphicsScene(QGraphicsScene * scene);
  void setTifImage();
  void updateImage();
public slots:
  void setBrightness(int brightness);
  void setContrast(int contrast);

private:
  Ui::MainWindow *ui;

  QGraphicsScene * mTiffScene;

};




#endif // MAINWINDOW_H
