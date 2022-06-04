#include "cropwindow.h"

#include <QCloseEvent>
#include <QMessageBox>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

#include "mainwindow.h"
#include "ui_cropwindow.h"

using namespace std;
using namespace cv;

CropWindow::CropWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::CropWindow) {
  ui->setupUi(this);
  setFixedSize(900, 660);

  this->setWindowIcon(
      QIcon(QApplication::applicationDirPath() + "/etc/images/ic_app.png"));

  ui->view->setMouseTracking(true);
  ui->view->installEventFilter(this);
}

CropWindow::~CropWindow() { delete ui; }

void CropWindow::setSourcePath(const QString& path) {
  if (path.isEmpty()) {
    return;
  }
  src = path;
  imageUtils = new ImageUtils(src);
  baseImg.load(src);
  QPixmap resImage = QPixmap::fromImage(baseImg);
  ui->view->setPixmap(resImage);
  ui->view->setAlignment(Qt::AlignCenter);
}

bool CropWindow::eventFilter(QObject* obj, QEvent* event) {
  QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
  if (obj == ui->view) {
    QPoint posLocal = QCursor::pos();  //获得相对于屏幕的坐标
    QPoint currentMousePoint;          //获得当前坐标
    if (event->type() == QEvent::MouseButtonPress) {
      if (mouseEvent->button() == Qt::LeftButton) {
        currentMousePoint =
            ui->view->mapFromGlobal(mouseEvent->globalPosition()).toPoint();
        posStartX = currentMousePoint.rx();
        posStartY = currentMousePoint.ry();

        //        posStartX = mouseEvent->globalPosition().rx();
        //        posStartY = mouseEvent->globalPosition().ry();

        isModified = true;
        return true;
      } else if (mouseEvent->button() == Qt::RightButton) {
        QPixmap resImage = QPixmap::fromImage(baseImg);
        ui->view->setPixmap(resImage);
      }
    } else if (event->type() == QEvent::MouseMove) {
      if (mouseEvent->buttons() == Qt::LeftButton) {
        currentMousePoint = ui->view->mapFromGlobal(posLocal);
        posEndX = currentMousePoint.x();
        posEndY = currentMousePoint.y();
        QImage imageWithRect = baseImg;
        painter.begin(&imageWithRect);
        painter.setPen(QPen(Qt::red, 2, Qt::DashDotLine, Qt::RoundCap));
        painter.drawRect(posStartX, posStartY, posEndX - posStartX,
                         posEndY - posStartY);
        painter.end();
        ui->view->setPixmap(QPixmap::fromImage(imageWithRect));
      }
      qDebug() << QString("startX:%1 startY:%2 Endx:%3 Endy:%4")
                      .arg(posStartX)
                      .arg(posStartY)
                      .arg(posEndX)
                      .arg(posEndY);

    } else if (event->type() == QEvent::MouseButtonRelease) {
      if (mouseEvent->button() == Qt::LeftButton) {
        // currentMousePoint = ui->view->mapFromGlobal(posLocal);
        // //获得相对于控件的坐标
        QPainter painter;
        QImage imageWithRect = baseImg;
        painter.begin(&imageWithRect);
        painter.setPen(
            QPen(Qt::red, 2, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
        painter.drawRect(posStartX, posStartY, posEndX - posStartX,
                         posEndY - posStartY);
        painter.end();
        ui->view->setPixmap(QPixmap::fromImage(imageWithRect));
        //本地裁剪
        QImage cropImage = baseImg.copy(
            posStartX, posStartY, posEndX - posStartX, posEndY - posStartY);
        // cropImage = cropImage.scaled(ui->view->size(), Qt::KeepAspectRatio);

        QPixmap resImage = QPixmap::fromImage(cropImage);
        ui->view->setPixmap(resImage);
      }
    }
  }
  return QWidget::eventFilter(obj, event);
}
