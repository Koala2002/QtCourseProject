#ifndef SHAPEPAINTER_H
#define SHAPEPAINTER_H

#include <QObject>
#include <QLabel>
#include <QPoint>
#include <QPainter>
#include <QPen>

class ShapePainter : public QObject
{
    Q_OBJECT
public:
    enum ShapeTheme{Rectangle,Circle};//形狀代號
    enum ShapeMode{Square,NotLimit,Solid,Hollow};//圖形特徵代號

    explicit ShapePainter(QObject *parent = nullptr);


    void DrawShapePosMove(QPointF Ori,QPointF Now);//圖形工具繪圖坐標校準
    QPoint getShapeDrawPos(QPointF Ori,QPointF Now);//圖形工具繪圖點
    QSize getShapeImageSize(QPointF Ori,QPointF Now);//圖形工具繪圖大小
    QImage getShapeImage(QPointF Ori,QPointF Now);//圖形工具繪出圖形

    void DrawShape(QImage &img,ShapeTheme theme,ShapeMode limit,int width,QColor color);
    void setShapeMode(ShapeMode shapemode);

    ShapeMode Mode();//回傳目前特徵

    void CreatNewShape();//創建新的圖形
    void SetNewImage(QImage img);
    void SetSize(QSize size);
    void ShapeComplete();//完成圖形繪圖工作

    QLabel* getDrawShapeLabel();

private:
    ShapeMode mode;//目前圖形特徵

    QLabel *DrawShapeLabel;//圖形工具圖形儲存容器
signals:

};

#endif // SHAPEPAINTER_H
