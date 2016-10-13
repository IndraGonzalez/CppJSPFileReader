#include "JSPFileReader.h"

JSPFileReader::JSPFileReader(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	reader = new Reader(this);
	reader->start();
}