#ifndef BLURRYPAINTER_H
#define BLURRYPAINTER_H

#include <QObject>
#include <QRgba64>
#include <QImage>
#include <queue>
#include <bucketpainter.h>
#include <vector>
#include <math.h>

class BlurryPainter : public BucketPainter
{
    Q_OBJECT
public:
    explicit BlurryPainter(QObject *parent = nullptr);

    QImage Blurrying(QImage img,QPoint Ori,int penSize);//就是模糊

private:
    QColor Blur(QImage img,QPoint Ori);//模糊此點

    double PointDis(QPoint p1,QPoint p2);//兩點距離


signals:

};

#endif // BLURRYPAINTER_H
