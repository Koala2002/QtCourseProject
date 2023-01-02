#ifndef SCENECLEANER_H
#define SCENECLEANER_H

#include <QObject>
#include <QImage>
#include <QPainter>

class SceneCleaner : public QObject
{
    Q_OBJECT
public:
    explicit SceneCleaner(QObject *parent = nullptr);

    QImage erased(QPoint pos,QImage img,QPen pen);
    QImage erased(QPoint pos1,QPoint pos2,QImage img,QPen pen);
signals:

};

#endif // SCENECLEANER_H
