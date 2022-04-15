#include "mainwindow.h"
#include "aboutdialog.h"
#include "error.h"
#include "file.h"
#include "imageinfodialog.h"
#include "imageutils.h"
#include "ui_imageinfodialog.h"
#include "ui_mainwindow.h"
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

    connect(ui->actionOpenFile, SIGNAL(triggered()), this, SLOT(openImage()));
    connect(ui->actionZoomIn, SIGNAL(triggered()), this, SLOT(zoomIn()));
    connect(ui->actionZoomOut, SIGNAL(triggered()), this, SLOT(zoomOut()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveImage()));
    connect(ui->actionGetImageInfo, SIGNAL(triggered()), this, SLOT(getImageInfo()));
    connect(ui->actionShowAbout, SIGNAL(triggered()), this, SLOT(showAbout()));

    ui->screen->setCacheMode(QGraphicsView::CacheNone);
    ui->screen->setDragMode(QGraphicsView::ScrollHandDrag);

    scene = new QGraphicsScene;
    imageUtils = new ImageUtils(this->tempImagePath);
}

MainWindow::~MainWindow()
{
    if (!tempImagePath.isEmpty() && QFile::exists(tempImagePath)) {
        QFile::remove(tempImagePath);
    }
    delete scene;
    delete imageUtils;
    delete ui;
}

void MainWindow::openImage()
{
    sourceImagePath = QFileDialog::getOpenFileName(this, "选择一张图片", "./", "图片(*.png;*.jpeg;*.jpg;*.bmp;*.webp;*.tiff);;所有文件(*.*)");
    if (sourceImagePath.isEmpty()) {
        return;
    }
    this->setWindowTitle(sourceImagePath);

    tempImagePath = File::generateTempSourceFile(sourceImagePath);

    if (!QFile::exists(tempImagePath)) {
        QMessageBox::critical(this, "错误！", "图片读取失败");
        return;
    }
    this->times = 1.00;
    showImage(tempImagePath);
    imageUtils = new ImageUtils(tempImagePath);
}

void MainWindow::saveImage()
{
    File::saveImage(this, zoomImagePath);
}

void MainWindow::getImageInfo() const
{
    if (this->sourceImagePath == nullptr) {
        return;
    }
    ImageInfoDialog* dialog = new ImageInfoDialog(this->sourceImagePath);
    dialog->exec();
}

void MainWindow::showAbout() const
{
    AboutDialog* a = new AboutDialog;
    a->exec();
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

    ui->statusbar->showMessage("放大倍数:" + QString::number(times));
}

void MainWindow::showImage(const QImage& image)
{
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
    times += 0.5;
    zoom();
}

void MainWindow::zoomOut()
{
    times -= 0.1;
    zoom();
}

void MainWindow::zoom()
{
    if (this->tempImagePath.isEmpty()) {
        ui->statusbar->showMessage("操作错误，图片不存在");
        return;
    }
    if (times <= imageUtils->MIN_TIMES || times > imageUtils->MAX_TIMES || !times) {
        QMessageBox::information(this, "提示", "已经达到缩放极限");
        return;
    }
    qDebug() << "zoom:" << times;
    QString tempPath = imageUtils->zoom(times);
    if (tempPath.startsWith("-")) {
        QMessageBox::information(this, "错误", "操作错误，错误码：" + tempPath);
        return;
    }
    this->showImage(tempPath);
}
