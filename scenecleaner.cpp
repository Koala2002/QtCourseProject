#include "scenecleaner.h"

SceneCleaner::SceneCleaner(QObject *parent)
    : QObject{parent}
{

}

//擦除一個點
QImage SceneCleaner::erased(QPoint pos, QImage img,QPen pen)
{
    QImage EraseImg(img.size(),QImage::Format_ARGB32_Premultiplied);


    QPainter painter(&EraseImg);
    painter.drawImage(0,0,img);
    painter.setCompositionMode(QPainter::CompositionMode_Source);   

    painter.setPen(pen);

    painter.drawPoint(pos);

    return EraseImg;
}

//擦除一條線
QImage SceneCleaner::erased(QPoint pos1, QPoint pos2, QImage img,QPen pen)
{
    QImage EraseImg=img;

    QPainter painter(&EraseImg);

    painter.setCompositionMode(QPainter::CompositionMode_Source);    

    painter.setPen(pen);

    painter.drawLine(pos1,pos2);

    return EraseImg;
}
