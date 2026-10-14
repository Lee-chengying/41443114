#include "cbuiltindialog.h"
#include <QDebug>
#include <QColorDialog>
#include <QFileDialog>
#include <QFontDialog>
#include <QInputDialog>
#include <QProgressDialog>
#include <QErrorMessage>

// 印表機支援模組標頭檔
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPageSetupDialog>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrintPreviewDialog>

CBuiltinDialog::CBuiltinDialog(QWidget *parent)
    : QDialog(parent)
{
    QGridLayout* gridLayout = new QGridLayout;

    // 建立 9 個元件
    displayTextEdit  = new QTextEdit(QStringLiteral("Qt的標準通用對話盒"));
    colorPushBtn     = new QPushButton(QStringLiteral("顏色對話盒"));
    errorPushBtn     = new QPushButton(QStringLiteral("錯誤訊息盒"));
    filePushBtn      = new QPushButton(QStringLiteral("檔案對話盒"));
    fontPushBtn      = new QPushButton(QStringLiteral("字體對話盒"));
    inputPushBtn     = new QPushButton(QStringLiteral("輸入對話盒"));
    pagePushBtn      = new QPushButton(QStringLiteral("頁面設定對話盒"));
    progressPushBtn  = new QPushButton(QStringLiteral("進度對話盒"));
    printPushBtn     = new QPushButton(QStringLiteral("列印對話盒"));
    textcolorPushBtn = new QPushButton(QStringLiteral("字體顏色對話盒")); // 加回按鈕

    // 3x3 完美九宮格佈局
    // 第 0 列
    gridLayout->addWidget(colorPushBtn,     0, 0);
    gridLayout->addWidget(errorPushBtn,     0, 1);
    gridLayout->addWidget(filePushBtn,      0, 2);

    // 第 1 列
    gridLayout->addWidget(fontPushBtn,      1, 0);
    gridLayout->addWidget(inputPushBtn,     1, 1);
    gridLayout->addWidget(pagePushBtn,      1, 2);

    // 第 2 列 (填滿 3 格)
    gridLayout->addWidget(progressPushBtn,  2, 0);
    gridLayout->addWidget(printPushBtn,     2, 1);
    gridLayout->addWidget(textcolorPushBtn, 2, 2); // 放在第 2 列第 2 欄

    // 第 3 列：文字顯示區跨滿 1 列 3 欄
    gridLayout->addWidget(displayTextEdit,  3, 0, 1, 3);

    setLayout(gridLayout);
    setWindowTitle(QStringLiteral("內建對話盒展示"));
    resize(600, 400);

    // 連接信號與槽函數
    connect(colorPushBtn,     SIGNAL(clicked()), this, SLOT(doPushBtn()));
    connect(errorPushBtn,     SIGNAL(clicked()), this, SLOT(doPushBtn()));
    connect(filePushBtn,      SIGNAL(clicked()), this, SLOT(doPushBtn()));
    connect(fontPushBtn,      SIGNAL(clicked()), this, SLOT(doPushBtn()));
    connect(inputPushBtn,     SIGNAL(clicked()), this, SLOT(doPushBtn()));
    connect(pagePushBtn,      SIGNAL(clicked()), this, SLOT(doPushBtn()));
    connect(progressPushBtn,  SIGNAL(clicked()), this, SLOT(doPushBtn()));
    connect(printPushBtn,     SIGNAL(clicked()), this, SLOT(doPushBtn()));
    connect(textcolorPushBtn, SIGNAL(clicked()), this, SLOT(doPushBtn())); // 連接事件
}

void CBuiltinDialog::doPushBtn()
{
    QPushButton* btn = qobject_cast<QPushButton*>(sender());

    // 1. 顏色對話盒 (更改【背景顏色】)
    if (btn == colorPushBtn)
    {
        QPalette palette = displayTextEdit->palette();
        const QColor color = QColorDialog::getColor(palette.color(QPalette::Base), this, QStringLiteral("選擇背景顏色"));
        if (color.isValid())
        {
            palette.setColor(QPalette::Base, color);
            displayTextEdit->setPalette(palette);
        }
    }

    // 2. 字體顏色對話盒 (更改【文字顏色】)
    if (btn == textcolorPushBtn)
    {
        QPalette palette = displayTextEdit->palette();
        const QColor color = QColorDialog::getColor(palette.color(QPalette::Text), this, QStringLiteral("選擇字體顏色"));
        if (color.isValid())
        {
            palette.setColor(QPalette::Text, color);
            displayTextEdit->setPalette(palette);
        }
    }

    // 3. 錯誤訊息盒
    if (btn == errorPushBtn)
    {
        QErrorMessage* errorDlg = new QErrorMessage(this);
        errorDlg->setWindowTitle(QStringLiteral("錯誤訊息盒"));
        errorDlg->showMessage(QStringLiteral("這是一個錯誤訊息示範！"));
    }

    // 4. 檔案對話盒 (儲存檔案)
    if (btn == filePushBtn)
    {
        QString fileName = QFileDialog::getSaveFileName(this, QStringLiteral("儲存檔案"), ".");
        if (!fileName.isEmpty())
        {
            displayTextEdit->setText(fileName);
        }
    }

    // 5. 字體對話盒
    if (btn == fontPushBtn)
    {
        bool ok;
        const QFont& font = QFontDialog::getFont(&ok, displayTextEdit->font(), this, QStringLiteral("字體對話盒"));
        if (ok)
        {
            displayTextEdit->setFont(font);
        }
    }

    // 6. 輸入對話盒
    if (btn == inputPushBtn)
    {
        bool ok;
        QString text = QInputDialog::getText(this,
                                             QStringLiteral("輸入對話盒"),
                                             QStringLiteral("輸入文字"),
                                             QLineEdit::Normal,
                                             QDir::home().dirName(),
                                             &ok);
        if (ok && !text.isEmpty())
        {
            displayTextEdit->setText(text);
        }
    }

    // 7. 頁面設定對話盒
    if (btn == pagePushBtn)
    {
        QPrinter printer(QPrinter::HighResolution);
        QPageSetupDialog* dlg = new QPageSetupDialog(&printer, this);
        dlg->setWindowTitle(QStringLiteral("頁面設定話塊"));
        if (dlg->exec() == QDialog::Accepted)
        {
            // 點選確定
        }
    }

    // 8. 進度對話盒
    if (btn == progressPushBtn)
    {
        QProgressDialog progress(QStringLiteral("正在複製檔案..."),
                                 QStringLiteral("取消"),
                                 0, 10000, this);
        progress.setWindowTitle(QStringLiteral("進度對話塊"));
        progress.show();

        for (int i = 0; i < 10000; i++)
        {
            progress.setValue(i);
            qApp->processEvents();
            if (progress.wasCanceled())
            {
                break;
            }
            qDebug() << i;
        }
        progress.setValue(10000);
    }

    // 9. 列印對話盒
    if (btn == printPushBtn)
    {
        QPrinter printer(QPrinter::HighResolution);
        QPrintDialog dialog(&printer, this);
        if (dialog.exec() != QDialog::Accepted)
        {
            return;
        }
    }
}