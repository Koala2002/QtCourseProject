#ifndef DRAWER_H
#define DRAWER_H

#include <QObject>
#include <QLabel>
#include <QPainter>
#include <QPainterPath>
#include <QPen>


class Drawer : public QObject
{
    Q_OBJECT
public:
    explicit Drawer(QObject *parent = nullptr);

    void Draw(QPoint pos,QPen pen);

    void DrawInit(QPoint MousePos,QPoint LabelPos,QSize LabelSize,QPen pen);

    void DrawComplete();

    bool is_On();

    QLabel *getDrawLabel();
private:
    QPainterPath *DrawPath;
    QLabel *DrawLabel;

signals:

};

#endif // DRAWER_H
