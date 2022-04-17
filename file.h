#pragma once

#include <QObject>

class File {
public:
    static QString generateTempSourceFile(const QString& sourceFilePath, const QString& tempFileName = "temp_src");
    static QString getTempDir(const QString& fileName = "temp");
    static bool copyFileToPath(const QString& sourceFile, QString& toFile, bool coverFileIfExist = true);
    static void saveImage(QWidget* obj, const QString& imagePath);

    /**
     * @brief getModelFilePath 获取模型文件绝对路径
     * @param modelFileName 模型文件名字,如 haarcascade_eye.xml
     * @param modelType 模型文件夹名，有两个文件夹 haarcascades 和 lbpcascades
     *        haarcascades、hogcascades 和 lbpcascades 分别表示
     *        通过haar、hog和lbp三种不同的特征而训练出的分类器
     *        "haar"特征主要用于人脸检测
     *        "hog"特征主要用于行人检测
     *        "lbp"特征主要用于人脸识别
     *        "eye"特征主要用于眼睛的检测识别
     * @return 文件路径
     */
    static QString getModelFilePath(const QString& modelFileName, const QString& modelType = "haarcascades");
};
