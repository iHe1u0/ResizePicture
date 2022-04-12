#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    MainWindow w;
    // 最大化显示
    // w.showMaximized();
    w.show();
    return app.exec();
}
