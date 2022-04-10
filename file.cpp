#include "file.h"
#include "error.h"
#include <QDir>
#include <QTemporaryDir>
#include <QTemporaryFile>

bool File::isFileExist(QString file)
{
    return false;
}

bool File::isDirExist(QString file)
{
    return false;
}

QString File::getTempDir(QString fileName)
{
    return QDir::tempPath() + QDir::separator() + fileName;
}
