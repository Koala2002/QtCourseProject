#include "drawer.h"

Drawer::Drawer(QObject *parent)
    : QObject{parent}
{
    DrawPath=NULL;
    DrawLabel=NULL;
}

void Drawer::Draw(QPoint pos,QPen pen)
{
    QImage DrawImg(DrawLabel->size(),QImage::Format_ARGB32_Premultiplied);
    DrawImg.fill(Qt::transparent);

    QPainter painter(&DrawImg);

    painter.setCompositionMode(QPainter::CompositionMode_Source);

    painter.setBackgroundMode(Qt::OpaqueMode);
    painter.setBackground(Qt::transparent);

    painter.setPen(pen);

    DrawPath->lineTo(pos);

    painter.drawImage(0,0,DrawLabel->pixmap(Qt::ReturnByValue).toImage());
    painter.drawPath(*DrawPath);

    DrawLabel->setPixmap(QPixmap::fromImage(DrawImg));

}

void Drawer::DrawInit(QPoint MousePos, QPoint LabelPos,QSize LabelSize,QPen pen)
{
    DrawPath=new QPainterPath(MousePos);
    DrawLabel=new QLabel();
    DrawLabel->setStyleSheet("background-color:transparent");
    DrawLabel->resize(LabelSize);
    DrawLabel->move(LabelPos);

    QImage DrawImg(DrawLabel->size(),QImage::Format_ARGB32_Premultiplied);
    DrawImg.fill(Qt::transparent);

    QPainter painter(&DrawImg);

    painter.setCompositionMode(QPainter::CompositionMode_Source);

    painter.setBackgroundMode(Qt::OpaqueMode);
    painter.setBackground(Qt::transparent);

    painter.setPen(pen);

    painter.drawPoint(MousePos);

    DrawLabel->setPixmap(QPixmap::fromImage(DrawImg));

}

void Drawer::DrawComplete()
{
    delete DrawPath;
    delete DrawLabel;
    DrawPath=NULL;
    DrawLabel=NULL;
}

bool Drawer::is_On()
{
    return DrawPath==nullptr||DrawPath==NULL;
}

QLabel *Drawer::getDrawLabel()
{
    return DrawLabel;
}
