#include "bucketpainter.h"

BucketPainter::BucketPainter()
{

}

void BucketPainter::BucketInit(QImage &Image, QColor color, int tValue)
{
    img=&Image;
    bucketColor=color;
    colorToleranceValue=tValue;
}

//顏色擴散
void BucketPainter::ColorDiffuse(QPoint p)
{
    Colored=std::vector<std::vector<bool>>(img->height(),std::vector<bool>(img->width(),false));
    coverColor=img->pixelColor(p);
    std::queue<QPoint> bfs;
    bfs.push(p);

    Colored[p.y()][p.x()]=true;
    img->setPixelColor(p,bucketColor);

    while(!bfs.empty()){
        img->setPixelColor(bfs.front(),bucketColor);
        for(flowDir DIR=UP;DIR<=RIGHT;DIR=flowDir(DIR+1)){
            QPoint pos=bfs.front();

            pos+=FlowPos(DIR);
            if(CanFlow(pos)==true){
                Colored[pos.y()][pos.x()]=true;               
                bfs.push(pos);
            }
        }
        bfs.pop();
    }    
}

//取得流動座標
QPoint BucketPainter::FlowPos(flowDir d)
{
    if(d==UP)return QPoint(-1,0);
    if(d==DOWN)return QPoint(1,0);
    if(d==LEFT)return QPoint(0,-1);
    if(d==RIGHT)return QPoint(0,1);
}

//確認是否能流過去
bool BucketPainter::CanFlow(QPoint p)
{
    if(p.x()>=img->width()||p.y()>=img->height())return false;
    else if(p.x()<0||p.y()<0)return false;
    else if(Colored[p.y()][p.x()]==true)return false;
    else {
        QColor imgColor=img->pixelColor(p);
        if(
            ((coverColor.red()+colorToleranceValue)>=imgColor.red()&&imgColor.red()>=(coverColor.red()-colorToleranceValue))&&
            ((coverColor.green()+colorToleranceValue)>=imgColor.green()&&imgColor.green()>=(coverColor.green()-colorToleranceValue))&&
            ((coverColor.blue()+colorToleranceValue)>=imgColor.blue()&&imgColor.blue()>=(coverColor.blue()-colorToleranceValue))&&
            ((coverColor.alpha()+colorToleranceValue)>=imgColor.alpha()&&imgColor.alpha()>=(coverColor.alpha()-colorToleranceValue))
        )return true;


        return false;
    }

}

//確認是否能使用座標p進行運算(用於模糊工具)
bool BucketPainter::CanFlow(QPoint p, QSize range)
{
    if(p.x()>=range.width()||p.y()>=range.height())return false;
    else if(p.x()<0||p.y()<0)return false;
    else return true;
}
