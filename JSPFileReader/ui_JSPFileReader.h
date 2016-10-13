/********************************************************************************
** Form generated from reading UI file 'JSPFileReader.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JSPFILEREADER_H
#define UI_JSPFILEREADER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_JSPFileReaderClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *JSPFileReaderClass)
    {
        if (JSPFileReaderClass->objectName().isEmpty())
            JSPFileReaderClass->setObjectName(QStringLiteral("JSPFileReaderClass"));
        JSPFileReaderClass->resize(600, 400);
        menuBar = new QMenuBar(JSPFileReaderClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        JSPFileReaderClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(JSPFileReaderClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        JSPFileReaderClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(JSPFileReaderClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        JSPFileReaderClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(JSPFileReaderClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        JSPFileReaderClass->setStatusBar(statusBar);

        retranslateUi(JSPFileReaderClass);

        QMetaObject::connectSlotsByName(JSPFileReaderClass);
    } // setupUi

    void retranslateUi(QMainWindow *JSPFileReaderClass)
    {
        JSPFileReaderClass->setWindowTitle(QApplication::translate("JSPFileReaderClass", "JSPFileReader", 0));
    } // retranslateUi

};

namespace Ui {
    class JSPFileReaderClass: public Ui_JSPFileReaderClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JSPFILEREADER_H
