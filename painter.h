#ifndef PAINTER_H
#define PAINTER_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsSceneEvent>
#include <QPixmap>
#include <QFileDialog>
#include <QLabel>
#include <QDebug>
#include <QScrollBar>
#include <QColorDialog>
#include <painterbucket.h>
#include <graphlayer.h>
#include <graphlayerdisplayer.h>
#include <stack>
#include <queue>

QT_BEGIN_NAMESPACE
namespace Ui { class Painter; }
QT_END_NAMESPACE

class Painter : public QMainWindow
{
    Q_OBJECT

public:

    Painter(QWidget *parent = nullptr);
    ~Painter();
    void setAction();//設定動作
    void creatMenu();//設定功能表內容
    void setColor();//設定調色盤
    void setTool();//設定工具
    void UISetting();//UI介面設定

    QImage drawingImage();
    void loadingPen(QPainter &painter);//讀取畫筆資料
    void Draw(QPainter* painter);//畫筆,橡皮擦
    void BucketDraw(QImage* img);//水桶
    void updatingImage(QImage img);//更新圖片



private:
    enum PainterTools{DrawPen,Eraser,Bucket,SelectTool};//工具代號
    Ui::Painter *ui;

   // QLabel *imageLabel;//畫布
    //ImageStorage imageStorage;//畫布儲存槽

    QMenu *fileMenu;//檔案操作功能表
    QMenu *toolMenu;//工具操作功能表

    QAction *openFile,*saveFile;//檔案功能表動作
    QAction *backToPreStep,*cancelBackToAction;//復原、重做

    bool mouse_pressed;//滑鼠按下檢查
    bool key_pressed;//鍵盤按下檢查

    QPoint mouse_pre,mouse_now;//滑鼠位置
    QRgb ColorNow;//現在畫筆的顏色
    QPen pen;//畫筆
    int penSize;//畫筆大小

    PainterTools Ptool;//使用中的工具代號

    GraphLayer GLayer;//圖層管理
    std::stack<GraphLayerDisplayerItem*> selectItemList;

    GraphLayerDisplayer *GDisplayer;//圖層UI顯示

    void getMouse(QMouseEvent *event);
    void MousePositionOffset();
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

private slots:
    void addGraphLayer(QImage img=QImage(800,600,QImage::Format_ARGB32),QPoint pos=QPoint(0,0));//新增圖層
    void mergeGraphLayer();
    //----檔案功能操作----//
    void SaveFile();//存檔
    void OpenFile();//開檔
    //----檔案操作----//

    //----工具功能操作----//
    void BackToPreStep();//復原
    void CancelBackToAction();//重做
    //----工具功能操作----//

    //----其他----//
    void ColorChange();//顏色改變
    void ToolChange();//工具切換
    //----其他----//

    void on_ColorDisplayer_clicked();//調色盤被點擊

    void on_PenSizeControl_valueChanged(int arg1);//畫筆大小更新

    void on_GraphLayerDisplayerItemClicked();

    void on_AddGraphLayer_clicked();

    void on_MergeGraphLayer_clicked();

signals:




};
#endif // PAINTER_H
