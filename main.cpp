#include "painter.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Painter w;
    w.showMaximized();
    w.setMouseTracking(true);

    return a.exec();
}
