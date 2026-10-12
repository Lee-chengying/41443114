#ifndef CBUILTINDIALOG_H
#define CBUILTINDIALOG_H

#include <QDialog>
#include<QtWidgets>

class Cbuiltindialog : public QDialog
{
    Q_OBJECT//巨集(Qt定義的)

public:
    explicit Cbuiltindialog(QWidget *parent = nullptr);
    ~Cbuiltindialog() override;
private:
    QTextEdit*     displayTextEdit;
    QPushButton*   colorPushBtn;
    QPushButton*   errorPushBtn;
    QPushButton*   filePushBtn;
    QPushButton*   fontPushBtn;
    QPushButton*   inputPushBtn;
    QPushButton*   pagePushBtn;
    QPushButton*   programPushBtn;
    QPushButton*   printPushBtn;
    QPushButton*   textcolorPushbtn;
private slots:
    void doPushBtn();
};
#endif // CBUILTINDIALOG_H
