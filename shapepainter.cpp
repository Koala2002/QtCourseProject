#include "shapepainter.h"

ShapePainter::ShapePainter(QObject *parent)
    : QObject{parent}
{
    shape=Rectangle;//圖形工具預設形狀為矩形
    mode=NotLimit;
}

void ShapePainter::DrawShapePosMove(QPointF Ori,QPointF Now)
{
    int offset=std::abs(std::abs(Now.x()-Ori.x())-std::abs(Now.y()-Ori.y()));
    if(Now.x()-Ori.x()<0&&Now.y()-Ori.y()<0){
        if(mode==NotLimit)DrawShapeLabel->move(Now.toPoint());
        else {
            if(Now.x()-Ori.x()<Now.y()-Ori.y())
                DrawShapeLabel->move(Now.x()+offset,Now.y());
            else
                DrawShapeLabel->move(Now.x(),Now.y()+offset);
        }
    }
    else if(Now.x()-Ori.x()<0){
        if(mode==NotLimit)DrawShapeLabel->move(Now.x(),Ori.y());
        else {
            if(std::abs(Now.x()-Ori.x())<std::abs(Now.y()-Ori.y()))
                DrawShapeLabel->move(Now.x(),Ori.y());
            else
                DrawShapeLabel->move(Now.x()+offset,Ori.y());
        }
    }
    else if(Now.y()-Ori.y()<0){
        if(mode==NotLimit)DrawShapeLabel->move(Ori.x(),Now.y());
        else {
            if(std::abs(Now.x()-Ori.x())<std::abs(Now.y()-Ori.y()))
                DrawShapeLabel->move(Ori.x(),Now.y()+offset);
            else
                DrawShapeLabel->move(Ori.x(),Now.y());
        }
    }
    else {
        DrawShapeLabel->move(Ori.toPoint());
    }
}

QPoint ShapePainter::DrawShapeDrawPos(QPointF Ori,QPointF Now)
{
    int offset=std::abs(std::abs(Now.x()-Ori.x())-std::abs(Now.y()-Ori.y()));
    if(Now.x()-Ori.x()<0&&Now.y()-Ori.y()<0){
        if(mode==NotLimit)return QPoint(Now.toPoint());
        else {
            if(Now.x()-Ori.x()<Now.y()-Ori.y())
                return QPoint(Now.x()+offset,Now.y());
            else
                return QPoint(Now.x(),Now.y()+offset);
        }
    }
    else if(Now.x()-Ori.x()<0){
        if(mode==NotLimit)return QPoint(Now.x(),Ori.y());
        else {
            if(std::abs(Now.x()-Ori.x())<std::abs(Now.y()-Ori.y()))
                return QPoint(Now.x(),Ori.y());
            else
                return QPoint(Now.x()+offset,Ori.y());
        }
    }
    else if(Now.y()-Ori.y()<0){
        if(mode==NotLimit)return QPoint(Ori.x(),Now.y());
        else {
            if(std::abs(Now.x()-Ori.x())<std::abs(Now.y()-Ori.y()))
                return QPoint(Ori.x(),Now.y()+offset);
            else
                return QPoint(Ori.x(),Now.y());
        }
    }
    else {
        return QPoint(Ori.toPoint());
    }
}

QSize ShapePainter::DrawShapeImageSize(QPointF Ori,QPointF Now)
{
    if(mode==NotLimit)return QSize(std::abs(Now.x()-Ori.x()),std::abs(Now.y()-Ori.y()));
    else{
        int minPos=std::min(std::abs(Now.x()-Ori.x()),std::abs(Now.y()-Ori.y()));

        return QSize(minPos,minPos);
    }
}

QImage ShapePainter::DrawShapeImage(QPointF Ori,QPointF Now)
{
    if(mode==NotLimit)return QImage(std::max(1,(int)std::abs(Now.x()-Ori.x())),std::max(1,(int)std::abs(Now.y()-Ori.y())),QImage::Format_ARGB32);
    else{
        int minPos=std::min(std::abs(Now.x()-Ori.x()),std::abs(Now.y()-Ori.y()));

        return QImage(std::max(1,minPos),std::max(1,minPos),QImage::Format_ARGB32);
    }
}

void ShapePainter::setShape(ShapeTheme shapetheme)
{
    shape=shapetheme;
}

void ShapePainter::setShapeMode(ShapeMode shapemode)
{
    mode=shapemode;
}

ShapePainter::ShapeTheme ShapePainter::Shape()
{
    return shape;
}

ShapePainter::ShapeMode ShapePainter::Mode()
{
    return mode;
}

void ShapePainter::CreatNewShape()
{
    DrawShapeLabel=new QLabel();
    DrawShapeLabel->setStyleSheet("background-color:rgba(0,0,0,0)");
}

void ShapePainter::SetNewImage(QImage img)
{
    DrawShapeLabel->setPixmap(QPixmap::fromImage(img));
}

void ShapePainter::SetSize(QSize size)
{
    DrawShapeLabel->resize(size);
}

void ShapePainter::ShapeComplete()
{
    delete DrawShapeLabel;
}

QLabel *ShapePainter::getDrawShapeLabel()
{
    return DrawShapeLabel;
}
