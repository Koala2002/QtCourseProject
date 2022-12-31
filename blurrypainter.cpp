#include "blurrypainter.h"

BlurryPainter::BlurryPainter(QObject *parent)
{

}

QColor BlurryPainter::Blur(QImage img, QPoint Ori)
{
    int newColor[4]={0};//新的rgba數值
    int OpPos[9][2]={{0,0},{0,1},{1,0},{1,1},{0,-1},{-1,0},{-1,-1},{-1,1},{1,-1}};

    for(int a=0;a<9;a++){
        QPoint pos(Ori+QPoint(OpPos[a][0],OpPos[a][1]));
        if(pos.x()>=img.size().width()||pos.y()>=img.height())continue;
        if(pos.x()<0||pos.y()<0)continue;
        newColor[0]+=img.pixelColor(pos).red();
        newColor[1]+=img.pixelColor(pos).green();
        newColor[2]+=img.pixelColor(pos).blue();
        newColor[3]+=img.pixelColor(pos).alpha();
    }

    for(int a=0;a<4;a++)newColor[a]/=9;

    return QColor(newColor[0],newColor[1],newColor[2],newColor[3]);
}

double BlurryPainter::PointDis(QPoint p1, QPoint p2)
{
    int xDis=p1.x()-p2.x();
    int yDis=p1.y()-p2.y();

    return std::sqrt(xDis*xDis+yDis*yDis);
}

QImage BlurryPainter::Blurrying(QImage img, QPoint Ori, int penSize)
{
    if(Ori.x()<0||Ori.y()<0||Ori.x()>=img.size().width()||Ori.y()>=img.size().height())return img;
    std::queue<QPoint> BFS;
    QImage newImg=img;

    BFS.push(Ori);
    std::vector<std::vector<bool>> isBlurry(img.size().height(),std::vector<bool>(img.size().width(),false));
    isBlurry[Ori.y()][Ori.x()]=true;

    while(!BFS.empty()){
        for(flowDir DIR=UP;DIR<=RIGHT;DIR=flowDir(DIR+1)){
            QPoint pos=BFS.front();
            pos+=FlowPos(DIR);
            if(CanFlow(pos,img.size())==true){
                if(isBlurry[pos.y()][pos.x()]==false){
                    if(PointDis(pos,Ori)>=penSize/2)continue;
                    newImg.setPixelColor(pos,Blur(img,pos));
                    isBlurry[pos.y()][pos.x()]=true;
                    BFS.push(pos);
                }
            }
        }

        BFS.pop();
    }

    return newImg;
}
