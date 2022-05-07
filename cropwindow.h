#pragma once

#include <QMainWindow>

namespace Ui {
class CropWindow;
}

class CropWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit CropWindow(QWidget* parent = nullptr);
    ~CropWindow();

    void setSourcePath(const QString& path);

private:
    Ui::CropWindow* ui;
    QString src;
};
