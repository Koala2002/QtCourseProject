#include "graphlayerdisplayer.h"
#include <QDebug>
GraphLayerDisplayerItem::GraphLayerDisplayerItem(GraphLayerDisplayer *parent,GraphLayerObject *layer,QGraphicsProxyWidget *SceneIdx,int layerNumber)
{
    idx=layer;
    displayer=parent;
    widgetIdx=SceneIdx;

    hiding=false;//隱藏狀態預設為false
    selecting=false;//選取狀態預設為false;

    this->setMinimumSize(100,100);
    this->setMaximumSize(100,100);

    this->setPixmap(layer->pixmap(Qt::ReturnByValue).scaled(100,100, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    objectVLayout=new QVBoxLayout();
    objectVLayout->setSpacing(5);

    layerText=new QLabel();
    layerText->setFont(QFont("標楷",11,QFont::Bold));
    layerText->setText(QString("圖層")+QString::number(layerNumber+1));    

    layerText->setStyleSheet(
        "max-height:22px;"
        "min-height:22px;"
        "background-color:rgb(225,225,225);"
        "border-radius:5px;"
        "qproperty-alignment: AlignCenter;"
    );

    QGridLayout *objectHLayout=new QGridLayout();

    objectHLayout->addWidget(layerText,0,0);
    //objectHLayout->addWidget(toolButton,0,0);

    objectVLayout->addLayout(objectHLayout);
    objectVLayout->addWidget(this);
}

GraphLayerDisplayerItem::~GraphLayerDisplayerItem(){
    delete objectVLayout;//刪除物件排版整合        
}

QGraphicsProxyWidget *GraphLayerDisplayerItem::getWidgetIdx()
{
    return widgetIdx;
}
GraphLayerObject *GraphLayerDisplayerItem::getIdx()
{
    return idx;
}

GraphLayerDisplayer *GraphLayerDisplayerItem::getParent()
{
    return displayer;
}

QVBoxLayout *GraphLayerDisplayerItem::ObjectLayout()
{
    return objectVLayout;
}

bool GraphLayerDisplayerItem::isHide()
{
    return hiding;
}

bool GraphLayerDisplayerItem::isSelect()
{
    return selecting;
}

void GraphLayerDisplayerItem::setSelectState(bool state)
{
    selecting=state;
}

void GraphLayerDisplayerItem::mousePressEvent(QMouseEvent *event)
{
    emit clicked();
}

void GraphLayerDisplayerItem::deleteLayer()
{
    getParent()->layerCount--;
    delete layerText;
    delete idx;

    //如果刪除的對象是現在的使用層
    if(getParent()->layerNow!=this){
        delete this;
        return;
    }

    QList<GraphLayerDisplayerItem*> GraphLayerDisplayerItemList=this->parent()->findChildren<GraphLayerDisplayerItem*>();
    for(auto &child:GraphLayerDisplayerItemList){
        //找到第一個和自己不符的圖層並且選擇他當作下一個使用圖層
        if(child!=this){
            getParent()->setLayer(child);
            delete this;
            return;
        }
    }

    //只有一個圖層
    getParent()->setLayer(NULL);
    delete this;
}

void GraphLayerDisplayerItem::hideLayer()
{
    if(!hiding){
        if(getParent()->layerNow==this)this->setStyleSheet("background-color:rgba(0,0,0,100);border:1px solid rgba(255,255,255,255);");
        else this->setStyleSheet("background-color:rgba(0,0,0,100);border:1px solid rgba(255,255,255,100);");

        hiding=true;
        idx->hide();
    }
    else{
        if(getParent()->layerNow==this)this->setStyleSheet("background-color:rgba(0,0,0,0);border:1px solid rgba(255,255,255,255);");
        else this->setStyleSheet("background-color:rgba(0,0,0,100);border:1px solid rgba(255,255,255,100);");

        hiding=false;
        idx->cancelHide();
    }
}

void GraphLayerDisplayerItem::copyLayer()
{

}

GraphLayerDisplayer::GraphLayerDisplayer(QWidget *parent)
{
    widget=parent;
    Canvas=new QVBoxLayout(parent);
    Canvas->setSizeConstraint(QLayout::SetMinimumSize);
    Canvas->setSpacing(20);
    Canvas->setAlignment({Qt::AlignTop,Qt::AlignHCenter});
    layerNow=NULL;
    layerCount=0;

}

void GraphLayerDisplayer::addLayer(GraphLayerDisplayerItem *layer)
{
    layerCount++;
    Canvas->addLayout(layer->ObjectLayout());
    setLayer(layer);
}

void GraphLayerDisplayer::setLayer(GraphLayerDisplayerItem *layer)
{
    if(layer!=NULL){
        QList<GraphLayerDisplayerItem*> GraphDisplayerItem=layer->parent()->findChildren<GraphLayerDisplayerItem*>();

        for(auto &child:GraphDisplayerItem){
            if(child->isHide()==false){
                child->setStyleSheet("background-color:rgba(0,0,0,0);border:1px solid rgba(255,255,255,100);");
            }
            else{
                child->setStyleSheet("background-color:rgba(0,0,0,100);border:1px solid rgba(255,255,255,100);");
            }
        }
        if(layer->isHide()==false){
            layer->setStyleSheet("background-color:rgba(0,0,0,0);border:1px solid rgba(255,255,255,255);");
        }
        else{
            layer->setStyleSheet("background-color:rgba(0,0,0,100);border:1px solid rgba(255,255,255,255);");
        }
    }
    layerNow=layer;
}

QWidget *GraphLayerDisplayer::Widget()
{
    return widget;
}

GraphLayerDisplayerItem *GraphLayerDisplayer::Top()
{
    return layerNow;
}

int GraphLayerDisplayer::total()
{
    return layerCount;
}

void GraphLayerDisplayer::layerCountChange(int num)
{
    layerCount=num;
}

