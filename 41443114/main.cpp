#include "cbuiltindialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CBuiltinDialog w;
    w.show();
    return a.exec();
}