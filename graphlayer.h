#ifndef GRAPHLAYER_H
#define GRAPHLAYER_H

#include <QWidget>
#include <QGridLayout>
#include <vector>
#include <queue>
#include <QLabel>
#include <imagestorage.h>
#include <QGraphicsScene>

class GraphLayerObject;
class CanvasRangeOperator;

class GraphLayer : public QWidget
{
    friend class GraphLayerObject;
    friend class CanvasRangeOperator;
    Q_OBJECT
public:
    explicit GraphLayer(QWidget *parent = new QWidget);

    void addGraphLayer(GraphLayerObject *layer);//新增圖層

    int total();//取得圖層總數
    void setLayer(GraphLayerObject * layer);//更改圖層
    void layerCountChange(int num);//改變圖層總數

    GraphLayerObject *Top();//返回目前圖層物件
    QSize CanvasSize();//返回視窗大小
    void CanvasUpdate(GraphLayerObject *objdata);//視窗大小更新

    QWidget* Widget();//不知道這啥

    int &layerDepth();//圖層深度

    QGraphicsScene* GraphLayerScene();//回傳畫布空間

private:

    GraphLayerObject *layerNow;
    QWidget *widget;

    QGraphicsScene *PainterDrawRegion;//畫布空間
    CanvasRangeOperator *CanvasOperator;//畫面大小計算
    int layerCount;//圖層總數
    int GraphLayerDisplayDepth;//圖層物件顯示深度

signals:

};

class GraphLayerObject:public QLabel{
    friend class GraphLayer;
    friend class CanvasRangeOperator;

    Q_OBJECT
public:
    enum UpdateAction{BackStep,Cancel};
    GraphLayerObject(GraphLayer *parent=new GraphLayer(),QImage img=QImage(800,700,QImage::Format_ARGB32));
    ~GraphLayerObject();//刪除圖層

    void setImage(QImage img);//設定圖片
    void update(QImage img);//更新,放入圖片
    void update(UpdateAction act);//更新,復原、重做

    void hide();//隱藏
    void cancelHide();//取消隱藏

    void operator=(const GraphLayerObject& obj);

    GraphLayer* getParent();

private:
    GraphLayer *graphlayer;
    ImageStorage storage;//畫布儲存器
};



#endif // GRAPHLAYER_H

