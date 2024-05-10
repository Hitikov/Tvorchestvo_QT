#include "corewindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CoreWindow w;
    w.show();
    return a.exec();
}
