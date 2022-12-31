#include "painterlabel.h"
#include <QDebug>
#include <QMouseEvent>
#include <math.h>
PainterLabel::PainterLabel(QWidget *parent,Qt::WindowFlags f)
    : QLabel{parent}
{

}

PainterLabel::~PainterLabel()
{

}

void PainterLabel::mousePressEvent(QMouseEvent *event)
{
    QPoint MousePos=event->globalPos();
    QPoint CircleCenter=this->parentWidget()->mapToGlobal(this->pos());
    CircleCenter+=QPoint(25,25);
    double xDis=(MousePos.x()-CircleCenter.x());
    double yDis=(MousePos.y()-CircleCenter.y());
    if(std::sqrt(xDis*xDis+yDis*yDis)>25)return;

    emit clicked();
}
