/********************************************************************************
** Form generated from reading UI file 'chatwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATWINDOW_H
#define UI_CHATWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatWindow
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ChatWindow)
    {
        if (ChatWindow->objectName().isEmpty())
            ChatWindow->setObjectName(QString::fromUtf8("ChatWindow"));
        ChatWindow->resize(400, 300);
        menuBar = new QMenuBar(ChatWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        ChatWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ChatWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        ChatWindow->addToolBar(mainToolBar);
        centralWidget = new QWidget(ChatWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        ChatWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ChatWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        ChatWindow->setStatusBar(statusBar);

        retranslateUi(ChatWindow);

        QMetaObject::connectSlotsByName(ChatWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ChatWindow)
    {
        ChatWindow->setWindowTitle(QCoreApplication::translate("ChatWindow", "ChatWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChatWindow: public Ui_ChatWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATWINDOW_H
