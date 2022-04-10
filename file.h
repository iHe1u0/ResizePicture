#pragma once
#include "error.h"

#include <QObject>

class File {
public:
    static bool isFileExist(QString file);
    static bool isDirExist(QString file);
    static QString getTempDir(QString fileName = "");
};
