#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.QWidget::showFullScreen();
    //w.setWindowState(Qt::WindowMaximized);
    //w.set
    w.show();
    return a.exec();
}
