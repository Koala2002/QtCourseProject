#ifndef CANVASRANGEOPERATOR_H
#define CANVASRANGEOPERATOR_H

#include <QPoint>
#include <QSize>
#include <QLabel>
#include <graphlayer.h>

class GraphLayerObject;

class RangeNode{
    friend class CanvasRangeOperator;
public:
    RangeNode(GraphLayerObject *nodeData){
        obj=nodeData;
        xNext=NULL;
        xPre=NULL;

        yNext=NULL;
        yPre=NULL;
    }
private:
    GraphLayerObject *obj;

    RangeNode *xNext;
    RangeNode *xPre;

    RangeNode *yNext;
    RangeNode *yPre;

};

class CanvasRangeOperator : public QPoint
{
    friend class RangeNode;
public:
    CanvasRangeOperator();
    QSize MaxRange();//畫布區域最大範圍

    void updateRange(GraphLayerObject *nodeData);
    void putRange(GraphLayerObject *nodeData);
    void deleteRange(GraphLayerObject *nodeData);

private:
    RangeNode *xFirst;//Max of range;
    RangeNode *xEnd;//Min of range;
    RangeNode *yFirst;
    RangeNode *yEnd;

    int getXRange(RangeNode *node);
    int getYRange(RangeNode *node);
};


#endif // CANVASRANGEOPERATOR_H
