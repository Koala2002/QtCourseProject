#include "graphlayer.h"
#include <QDebug>
#include <QPushButton>
#include <canvasrangeoperator.h>
#include "graphlayerdisplayer.h"
#include <QGraphicsProxyWidget>

//----GraphLayer----//
GraphLayer::GraphLayer(QWidget *parent)
{
    widget=parent;
    GraphLayerDisplayDepth=0;
    layerCount=0;
    layerNow=NULL;
    CanvasOperator=new CanvasRangeOperator();
    PainterDrawRegion=new QGraphicsScene;
}

//新增圖層
void GraphLayer::addGraphLayer(GraphLayerObject *layer)
{
    CanvasOperator->putRange(layer);
    layerNow=layer;
    layerCount++;
}

//回傳繪畫工作區大小
QSize GraphLayer::CanvasSize()
{
    return CanvasOperator->MaxRange();
}

void GraphLayer::CanvasUpdate(GraphLayerObject *objdata)
{
    CanvasOperator->updateRange(objdata);
}

//設定現在圖層
void GraphLayer::setLayer(GraphLayerObject *layer){

    layerNow=layer;   
}

void GraphLayer::layerCountChange(int num)
{
    layerCount=num;
}

int GraphLayer::total()
{
    return layerCount;
}

QWidget *GraphLayer::Widget()
{
    return widget;
}

int &GraphLayer::layerDepth()
{
    return GraphLayerDisplayDepth;
}

QGraphicsScene *GraphLayer::GraphLayerScene()
{
    return PainterDrawRegion;
}

GraphLayerObject::GraphLayerObject(GraphLayer *parent,QImage img)
{

    graphlayer=parent;
    setImage(img);

    update(img);

    this->setStyleSheet("background-color:rgba(0,0,0,0);border:1px solid rgba(255,255,255,100);");
}
//----GraphLayer----//

//----GraphLayerObject----//
GraphLayerObject::~GraphLayerObject()
{
    getParent()->CanvasOperator->deleteRange(this);
    getParent()->layerCount--;
    getParent()->GraphLayerScene()->setSceneRect(QRect(0,0,getParent()->CanvasSize().width(),getParent()->CanvasSize().height()));//視窗自動調整大小

    if(getParent()->layerNow!=this)return;
    QList<GraphLayerDisplayerItem*> GraphLayerObjectList=this->getParent()->Widget()->findChildren<GraphLayerDisplayerItem*>();

    for(auto &child:GraphLayerObjectList){
        if(child->getIdx()!=this){
            getParent()->setLayer(child->getIdx());

            child->getWidgetIdx()->setZValue(this->getParent()->layerDepth()++);
            return;
        }
    }
    getParent()->setLayer(NULL);

}

QImage GraphLayerObject::getPreImage()
{
    return storage.front();
}

//設定圖片
void GraphLayerObject::setImage(QImage img)
{
    this->setPixmap(QPixmap::fromImage(img));
}

//發生圖像更改
void GraphLayerObject::update(QImage img)
{
    storage.push(img);
}

//復原或重做事件發生
void GraphLayerObject::update(UpdateAction act)
{
    if(act==BackStep){
        if(storage.size()==1)return;
        storage.pop_front();

        QImage image=storage.front();
        image=image.convertToFormat(QImage::Format_ARGB32);

        this->setPixmap(QPixmap::fromImage(image));
        return;
    }
    if(act==Cancel){
        storage.returnBTBSImage();
        QImage image=storage.front();
        image=image.convertToFormat(QImage::Format_ARGB32);

        this->setPixmap(QPixmap::fromImage(image));
        return;
    }
}

void GraphLayerObject::hide()
{
    this->setStyleSheet("background-color:rgba(0,0,0,0);");
    this->setVisible(false);

}

void GraphLayerObject::cancelHide()
{
    this->setStyleSheet("background-color:rgba(0,0,0,0);border:1px solid rgba(255,255,255,100);");
    this->setVisible(true);
}

void GraphLayerObject::operator=(const GraphLayerObject &obj)
{

    this->setImage(obj.pixmap(Qt::ReturnByValue).toImage());
    this->setMaximumSize(obj.size());
    this->setMinimumSize(obj.size());

    while(this->storage.size()>0){
        this->storage.pop_back();
    }
    ImageNode* node=obj.storage.back();
    while(node!=NULL){
        this->storage.push(node->Image());
        node=node->pre;
    }
}

GraphLayer *GraphLayerObject::getParent()
{
    return graphlayer;
}

GraphLayerObject *GraphLayer::Top()
{
    return layerNow;
}


//----GraphLayerObject----//
