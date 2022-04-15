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
    setWindowTitle("Licenses");
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
