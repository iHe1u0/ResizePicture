#pragma once
#include <QObject>

/**
 * @brief The Resize class
 * 实现对图片的缩放
 */
class Resize {
public:
    // 利用原始图片路径构建类
    Resize(const QString src_path);

    /**
     * @brief 放大图片
     * @param times 放大倍数，默认为1，即原图，不放大
     * @return 放大后的图片缓存路径
     */
    QString enlarge(int times = 1);

private:
    QString src_image_path;
};
