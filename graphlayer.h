#ifndef GRAPHLAYER_H
#define GRAPHLAYER_H

#include <QWidget>
#include <QGridLayout>
#include <vector>
#include <QLabel>
#include <imagestorage.h>

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
    GraphLayerObject *Top();
    QSize CanvasSize();
    void CanvasUpdate(GraphLayerObject *objdata);
    QWidget* Widget();

private:

    GraphLayerObject *layerNow;
    QWidget *widget;
    CanvasRangeOperator *CanvasOperator;
    int layerCount;//圖層總數
signals:

};

class GraphLayerObject:public QLabel{
    friend class GraphLayer;
    friend class CanvasRangeOperator;
    Q_OBJECT
public:
    enum UpdateAction{BackStep,Cancel};
    GraphLayerObject(QWidget *CanvasControlWidget=new QWidget(),GraphLayer *parent=new GraphLayer(),QImage img=QImage(800,600,QImage::Format_ARGB32));
    ~GraphLayerObject();//刪除圖層

    void setImage(QImage img);//設定圖片
    void update(QImage img);//更新,放入圖片
    void update(UpdateAction act);//更新,復原、重做

    void hide();//隱藏
    void cancelHide();//取消隱藏

    GraphLayer* getParent();
protected:
    //void mousePressEvent(QMouseEvent *event);
    //void mouseReleaseEvent(QMouseEvent *event);
    //void mouseMoveEvent(QMouseEvent *event,QPoint prePoint,QPoint nowPoint);
private:
    GraphLayer *graphlayer;
    ImageStorage storage;
};



#endif // GRAPHLAYER_H

