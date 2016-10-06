#include "JSPFileReader.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    JSPFileReader w;
    w.show();
    return a.exec();
}
