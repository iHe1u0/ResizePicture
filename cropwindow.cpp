#include "cropwindow.h"

#include "ui_cropwindow.h"

CropWindow::CropWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::CropWindow) {
  ui->setupUi(this);
  this->setWindowTitle("图片裁剪");
  this->setWindowIcon(
      QIcon(QApplication::applicationDirPath() + "/etc/images/ic_app.png"));
}

CropWindow::~CropWindow() {
  delete ui;
}

void CropWindow::setSourcePath(const QString& path) {
  if (path.isEmpty()) {
    return;
  }
  src = path;
}
