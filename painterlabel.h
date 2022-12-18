#ifndef PAINTERLABEL_H
#define PAINTERLABEL_H

#include <QMainWindow>
#include <QLabel>

//含clicked事件QLabel
class PainterLabel : public QLabel {
    Q_OBJECT

public:
    explicit PainterLabel(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~PainterLabel();

protected:
    void mousePressEvent(QMouseEvent *event);

signals:
    void clicked();
};

#endif // PAINTERLABEL_H
