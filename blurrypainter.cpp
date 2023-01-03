#include "blurrypainter.h"

BlurryPainter::BlurryPainter(QObject *parent)
{

}

QColor BlurryPainter::Blur(QImage img, QPoint Ori,int weight)
{
    int newColor[4]={0};//新的rgba數值
    int totalWeightCount=weight;

    newColor[0]+=img.pixelColor(Ori).red()*weight;
    newColor[1]+=img.pixelColor(Ori).green()*weight;
    newColor[2]+=img.pixelColor(Ori).blue()*weight;
    newColor[3]+=img.pixelColor(Ori).alpha()*weight;


    for(flowDir DIR=UP;DIR<=RIGHT;DIR=flowDir(DIR+1)){
        for(int dis=1;dis<=weight;dis++){
            QPoint flowPoint=Ori+FlowPos(DIR)*dis;
            if(CanFlow(flowPoint,img.size())==true){
                newColor[0]+=img.pixelColor(flowPoint).red()*std::max(1,(int)(weight/dis));
                newColor[1]+=img.pixelColor(flowPoint).green()*std::max(1,(int)(weight/dis));
                newColor[2]+=img.pixelColor(flowPoint).blue()*std::max(1,(int)(weight/dis));
                newColor[3]+=img.pixelColor(flowPoint).alpha()*std::max(1,(int)(weight/dis));
                totalWeightCount+=std::max(1,(int)(weight/dis));
            }
        }
    }
    for(int a=0;a<4;a++)newColor[a]/=totalWeightCount;

    return QColor(newColor[0],newColor[1],newColor[2],newColor[3]);
}

double BlurryPainter::PointDis(QPoint p1, QPoint p2)
{
    int xDis=p1.x()-p2.x();
    int yDis=p1.y()-p2.y();

    return std::sqrt(xDis*xDis+yDis*yDis);
}

QImage BlurryPainter::Blurrying(QImage img, QPoint Ori, int penSize,int weight)
{
    if(Ori.x()<0||Ori.y()<0||Ori.x()>=img.size().width()||Ori.y()>=img.size().height())return img;
    std::queue<QPoint> BFS;
    QImage newImg=img;

    BFS.push(Ori);
    std::vector<std::vector<bool>> isBlurry(img.size().height(),std::vector<bool>(img.size().width(),false));
    isBlurry[Ori.y()][Ori.x()]=true;

    while(!BFS.empty()){
        newImg.setPixelColor(BFS.front(),Blur(img,BFS.front(),weight));
        for(flowDir DIR=UP;DIR<=RIGHT;DIR=flowDir(DIR+1)){
            QPoint pos=BFS.front();

            pos+=FlowPos(DIR);
            if(CanFlow(pos,img.size())==true){
                if(isBlurry[pos.y()][pos.x()]==false){
                    if(PointDis(pos,Ori)>penSize/2)continue;
                    isBlurry[pos.y()][pos.x()]=true;
                    BFS.push(pos);
                }
            }
        }

        BFS.pop();
    }

    return newImg;
}
