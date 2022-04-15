#pragma once

#include <QApplication>
#include <QDialog>
#include <QFileSystemModel>

namespace Ui {
class AboutDialog;
}

class AboutDialog : public QDialog {
    Q_OBJECT

public:
    explicit AboutDialog(QWidget* parent = nullptr);
    ~AboutDialog();

private:
    Ui::AboutDialog* ui;
    const QString licenseFilePath = QApplication::applicationDirPath().append("/etc/licenses");
    QFileSystemModel* fileModel;

private slots:
    void itemClicked(QModelIndex index);
};
