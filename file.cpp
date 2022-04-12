#include "file.h"
#include "error.h"
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QImageReader>
#include <QTemporaryDir>
#include <QTemporaryFile>

QString File::generateTempSourceFile(const QString& sourceFilePath, const QString& tempFileName)
{
    if (sourceFilePath.isEmpty() || !QFile::exists(sourceFilePath)) {
        return QString::number(ERROR_IMAGE_NOT_FOUND);
    }
    QFileInfo* fi = new QFileInfo(sourceFilePath);
    QString sourceTempFileDir = getTempDir(tempFileName + "." + QImageReader::imageFormat(sourceFilePath));
    bool status = copyFileToPath(sourceFilePath, sourceTempFileDir, true);
    delete fi;
    if (status) {
        return sourceTempFileDir;
    }
    return QString::number(ERROR_IO);
}

QString File::getTempDir(const QString& fileName)
{
    return QDir::tempPath() + QDir::separator() + fileName;
}

bool File::copyFileToPath(const QString& sourceFile, QString& toFile, bool coverFileIfExist)
{
    if (sourceFile.isEmpty() || toFile.isEmpty()) {
        return false;
    }
    toFile.replace("\\", "/");
    if (!QFile::exists(sourceFile)) {
        return false;
    }
    if (sourceFile == toFile) {
        return true;
    }
    if (QFile::exists(toFile)) {
        if (coverFileIfExist) {
            QFile::remove(toFile);
        } else {
            return false;
        }
    }
    if (QFile::copy(sourceFile, toFile)) {
        return true;
    }
    return false;
}

void File::saveImage(QWidget* obj, const QString& imagePath)
{
    if (imagePath.isEmpty()) {
        return;
    }
    QFileInfo* fileInfo = new QFileInfo(imagePath);
    QString savePath = QFileDialog::getSaveFileName(obj, "保存", fileInfo->absoluteFilePath(), "*." + QImageReader::imageFormat(imagePath));
    copyFileToPath(imagePath, savePath, true);
    delete fileInfo;
}
