#include "shapepainter.h"
#include <QDebug>


ShapePainter::ShapePainter(QObject *parent)
    : QObject{parent}
{  
    mode=NotLimit;
}

//圖形工具Label座標校正
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

//取得圖形工具繪圖座標
QPoint ShapePainter::getShapeDrawPos(QPointF Ori,QPointF Now)
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

//取得圖形工具繪圖圖片大小
QSize ShapePainter::getShapeImageSize(QPointF Ori,QPointF Now)
{
    if(mode==NotLimit)return QSize(std::abs(Now.x()-Ori.x()),std::abs(Now.y()-Ori.y()));
    else{
        int minPos=std::min(std::abs(Now.x()-Ori.x()),std::abs(Now.y()-Ori.y()));

        return QSize(minPos,minPos);
    }
}

//取得圖形工具上色圖片
QImage ShapePainter::getShapeImage(QPointF Ori,QPointF Now)
{
    if(mode==NotLimit)return QImage(std::max(1,(int)std::abs(Now.x()-Ori.x())),std::max(1,(int)std::abs(Now.y()-Ori.y())),QImage::Format_ARGB32);
    else{
        int minPos=std::min(std::abs(Now.x()-Ori.x()),std::abs(Now.y()-Ori.y()));

        return QImage(std::max(1,minPos),std::max(1,minPos),QImage::Format_ARGB32);
    }
}

//畫圖形
void ShapePainter::DrawShape(QImage &img, ShapeTheme theme,ShapeMode limit,int width,QColor color)
{
    QPainter painter(&img);

    //如果是空心狀態則設置pen來畫邊，否則設置一個透明的筆畫邊
    if(limit!=Solid)painter.setPen(QPen(color,width));
    else painter.setPen(QPen(Qt::transparent));

    img.fill(Qt::transparent);

    //圖形樣式如果是矩形
    if(theme==ShapePainter::Rectangle){
        if(limit==Solid)painter.setBrush(QBrush(color));
        painter.drawRect(0,0,img.size().width()-1,img.size().height()-1);

    }

    //圖形樣式如果是橢圓
    if(theme==ShapePainter::Circle){
        if(limit==Solid)painter.setBrush(QBrush(color));        
        if(limit==Hollow){
            if(img.width()<=width*2||img.height()<=width*2){
                painter.setBrush(QBrush(color));
                painter.setPen(QPen(Qt::transparent,0));
                painter.drawEllipse(width/2/img.width(),width/2/img.height(),img.width(),img.height());
            }
            else painter.drawEllipse(width/2,width/2,img.width()-width-1,img.height()-width-1);
            return;
        }
        qDebug()<<img.size();
        painter.drawEllipse(0,0,img.size().width()-1,img.size().height()-1);
    }
}

//設定圖形繪圖樣式(橢圓或矩形)
void ShapePainter::setShapeMode(ShapeMode shapemode)
{
    mode=shapemode;
}

//回傳圖形繪圖樣式(橢圓或矩形)
ShapePainter::ShapeMode ShapePainter::Mode()
{
    return mode;
}

//開始使用圖形工具做畫
void ShapePainter::CreatNewShape()
{
    DrawShapeLabel=new QLabel();
    DrawShapeLabel->setStyleSheet("background-color:rgba(0,0,0,0)");
}

//更新圖形工具使用於預覽畫面顯示的QLabel Pixmap
void ShapePainter::SetNewImage(QImage img)
{
    DrawShapeLabel->setPixmap(QPixmap::fromImage(img));
}

//設定使用於預覽畫面顯示的QLabel大小
void ShapePainter::SetSize(QSize size)
{
    DrawShapeLabel->resize(size);
}

//完成圖形工具繪圖工作
void ShapePainter::ShapeComplete()
{
    delete DrawShapeLabel;
}

//回傳繪圖工具使用的QLabel用於更新圖片
QLabel *ShapePainter::getDrawShapeLabel()
{
    return DrawShapeLabel;
}
