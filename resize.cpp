#include "resize.h"
#include "error.h"
#include "file.h"
#include <QObject>
#include <opencv2/opencv.hpp>

using namespace cv;

Resize::Resize(const QString src_path)
{
    if (src_path.isEmpty()) {
        return;
    }
    this->src_image_path = src_path;
}

QString Resize::enlarge(int times)
{
    Mat image = imread(this->src_image_path.toStdString()), image_enlarge;
    if (image.empty()) {
        return QString::number(ERROR_FILE_NOT_FOUND);
    }
    //原图像行数
    int height = image.rows;
    //原图像列数
    int width = image.cols;
    Size size = Size(round(times * width), round(times * height));
    resize(image, image_enlarge, size, 0, 0, INTER_NEAREST);

    QString enlarge_image_path = File::getTempDir("enlarge.jpg");
    imwrite(enlarge_image_path.toStdString(), image_enlarge);
    return enlarge_image_path;
}
