#include "zoom.h"
#include "error.h"
#include "file.h"
#include <QFileInfo>
#include <QObject>
#include <opencv2/opencv.hpp>

using namespace cv;

ZoomUtils::ZoomUtils(const QString src_path)
{
    if (src_path.isEmpty()) {
        return;
    }
    this->file_info = new QFileInfo(src_path);
    this->tempFileName = "temp." + file_info->suffix();
}

ZoomUtils::~ZoomUtils()
{
    if (this->file_info) {
        delete this->file_info;
    }
}

QString ZoomUtils::zoomIn(double times)
{
    Mat image = imread(file_info->absoluteFilePath().toStdString()), tempImage;

    if (image.empty()) {
        return QString::number(ERROR_FILE_NOT_FOUND);
    }
    // 原图像行数
    int height = image.rows;
    // 原图像列数
    int width = image.cols;
    Size size = Size(round(times * width), round(times * height));
    resize(image, tempImage, size, 0, 0, INTER_CUBIC);

    QString tempFilePath = File::getTempDir(this->tempFileName);
    imwrite(tempFilePath.toStdString(), tempImage);
    return tempFilePath;
}

QString ZoomUtils::zoomOut(double times)
{
    Mat image = imread(file_info->absoluteFilePath().toStdString()), tempImage;

    if (image.empty()) {
        return QString::number(ERROR_FILE_NOT_FOUND);
    }
    // 原图像行数
    int height = image.rows;
    // 原图像列数
    int width = image.cols;
    Size size = Size(round(times * width), round(times * height));
    resize(image, tempImage, size, 0, 0, INTER_AREA);

    QString tempFilePath = File::getTempDir(this->tempFileName);
    imwrite(tempFilePath.toStdString(), tempImage);
    return tempFilePath;
}
