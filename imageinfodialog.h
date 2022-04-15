#ifndef IMAGEINFODIALOG_H
#define IMAGEINFODIALOG_H

#include <QDialog>
#include <QFileInfo>

namespace Ui {
class ImageInfoDialog;
}

class ImageInfoDialog : public QDialog {
    Q_OBJECT

public:
    explicit ImageInfoDialog(const QString& imagePath, QWidget* parent = nullptr);
    ~ImageInfoDialog();

private:
    Ui::ImageInfoDialog* ui;
    QFileInfo* info;
};

#endif // IMAGEINFODIALOG_H
