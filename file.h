#pragma once

#include <QObject>

class File {
public:
    static QString generateTempSourceFile(QString sourceFilePath, QString tempFileName = "temp_src");
    static QString getTempDir(QString fileName = "temp");
    static bool copyFileToPath(QString sourceFile, QString toFile, bool coverFileIfExist = true);
};
