#include <QApplication>

#include "cropwindow.h"
#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  MainWindow w;
  w.showMaximized();
  //  CropWindow w;
  //  w.setSourcePath("E:/User/Pictures/head_nn.jpg");
  //  w.show();

  return app.exec();
}
