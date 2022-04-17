#include "mainwindow.h"
#include "aboutdialog.h"
#include "error.h"
#include "file.h"
#include "imageinfodialog.h"
#include "imageutils.h"
#include "ui_imageinfodialog.h"
#include "ui_mainwindow.h"
#include <QActionGroup>
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
    connect(ui->actionResetImage, SIGNAL(triggered(bool)), this, SLOT(reset(bool)));
    connect(ui->actionCanny, SIGNAL(triggered(bool)), this, SLOT(cannyCheck(bool)));
    connect(ui->actionGrayImage, SIGNAL(triggered(bool)), this, SLOT(grayImage(bool)));
    connect(ui->actionDetectFace, SIGNAL(triggered(bool)), this, SLOT(detectFace(bool)));
    connect(ui->actionShowAbout, SIGNAL(triggered()), this, SLOT(showAbout()));
    ui->screen->setCacheMode(QGraphicsView::CacheNone);
    ui->screen->setDragMode(QGraphicsView::ScrollHandDrag);

    scene = new QGraphicsScene;

    // 图片处理只在原图或者是缩放的图片上单一操作
    imageOperationMenu = new QActionGroup(this);
    imageOperationMenu->addAction(ui->actionResetImage);
    imageOperationMenu->addAction(ui->actionCanny);
    imageOperationMenu->addAction(ui->actionGrayImage);
    imageOperationMenu->addAction(ui->actionDetectFace);
    imageOperationMenu->setEnabled(false);
}

MainWindow::~MainWindow()
{
    if (!tempImagePath.isEmpty() && QFile::exists(tempImagePath)) {
        QFile::remove(tempImagePath);
    }
    if (imageUtils) {
        delete imageUtils;
    }
    delete imageOperationMenu;
    delete scene;
    delete ui;
}

void MainWindow::openImage()
{
    this->sourceImagePath = QFileDialog::getOpenFileName(this, "选择一张图片", "./", "图片(*.png;*.jpeg;*.jpg;*.bmp;*.webp;*.tiff);;所有文件(*.*)");
    if (sourceImagePath.isEmpty()) {
        return;
    }
    setWindowTitle(sourceImagePath);
    tempImagePath = File::generateTempSourceFile(sourceImagePath);
    imageUtils = new ImageUtils(tempImagePath);
    if (!QFile::exists(tempImagePath)) {
        QMessageBox::critical(this, "错误！", "图片读取失败");
        return;
    }
    this->times = 1.00;
    showImage(tempImagePath);
    imageOperationMenu->setEnabled(true);
    ui->actionResetImage->setChecked(true);
}

void MainWindow::saveImage()
{
    File::saveImage(this, tempImagePath);
}

void MainWindow::getImageInfo() const
{
    if (this->sourceImagePath.isEmpty()) {
        return;
    }
    ImageInfoDialog* dialog = new ImageInfoDialog(this->sourceImagePath);
    dialog->exec();
}

void MainWindow::reset(bool isChecked)
{
    if (isChecked) {
        tempImagePath = File::generateTempSourceFile(sourceImagePath);
        imageUtils = new ImageUtils(tempImagePath);
        times = 1.0;
        showImage(this->tempImagePath);
    }
}

void MainWindow::cannyCheck(bool isChecked)
{
    if (isChecked) {
        tempImagePath = imageUtils->cannyCheck(tempImagePath);
        imageUtils = new ImageUtils(tempImagePath);
        times = 1.0;
        showImage(tempImagePath);
    }
}

void MainWindow::grayImage(bool isChecked)
{
    if (isChecked) {
        tempImagePath = imageUtils->generateGrayImage(tempImagePath);
        imageUtils = new ImageUtils(tempImagePath);
        times = 1.0;
        showImage(tempImagePath);
    }
}

void MainWindow::detectFace(bool isChecked)
{
    if (isChecked) {
        QString faceDetectionImagePath = File::generateTempSourceFile(sourceImagePath);
        bool hasFace = imageUtils->detectFace(sourceImagePath, faceDetectionImagePath);
        if (hasFace) {
            tempImagePath = faceDetectionImagePath;
            imageUtils = new ImageUtils(tempImagePath);
            times = 1.0;
            showImage(tempImagePath);
        } else {
            QMessageBox::critical(this, "提示", "未检测到人脸");
            ui->actionResetImage->setChecked(true);
        }
    }
}

void MainWindow::showAbout() const
{
    AboutDialog* dialog = new AboutDialog;
    dialog->exec();
}

void MainWindow::showImage(const QString& imagePath)
{
    if (imagePath.isEmpty() || !QFile::exists(imagePath)) {
        return;
    }
    if (scene) {
        delete scene;
        scene = new QGraphicsScene;
    }

    scene->addPixmap(QPixmap(imagePath));
    ui->screen->setScene(scene);
    ui->screen->show();

    updateStatusBar();
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
    updateStatusBar();
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
    QString tempPath = imageUtils->zoom(times);
    if (tempPath.startsWith("-")) {
        QMessageBox::information(this, "错误", "操作错误，错误码：" + tempPath);
        return;
    }
    this->showImage(tempPath);
}

void MainWindow::updateStatusBar() const
{
    ui->statusbar->showMessage("缩放倍数:" + QString::number(times));
}
