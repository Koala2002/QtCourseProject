#include "painter.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Painter w;
    w.setGeometry(QRect(300,50,1290,940));
    w.showMinimized();
    w.setMouseTracking(true);

    return a.exec();
}
