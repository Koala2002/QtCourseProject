#ifndef BUCKETPAINTER_H
#define BUCKETPAINTER_H

#include <QObject>
#include <QPoint>
#include <QImage>
#include <queue>
#include <vector>
#include <QColor>
#include <qDebug>

class BucketPainter : public QObject
{
    Q_OBJECT
public:
    explicit BucketPainter();

    void BucketInit(QImage &Image,QColor color,int tValue);
    void ColorDiffuse(QPoint p);//顏色擴散


private:
    QColor bucketColor,coverColor;//水桶顏色,要覆蓋的顏色
    int colorToleranceValue;
protected:
    enum flowDir{UP,DOWN,LEFT,RIGHT};//顏色流動方向
    QPoint FlowPos(flowDir d);//顏色流動位置

    bool CanFlow(QPoint p);//是否能流過去
    bool CanFlow(QPoint p,QSize range);//給模糊功能用的

    std::vector<std::vector<bool>> Colored;
    QImage *img;//用於運算圖片


signals:

};

#endif // BUCKETPAINTER_H
