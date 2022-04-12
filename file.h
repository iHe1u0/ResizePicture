#pragma once

#include <QObject>

class File {
public:
    static QString generateTempSourceFile(const QString& sourceFilePath, const QString& tempFileName = "temp_src");
    static QString getTempDir(const QString& fileName = "temp");
    static bool copyFileToPath(const QString& sourceFile, QString& toFile, bool coverFileIfExist = true);
    static void saveImage(QWidget* obj, const QString& imagePath);
};
