#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("你喜欢就好-像素风消消乐");
    w.show();

    return a.exec();
}
