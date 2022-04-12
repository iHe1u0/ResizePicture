#include "mainwindow.h"
#include "error.h"
#include "file.h"
#include "ui_mainwindow.h"
#include "zoom.h"
#include <QApplication>
#include <QFileDialog>
#include <QFileInfo>
#include <QImage>
#include <QImageReader>
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
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveImage()));

    ui->screen->setCacheMode(QGraphicsView::CacheNone);
    ui->screen->setDragMode(QGraphicsView::ScrollHandDrag);

    scene = new QGraphicsScene;
    zoomUtils = new ZoomUtils(this->imagePath);
}

MainWindow::~MainWindow()
{
    if (!imagePath.isEmpty() && QFile::exists(imagePath)) {
        QFile::remove(imagePath);
    }
    delete scene;
    delete zoomUtils;
    delete ui;
}

void MainWindow::openImage()
{
    QString filePath = QFileDialog::getOpenFileName(this, "选择一张图片", "./", "图片(*.png *.jpeg *.jpg *.bmp *.webp *.tiff)");
    if (filePath.isEmpty()) {
        return;
    }
    this->setWindowTitle(filePath);

    imagePath = File::generateTempSourceFile(filePath);

    if (!QFile::exists(imagePath)) {
        QMessageBox::information(this, "错误！", "图片读取失败");
        return;
    }
    this->times = 1.00;
    showImage(imagePath);
    zoomUtils = new ZoomUtils(imagePath);
}

void MainWindow::saveImage()
{
    File::saveImage(this, zoomImagePath);
}

void MainWindow::showImage(const QString& imagePath)
{
    if (imagePath.isEmpty()) {
        return;
    }
    if (scene) {
        delete scene;
        scene = new QGraphicsScene;
    }
    zoomImagePath = imagePath;

    scene->addPixmap(QPixmap(zoomImagePath));
    ui->screen->setScene(scene);
    ui->screen->show();
    //    QImageReader reader(zoomImagePath);
    //    qDebug() << "Image Size:" << reader.size();
    //    reader.setScaledSize(QSize(600, 600));
    //    showImage(reader.read());
    //    qDebug() << "Show Size:" << reader.size();

    ui->statusbar->showMessage("放大倍数:" + QString::number(times));
}

void MainWindow::showImage(const QImage& image)
{
    QPixmap pixmap = QPixmap::fromImage(image);
    if (scene) {
        delete scene;
        scene = new QGraphicsScene;
    }
    scene->addPixmap(QPixmap::fromImage(image));
    ui->screen->setScene(scene);
    ui->screen->show();

    ui->statusbar->showMessage("放大倍数:" + QString::number(times));
}

void MainWindow::zoomIn()
{
    times += 5;
    zoom();
}

void MainWindow::zoomOut()
{
    times -= 0.1;
    zoom();
}

void MainWindow::zoom()
{
    if (this->imagePath.isEmpty()) {
        ui->statusbar->showMessage("操作错误，图片不存在");
        return;
    }
    if (times <= zoomUtils->MIN_TIMES || times > zoomUtils->MAX_TIMES || !times) {
        QMessageBox::information(this, "提示", "已经达到缩放极限");
        return;
    }
    qDebug() << "zoom:" << times;
    QString tempPath = zoomUtils->zoom(times);
    if (tempPath.startsWith("-")) {
        QMessageBox::information(this, "错误", "操作错误，错误码：" + tempPath);
        return;
    }
    this->showImage(tempPath);
}
