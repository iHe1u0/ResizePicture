#pragma once
#include "imageutils.h"
#include "ui_mainwindow.h"
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
    ImageUtils* imageUtils = nullptr;

    // 原图路径
    QString sourceImagePath;

    // 临时缓存图片路径
    QString tempImagePath;

    // 缩放倍数
    double times;

    // 显示界面对象
    QGraphicsScene* scene;

    // 缩放后的文件路径
    QString zoomImagePath;

    // 图片操作菜单组
    QActionGroup* imageOperationMenu;
    /**
     * @brief showImage 用指定路径的图片文件更新主界面显示
     * @param imagePath 图片文件路径
     */
    void showImage(const QString& imagePath);

    /**
     * @brief showImage 用一个QImage对象更新主界面显示的图片
     * @param image QImage对象
     */
    void showImage(const QImage& image);

    /**
     * @brief zoom 缩放
     * @param times 缩放倍数，指缩放到原图的times倍
     */
    void zoom();

    /**
     * @brief updateStatusBar 更新状态栏
     */
    void updateStatusBar() const;
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

    /**
     * @brief saveImage 保存图片
     */
    void saveImage();

    /**
     * @brief getImageInfo 显示图片信息
     */
    void getImageInfo() const;

    /**
     * @brief reset 重置为原图
     */
    void reset(bool isChecked);

    /**
     * @brief cannyCheck canny边缘检测
     * @param isChecked true为开启边缘检测
     */
    void cannyCheck(bool isChecked);

    /**
     * @brief grayImage 灰度图
     * @param isChecked true为显示
     */
    void grayImage(bool isChecked);

    /**
     * @brief denoising 图像去噪
     */
    void denoising();

    void showAbout() const;
};
