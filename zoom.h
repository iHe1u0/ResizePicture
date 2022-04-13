#pragma once
#include <QFileInfo>
#include <QObject>
#include <opencv2/opencv.hpp>

using namespace cv;
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
    ZoomUtils(const QString& src_path);
    ~ZoomUtils();

    /**
     * @brief zoom 缩放图片
     * @param times 倍数，默认为1，即原图，不缩放
     * @return 缩放后的图片缓存路径或者是错误码
     */
    QString zoom(const double& times = 1.0) const;

    /**
     * @brief mat2QImage OpenCV的Mat的对象转换为QImage对象
     * @param mat 要转换的Mat对象
     * @return 转换后的QImage对象
     */
    QImage mat2QImage(const Mat& mat) const;

private:
    QFileInfo* fileInfo;
    QString tempFileName;
};
