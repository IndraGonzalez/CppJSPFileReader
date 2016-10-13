#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_JSPFileReader.h"
#include<Reader.h>

class JSPFileReader : public QMainWindow
{
    Q_OBJECT

public:
    JSPFileReader(QWidget *parent = Q_NULLPTR);

private:
    Ui::JSPFileReaderClass ui;
	Reader* reader;
};
