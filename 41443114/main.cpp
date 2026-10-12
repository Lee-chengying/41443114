#include "cbuiltindialog.h"

#include <QApplication>

int main(int argc, char *argv[])//程式進入點
{
    QApplication a(argc, argv);//建立視窗環境
    Cbuiltindialog w;//我們宣告的類別之物件實體
    w.setWindowTitle("我的對話盒");
    w.show();//將物件顯示出來於桌面
    return QApplication::exec();//進入視窗的程式迴圈
}
