#include "painter.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Painter w;
    w.setGeometry(QRect(400,200,1088,694));
    w.showMaximized();
    w.setMouseTracking(true);

    return a.exec();
}
