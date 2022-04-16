#include "imageutils.h"
#include "error.h"
#include "file.h"
#include <QFileInfo>
#include <QImageReader>
#include <QMessageBox>
#include <QObject>
#include <QTextCodec>
#include <exception>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;

QString ImageUtils::getImageType(const QString& imagePath)
{
    if (imagePath.isEmpty() || !QFile::exists(imagePath)) {
        return "jpeg";
    }
    return QImageReader::imageFormat(imagePath);
}

ImageUtils::ImageUtils(const QString& filePath)
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

ImageUtils::~ImageUtils()
{
    if (this->fileInfo) {
        delete this->fileInfo;
    }
}

QString ImageUtils::zoom(const double& times) const
{
    if (times <= 0) {
        return QString::number(ERROR_ZERO_ZOOM);
    }
    Mat image = imread(fileInfo->absoluteFilePath().toStdString(), ImreadModes::IMREAD_UNCHANGED);
    if (image.empty()) {
        return QString::number(ERROR_FILE_NOT_FOUND);
    }
    // 原图像行数
    int height = image.rows;
    // 原图像列数
    int width = image.cols;
    Size size = Size(round(times * width), round(times * height));
    Mat* tempImage = new Mat;
    cv::resize(image, *tempImage, size, 0, 0, INTER_CUBIC);
    QString tempFilePath = File::getTempDir(this->tempFileName);
    imwrite(tempFilePath.toStdString(), *tempImage);
    delete tempImage;
    return tempFilePath;
}

QImage ImageUtils::mat2QImage(const Mat& mat) const
{
    // 8-bits unsigned, NO. OF CHANNELS = 1
    if (mat.type() == CV_8UC1) {
        QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
        // Set the color table (used to translate colour indexes to qRgb values)
        image.setColorCount(256);
        for (int i = 0; i < 256; i++) {
            image.setColor(i, qRgb(i, i, i));
        }
        // Copy input Mat
        uchar* pSrc = mat.data;
        for (int row = 0; row < mat.rows; row++) {
            uchar* pDest = image.scanLine(row);
            memcpy(pDest, pSrc, mat.cols);
            pSrc += mat.step;
        }
        return image;
    }
    // 8-bits unsigned, NO. OF CHANNELS = 3
    else if (mat.type() == CV_8UC3) {
        // Copy input Mat
        const uchar* pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return image.rgbSwapped();
    } else if (mat.type() == CV_8UC4) {
        // Copy input Mat
        const uchar* pSrc = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
        return image.copy();
    } else {
        qDebug() << "ERROR: Mat could not be converted to QImage.";
        return QImage();
    }
}

QString ImageUtils::cannyCheck(const QString& imagePath) const
{
    if (imagePath.isEmpty()) {
        return QString::number(ERROR_FILE_NOT_FOUND);
    }
    QString tempImagePath = File::getTempDir("canny").append(".").append(getImageType(imagePath));
    Mat image = imread(imagePath.toStdString());
    Mat cannyImage(image.size(), CV_8UC1, Scalar());
    Canny(image, cannyImage, 100, 100, 3, false);
    imwrite(tempImagePath.toStdString(), cannyImage);
    return tempImagePath;
}

QString ImageUtils::generateGrayImage(const QString& imagePath) const
{
    if (imagePath.isEmpty()) {
        return QString::number(ERROR_FILE_NOT_FOUND);
    }
    QString tempImagePath = File::getTempDir("grayImage").append(".").append(getImageType(imagePath));
    Mat image = imread(imagePath.toStdString());
    Mat grayImage;
    cvtColor(image, grayImage, cv::COLOR_RGBA2GRAY);
    cv::imwrite(tempImagePath.toStdString(), grayImage);
    return tempImagePath;
}
