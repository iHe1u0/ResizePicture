#pragma once
#include "ui_mainwindow.h"
#include "zoom.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow* ui;
    ZoomUtils* zoomUtils;
    QString imagePath;
    double times;
    void updateImage(QString image_path);
private slots:
    void openImage();
    void zoomIn();
    void zoomOut();
};
