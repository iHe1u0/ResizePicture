#pragma once

#include <QObject>

class File {
public:
    static QString generateTempSourceFile(const QString& sourceFilePath, QString tempFileName = "temp_src");
    static QString getTempDir(QString fileName = "temp");
    static bool copyFileToPath(QString sourceFile, QString toFile, bool coverFileIfExist = true);
    static void saveImage(QWidget* obj, const QString& imagePath);
};
