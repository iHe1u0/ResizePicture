#pragma once

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
