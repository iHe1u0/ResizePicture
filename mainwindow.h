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
    // 缩放类
    ZoomUtils* zoomUtils;

    //保存的图片路径
    QString imagePath;

    // 缩放倍数
    double times;

    // 更新主界面显示的图片
    void showImage(QString image_path);
private slots:
    /**
     * @brief openImage 打开图片
     */
    void openImage();

    /**
     * @brief zoomIn 放大图片
     */
    void zoomIn();

    /**
     * @brief zoomOut 缩小图片
     */
    void zoomOut();
};
