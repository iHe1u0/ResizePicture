#pragma once
#include "resize.h"
#include "ui_mainwindow.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

constexpr int SCALE_MIN = 1;
constexpr int SCALE_MAX = 5;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow* ui;
    Resize* resize;
    QString imagePath;
    QGraphicsScene* scene;
    void updateImage(QString image_path);
private slots:
    void openImage();
    void enlarge();
};
