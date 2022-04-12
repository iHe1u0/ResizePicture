#include "zoom.h"
#include "error.h"
#include "file.h"
#include <QFileInfo>
#include <QMessageBox>
#include <QObject>
#include <QTextCodec>
#include <exception>
#include <opencv2/opencv.hpp>

using namespace cv;

ZoomUtils::ZoomUtils(const QString filePath)
{
    if (filePath.isEmpty()) {
        return;
    }
    this->fileInfo = new QFileInfo(filePath);
    if (fileInfo->exists() && fileInfo->isFile()) {
        this->tempFileName = "temp." + fileInfo->suffix();
    } else {
        throw std::exception((QString::number(ERROR_WRONG_FILE_TYPE)).toStdString().c_str());
    }
}

ZoomUtils::~ZoomUtils()
{
    if (this->fileInfo) {
        delete this->fileInfo;
    }
}

QString ZoomUtils::zoomIn(double times)
{
    Mat image = imread(fileInfo->absoluteFilePath().toStdString()), tempImage;
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
    if (times <= 0) {
        return QString::number(ERROR_ZERO_ZOOM);
    }
    QString imageFilePath = fileInfo->absoluteFilePath();
    qDebug() << imageFilePath;
    QTextCodec* codec = QTextCodec::codecForName("UTF-8");
    qDebug() << codec->fromUnicode(imageFilePath);
    Mat image = imread(imageFilePath.toStdString().c_str());
    if (image.empty()) {
        return QString::number(ERROR_IO);
    }
    // 原图像行数
    int height = image.rows;
    // 原图像列数
    int width = image.cols;
    Size size = Size(round(times * width), round(times * height));
    Mat* tempImage = new Mat;
    resize(image, *tempImage, size, 0, 0, INTER_AREA);
    QString tempFilePath = File::getTempDir(this->tempFileName);
    imwrite(tempFilePath.toStdString(), *tempImage);
    return tempFilePath;
}