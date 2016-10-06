#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_JSPFileReader.h"

class JSPFileReader : public QMainWindow
{
    Q_OBJECT

public:
    JSPFileReader(QWidget *parent = Q_NULLPTR);

private:
    Ui::JSPFileReaderClass ui;
};
