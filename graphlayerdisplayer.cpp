#include "graphlayerdisplayer.h"
#include <QDebug>
GraphLayerDisplayerItem::GraphLayerDisplayerItem(GraphLayerDisplayer *parent,GraphLayerObject *layer,int layerNumber)
{
    idx=layer;
    displayer=parent;

    hiding=false;//隱藏狀態預設為false
    selecting=false;//選取狀態預設為false;

    this->setMinimumSize(100,100);
    this->setMaximumSize(100,100);

    this->setPixmap(layer->pixmap()->scaled(100,100, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    objectVLayout=new QVBoxLayout();
    objectVLayout->setSpacing(2);

    layerText=new QLabel();

    layerText->setText(QString("圖層")+QString::number(layerNumber+1));

    setToolButton();//選項內容設定

    QGridLayout *objectHLayout=new QGridLayout();

    objectHLayout->addWidget(layerText,0,0);
    objectHLayout->addWidget(toolButton,0,1);

    objectVLayout->addLayout(objectHLayout);
    objectVLayout->addWidget(this);
}

GraphLayerDisplayerItem::~GraphLayerDisplayerItem(){
    delete objectVLayout;//刪除物件排版整合
    delete toolButton;//刪除選項按鈕
    delete toolMenu;//刪除選項清單
}
GraphLayerObject *GraphLayerDisplayerItem::getidx()
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

void GraphLayerDisplayerItem::setToolButton()
{
    toolButton= new QToolButton();
    toolMenu = new QMenu();

    deleteAction=new QAction(QString("刪除"));
    hideLayerAction=new QAction(QString("隱藏"));
    connect(deleteAction,SIGNAL(triggered()),SLOT(deleteLayer()));
    toolMenu->addAction(deleteAction);


    connect(hideLayerAction,SIGNAL(triggered()),SLOT(hideLayer()));
    toolMenu->addAction(hideLayerAction);

    toolMenu->addAction(QString("我不知道還能加什麼"));
    toolButton->setPopupMode(QToolButton::InstantPopup );
    toolButton->setMenu(toolMenu);

    toolButton->setMaximumSize(50,20);
    toolButton->setText(QString("選項"));

    toolButton->setStyleSheet(
        "background-color:rgb(235,235,235);"
        "color:rgb(35,35,35);"
    );

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
        hideLayerAction->setText("取消隱藏");
        hiding=true;
        idx->hide();
    }
    else{
        if(getParent()->layerNow==this)this->setStyleSheet("background-color:rgba(0,0,0,0);border:1px solid rgba(255,255,255,255);");
        else this->setStyleSheet("background-color:rgba(0,0,0,0);border:1px solid rgba(255,255,255,100);");

        hideLayerAction->setText("隱藏");
        hiding=false;
        idx->cancelHide();
    }
}

GraphLayerDisplayer::GraphLayerDisplayer(QWidget *parent)
{
    widget=parent;
    Canvas=new QHBoxLayout(parent);
    Canvas->setSizeConstraint(QLayout::SetMinimumSize);
    Canvas->setSpacing(30);
    Canvas->setAlignment(Qt::AlignLeft);
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

