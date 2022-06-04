#pragma once

#include <QCloseEvent>
#include <QMainWindow>
#include <QMessageBox>
#include <QPainter>

#include "imageutils.h"

namespace Ui {
class CropWindow;
}

class CropWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit CropWindow(QWidget* parent = nullptr);
  ~CropWindow();

  void setSourcePath(const QString& path);

 private:
  Ui::CropWindow* ui;
  bool isModified;
  QString src;
  QImage baseImg;
  ImageUtils* imageUtils;
  QPainter painter;
  int posStartX, posStartY, posEndX, posEndY;
  bool eventFilter(QObject* obj, QEvent* event);
};
