#ifndef CBUILTINDIALOG_H
#define CBUILTINDIALOG_H

#include <QDialog>
#include <QtWidgets>

class CBuiltinDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CBuiltinDialog(QWidget *parent = nullptr);
    ~CBuiltinDialog() override = default;

private:
    QTextEdit*      displayTextEdit;
    QPushButton*    colorPushBtn;        // 顏色對話盒 (背景色)
    QPushButton*    errorPushBtn;        // 錯誤訊息盒
    QPushButton*    filePushBtn;         // 檔案對話盒
    QPushButton*    fontPushBtn;         // 字體對話盒
    QPushButton*    inputPushBtn;        // 輸入對話盒
    QPushButton*    pagePushBtn;         // 頁面設定對話盒
    QPushButton*    progressPushBtn;     // 進度對話盒
    QPushButton*    printPushBtn;        // 列印對話盒
    QPushButton*    textcolorPushBtn;    // 字體顏色對話盒 (加回)

private slots:
    void doPushBtn();
};

#endif // CBUILTINDIALOG_H