#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include <QDesktopServices>
#include <QFileSystemModel>
#include <QStringListModel>
#include <QUrl>

AboutDialog::AboutDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(QApplication::applicationDirPath() + "/etc/images/ic_app.png"));
    this->setWindowTitle("使用到的开源库及其版权声明");
    setAttribute(Qt::WA_DeleteOnClose);

    fileModel = new QFileSystemModel;
    fileModel->setRootPath(licenseFilePath);

    ui->licenseListView->setModel(fileModel);
    ui->licenseListView->setRootIndex(fileModel->index(licenseFilePath));
    ui->licenseListView->show();

    connect(ui->licenseListView, SIGNAL(clicked(QModelIndex)), this, SLOT(itemClicked(QModelIndex)));
}

AboutDialog::~AboutDialog()
{
    delete fileModel;
    delete ui;
}

void AboutDialog::itemClicked(QModelIndex index)
{
    QString path = licenseFilePath + "/" + index.data().toByteArray();
    QDesktopServices::openUrl(QUrl("file:///" + path));
}
