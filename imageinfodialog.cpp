#include "imageinfodialog.h"
#include "ui_imageinfodialog.h"

#include <QIcon>

ImageInfoDialog::ImageInfoDialog(const QString& imagePath, QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::ImageInfoDialog)
{
    ui->setupUi(this);
    if (imagePath.isEmpty()) {
        this->close();
    }
    info = new QFileInfo(imagePath);
    this->setWindowTitle("图片信息");
    this->setWindowIcon(QIcon(QApplication::applicationDirPath() + "/etc/images/ic_app.png"));
    setWindowModality(Qt::ApplicationModal);
    setAttribute(Qt::WA_DeleteOnClose);

    ui->image_info_dialog_filename->setText(info->fileName());
    ui->image_info_dialog_size->setText(QString("%1 KB").arg(info->size() / 1024.0));
    ui->image_info_dialog_type->setText(info->suffix());
    ui->image_info_dialog_filepath->setText(info->absoluteFilePath());
}

ImageInfoDialog::~ImageInfoDialog()
{
    delete info;
    delete ui;
}
