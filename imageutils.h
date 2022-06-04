#pragma once

#include <QFileInfo>
#include <QObject>
#include <opencv2/opencv.hpp>

using namespace cv;
/**
 * @brief The ImageUtils class
 * 实现对图片的缩放
 */
class ImageUtils : public QObject {
 public:
  // 定义放大倍数的极限值
  static constexpr double MAX_TIMES = 6.0;
  static constexpr double MIN_TIMES = 0.1;

  /**
   * @brief getImageType 获取图片类型
   * @param imagePath 图片路径
   * @return 图片类型，如 jpeg、png等，如果图片不存在默认返回 "jpeg"
   */
  static QString getImageType(const QString& imagePath);

  /**
   * @brief ImageUtils 利用原始图片路径构建类
   * @param src_path 源文件路径
   */
  ImageUtils(const QString& src_path);
  ~ImageUtils();

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
  static QImage mat2QImage(const Mat& mat);

  /**
   * @brief cannyCheck 边缘检测 使用的函数：
   * @第一个参数，InputArray类型的image，输入图像，即原图像，填Mat类型的对象即可，且需为单通道8位图像
   * @第二个参数，OutputArray类型的edges，输出的边缘图，需要和源图片有一样的尺寸和类型
   * @第三个参数，double类型的threshold1，第一个滞后性阈值
   * @第四个参数，double类型的threshold2，第二个滞后性阈值
   * @第五个参数，int类型的apertureSize，表示应用Sobel算子的孔径大小，其有默认值3
   * @第六个参数，bool类型的L2gradient，一个计算图像梯度幅值的标识，有默认值false
   *
   * @param imagePath 原图路径
   * @return 缓存文件路径
   */
  QString cannyCheck(const QString& imagePath) const;

  /**
   * @brief generateGrayImage 生成灰度图
   * @param imagePath 图片路径
   * @return 缓存文件路径
   */
  QString generateGrayImage(const QString& imagePath) const;

  /**
   * @brief denoisingImage 图像去噪 使用的函数：
   * CV_EXPORTS_W void fastNlMeansDenoisingColored( InputArray src, OutputArray
   * dst, float h = 3, float hColor = 3,int templateWindowSize = 7, int
   * searchWindowSize = 21);
   * @src 输入图像
   * @dst 输出图像
   * @h 决定过滤器强度。h 值高可以很好的去除噪声,但也会把图像的细节抹去。(取 10
   * 的效果不错）
   * @hColor 与h相同，使用于彩色图像
   * @templateWindowSize 奇数。(推荐值为 7）
   * @searchWindowSize 奇数。(推荐值为 21)
   *
   * @return 消除噪声后图片的缓存地址
   */
  QString denoisingImage() const;

 private:
  QFileInfo* fileInfo;
  QString tempFileName;
};
