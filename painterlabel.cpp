#include "painterlabel.h"

PainterLabel::PainterLabel(QWidget *parent,Qt::WindowFlags f)
    : QLabel{parent}
{

}

PainterLabel::~PainterLabel()
{

}

void PainterLabel::mousePressEvent(QMouseEvent *event)
{
    emit clicked();
}
