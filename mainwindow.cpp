#include "mainwindow.h"
#include "error.h"
#include "resize.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QPixmap>
#include <opencv2/opencv.hpp>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("OpenCV图片缩放");
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    setFixedSize(this->width(), this->height());

    ui->scaleSlider->setMinimum(SCALE_MIN);
    ui->scaleSlider->setMaximum(SCALE_MAX);

    connect(ui->actionOpenFile, SIGNAL(triggered()), this, SLOT(openImage()));
    connect(ui->scaleSlider, SIGNAL(valueChanged(int)), this, SLOT(enlarge()));
    connect(ui->scaleSlider, SIGNAL(valueChanged(int)), ui->scaleSpinBox, SLOT(setValue(int)));
    connect(ui->scaleSpinBox, SIGNAL(valueChanged(int)), ui->scaleSlider, SLOT(setValue(int)));

    ui->scaleSpinBox->setValue(SCALE_MIN);
    scene = new QGraphicsScene;
    resize = new Resize(this->imagePath);
}

MainWindow::~MainWindow()
{
    delete resize;
    delete scene;
    delete ui;
}

void MainWindow::openImage()
{
    QString filePath = QFileDialog::getOpenFileName(this, "选择一张图片", "/", "files(*)");
    if (!filePath.isEmpty()) {
        this->imagePath = filePath;
        updateImage(filePath);
        resize = new Resize(this->imagePath);
    }
}

void MainWindow::enlarge()
{
    if (this->imagePath.isEmpty()) {
        return;
    }
    int times = this->ui->scaleSlider->value();
    QString temp_path = resize->enlarge(times);
    this->updateImage(temp_path);
}

void MainWindow::updateImage(QString image_path)
{
    if (image_path.isEmpty()) {
        qDebug() << "can't get file path";
        return;
    }
    scene->addPixmap(QPixmap(image_path));
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
}
