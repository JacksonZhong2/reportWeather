#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //设置全局字体
    QFont global("Microsoft YaHei UI");
    a.setStyleSheet("QLabel { font-family: Microsoft YaHei UI;}");
    Widget w;
    w.show();
    return a.exec();
}
