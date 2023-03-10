#ifndef GRAPHLAYERDISPLAYER_H
#define GRAPHLAYERDISPLAYER_H

#include <QLabel>
#include <QObject>
#include <QToolButton>
#include <QPushButton>
#include <QAction>
#include <QMenu>
#include <QWidgetAction>
#include <QAction>
#include <QWidget>
#include <graphlayer.h>
#include <QMouseEvent>

class GraphLayerDisplayerItem;

class GraphLayerDisplayer : public QObject
{
    friend class GraphLayerDisplayerItem;
    Q_OBJECT
public:
    GraphLayerDisplayer(QWidget *parent = new QWidget);

    void addLayer(GraphLayerDisplayerItem *layer);//新增圖層
    void setLayer(GraphLayerDisplayerItem *layer);//設定現在圖層

    QWidget* Widget();
    GraphLayerDisplayerItem *Top();//圖層顯示器最上層物件

    int total();//取得現在圖層總數
    void layerCountChange(int num);//改變圖層總數

    bool Ctrl_pressed();//是否按下ctrl
    void ItemSlect(GraphLayerDisplayerItem* item);
private:
    GraphLayerDisplayerItem *layerNow;//現在選擇圖層顯示物件

    QWidget *widget;
    QVBoxLayout *Canvas;

    int layerCount;//圖層總數
};

class GraphLayerDisplayerItem : public QLabel
{
    friend class GraphLayerDisplayer;
    Q_OBJECT
public:
    GraphLayerDisplayerItem(
        GraphLayerDisplayer *parent=new GraphLayerDisplayer(),
        GraphLayerObject *layer=new GraphLayerObject(),
        QGraphicsProxyWidget *SceneIdx=NULL,
        int layerNumber=0
    );
    ~GraphLayerDisplayerItem();

    GraphLayerObject* getIdx();
    QGraphicsProxyWidget* getWidgetIdx();
    GraphLayerDisplayer *getParent();
    QVBoxLayout *ObjectLayout();

    bool isHide();//是否處於隱藏狀態
    bool isSelect();//是否處於選取狀態
    void setSelectState(bool state);//設定選取狀態

    void deleteLayer();//刪除圖層
    void hideLayer();//隱藏圖層
    void copyLayer();//複製圖層

private:
    QGraphicsProxyWidget *widgetIdx;//圖層物件在畫版上的位置
    GraphLayerObject *idx;//圖層物件位置
    GraphLayerDisplayer *displayer;//圖層清單顯示器
    QVBoxLayout *objectVLayout;//物件排版整合
    QLabel *layerText;//圖層名稱

    QAction *deleteAction;//刪除功能
    QAction *hideLayerAction;//隱藏功能

    bool hiding;//隱藏狀態
    bool selecting;//選取狀態(合併圖層用)

protected:
    void mousePressEvent(QMouseEvent *event);    

signals:
    void clicked();

};
#endif // GRAPHLAYERDISPLAYER_H
