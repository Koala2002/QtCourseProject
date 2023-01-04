#include "drawer.h"

Drawer::Drawer(QObject *parent)
    : QObject{parent}
{
    DrawPath=NULL;
    DrawLabel=NULL;
}

//繪圖
void Drawer::Draw(QPoint pos,QPen pen)
{
    QImage DrawImg(DrawLabel->size(),QImage::Format_ARGB32_Premultiplied);
    DrawImg.fill(Qt::transparent);

    QPainter painter(&DrawImg);

    painter.setCompositionMode(QPainter::CompositionMode_Source);

    painter.setPen(pen);

    DrawPath->lineTo(pos);

    painter.drawImage(0,0,DrawLabel->pixmap(Qt::ReturnByValue).toImage());
    painter.drawPath(*DrawPath);

    DrawLabel->setPixmap(QPixmap::fromImage(DrawImg));

}

//畫筆工具開始使用初始化
void Drawer::DrawInit(QPoint MousePos, QPoint LabelPos,QSize LabelSize,QPen pen)
{
    DrawPath=new QPainterPath(MousePos);
    DrawLabel=new QLabel();

    DrawLabel->setStyleSheet("background-color:transparent");//將QLalbel初始化背景需設為透明，因為QLabel背景預設顏色為白色
    DrawLabel->resize(LabelSize);
    DrawLabel->move(LabelPos);


    QImage DrawImg(DrawLabel->size(),QImage::Format_ARGB32_Premultiplied);
    DrawImg.fill(Qt::transparent);

    QPainter painter(&DrawImg);

    painter.setCompositionMode(QPainter::CompositionMode_Source);   

    painter.setPen(pen);

    painter.drawPoint(MousePos);//一開始滑鼠按下繪下的點

    DrawLabel->setPixmap(QPixmap::fromImage(DrawImg));
}

//完成畫筆工具工作
void Drawer::DrawComplete()
{
    delete DrawPath;
    delete DrawLabel;
    DrawPath=NULL;
    DrawLabel=NULL;
}

//判斷是否正在使用畫筆工具避免一些奇怪的bug
bool Drawer::is_On()
{
    return DrawPath==nullptr||DrawPath==NULL;
}

//回傳畫筆工具繪圖預覽QLabel
QLabel *Drawer::getDrawLabel()
{
    return DrawLabel;
}
