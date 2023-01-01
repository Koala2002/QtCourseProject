#include "painter.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Painter w;
    w.setGeometry(QRect(400,200,1150,780));
    w.showMinimized();
    w.setMouseTracking(true);

    return a.exec();
}
