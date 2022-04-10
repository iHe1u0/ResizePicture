#pragma once
#include <QFileInfo>
#include <QObject>

/**
 * @brief The ZoomUtils class
 * 实现对图片的缩放
 */
class ZoomUtils {
public:
    // 定义放大倍数的极限值
    static constexpr double MAX_TIMES = 10.0;
    static constexpr double MIN_TIMES = 0.1;

    /**
     * @brief ZoomUtils 利用原始图片路径构建类
     * @param src_path 源文件路径
     */
    ZoomUtils(const QString src_path);
    ~ZoomUtils();

    /**
     * @brief zoomIn 放大图片
     * @param times 放大倍数，默认为1，即原图，不放大
     * @return 放大后的图片缓存路径
     */
    QString zoomIn(double times = 1.0);

    /**
     * @brief zoomOut 缩小图片
     * @param times 缩小倍数
     * @return 缩小后的图片缓存路径
     */
    QString zoomOut(double times = 1.0);

private:
    QFileInfo* file_info;
    QString tempFileName;
};
