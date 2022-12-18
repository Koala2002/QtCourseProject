#include "graphlayer.h"
#include <QDebug>
#include <QPushButton>
#include <canvasrangeoperator.h>
//----GraphLayer----//
GraphLayer::GraphLayer(QWidget *parent)
    : QWidget{parent}
{
    widget=parent;
    //Rangeof
    layerNow=NULL;
    CanvasOperator=new CanvasRangeOperator();
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
    if(layerNow!=NULL)layerNow->raise();

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

GraphLayerObject::GraphLayerObject(QWidget* CanvasControlWidget,GraphLayer *parent,QImage img)
{
    this->setParent(CanvasControlWidget);
    graphlayer=parent;

    setImage(img);
    update(img);

    this->setStyleSheet("background-color:rgba(0,0,0,0);border:1px solid rgba(255,255,255,100);");
    this->show();
}
//----GraphLayer----//



//----GraphLayerObject----//
GraphLayerObject::~GraphLayerObject()
{
    getParent()->CanvasOperator->deleteRange(this);
    this->parentWidget()->setMinimumSize(getParent()->CanvasOperator->MaxRange()+QSize(25,25));
    getParent()->layerCount--;
    if(getParent()->layerNow!=this)return;
    QList<GraphLayerObject*> GraphLayerObjectList=this->parent()->findChildren<GraphLayerObject*>();

    for(auto &child:GraphLayerObjectList){
        if(child!=this){       
            getParent()->setLayer(child);
            return;
        }
    }
    getParent()->setLayer(NULL);
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
        if(storage.size()==0)return;
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

GraphLayer *GraphLayerObject::getParent()
{
    return graphlayer;
}

GraphLayerObject *GraphLayer::Top()
{
    return layerNow;
}


//----GraphLayerObject----//
