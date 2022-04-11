#include "mainwindow.h"
#include "error.h"
#include "ui_mainwindow.h"
#include "zoom.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QPixmap>
#include <opencv2/opencv.hpp>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("OpenCV图片缩放");
    //    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    //    setFixedSize(this->width(), this->height());

    connect(ui->actionOpenFile, SIGNAL(triggered()), this, SLOT(openImage()));
    connect(ui->actionZoomIn, SIGNAL(triggered()), this, SLOT(zoomIn()));
    connect(ui->actionZoomOut, SIGNAL(triggered()), this, SLOT(zoomOut()));

    ui->graphicsView->setCacheMode(QGraphicsView::CacheNone);
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);

    zoomUtils = new ZoomUtils(this->imagePath);
}

MainWindow::~MainWindow()
{
    delete zoomUtils;
    delete ui;
}

void MainWindow::openImage()
{
    QString filePath = QFileDialog::getOpenFileName(this, "选择一张图片", "E:\\testdata\\", "图片(*.png *.jpeg *.jpg *.bmp *.webp)");
    if (!filePath.isEmpty()) {
        this->imagePath = filePath;
        this->times = 1.00;
        showImage(filePath);
        zoomUtils = new ZoomUtils(this->imagePath);
    }
}

void MainWindow::zoomIn()
{
    if (this->imagePath.isEmpty()) {
        return;
    }
    if (times < zoomUtils->MAX_TIMES) {
        times += 0.5;
        QString tempPath = zoomUtils->zoomIn(times);
        if (tempPath.startsWith("-")) {
            QMessageBox::question(this, "错误", "操作错误，错误码：" + tempPath);
            return;
        }
        this->showImage(tempPath);
    } else {
        QMessageBox::information(this, "提示", "已经达到放大极限");
    }
}

void MainWindow::zoomOut()
{
    if (this->imagePath.isEmpty()) {
        return;
    }
    if (times > 0.5 && times > zoomUtils->MIN_TIMES) {
        times -= 0.5;
        QString tempPath = zoomUtils->zoomIn(times);
        if (tempPath.startsWith("-")) {
            QMessageBox::question(this, "错误", "操作错误，错误码：" + tempPath);
            return;
        }
        this->showImage(tempPath);
    } else {
        QMessageBox::information(this, "提示", "已经达到缩小极限");
    }
}
void MainWindow::showImage(QString imagePath)
{
    if (imagePath.isEmpty()) {
        return;
    }
    QGraphicsScene* scene = new QGraphicsScene;
    scene->addPixmap(QPixmap(imagePath));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
}
