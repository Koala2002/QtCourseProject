#include "painterbucket.h"

BucketPainter::BucketPainter(QImage *image,QColor c,QObject *parent)
    : QObject{parent}
{
    img=image;
    bucketColor=c;
}

//顏色擴散(BFS)
void BucketPainter::ColorDiffuse(QPoint p)
{
    Colored=std::vector<std::vector<bool>>(img->height(),std::vector<bool>(img->width(),false));
    coverColor=img->pixelColor(p);
    std::queue<QPoint> bfs;
    bfs.push(p);

    Colored[p.y()][p.x()]=true;
    img->setPixelColor(p,bucketColor);

    while(!bfs.empty()){
        for(flowDir DIR=UP;DIR<=RIGHT;DIR=flowDir(DIR+1)){
            QPoint pos=bfs.front();
            pos+=FlowPos(DIR);
            if(CanFlow(pos)==true){
                //qDebug()<<pos;
                Colored[pos.y()][pos.x()]=true;
                img->setPixelColor(pos,bucketColor);
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
    else if(img->pixelColor(p)==bucketColor)return false;
    else if(img->pixelColor(p)!=coverColor)return false;
    else return true;
}