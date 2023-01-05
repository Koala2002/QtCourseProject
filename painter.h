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
#include <bucketpainter.h>
#include <graphlayer.h>
#include <graphlayerdisplayer.h>
#include <stack>
#include <queue>
#include <math.h>
#include <QGraphicsProxyWidget>
#include <shapepainter.h>
#include <blurrypainter.h>
#include <valuecontroller.h>
#include <drawer.h>
#include <scenecleaner.h>

QT_BEGIN_NAMESPACE
namespace Ui { class Painter; }
QT_END_NAMESPACE

class Painter : public QMainWindow
{
    Q_OBJECT

public:
    enum PainterTools{DrawPen,Eraser,Bucket,DragTool,DrawShape,Blurry};//工具代號
    Painter(QWidget *parent = nullptr);
    ~Painter();
    void setAction();//設定動作
    void creatMenu();//設定功能表內容
    void setColor();//設定調色盤  
    void setTool();//設定工具
    void UISetting();//UI介面設定

    QImage BucketDrawImage();
    //void PenDraw();
    void Draw();//畫筆,橡皮擦
    void BucketDraw(QImage* img);//水桶
    void updatingImage(QImage img);//更新圖片

private:  

    Ui::Painter *ui;

    QMenu *fileMenu;//檔案操作功能表
    QMenu *toolMenu;//工具操作功能表

    QAction *openFile,*saveFile;//檔案功能表動作
    QAction *backToPreStep,*cancelBackToAction;//復原、重做

    bool mouse_pressed;//滑鼠按下檢查
    bool CtrlKeyPressed;//Ctrl按鍵按下檢查
    bool LShiftKeyPressed;//LShift按鍵按下檢查
    bool SceneHovered;//是否在繪圖區域畫面上

    QPointF mouse_pre,mouse_now;//滑鼠位置

    Drawer DrawTool;//繪圖工具
    SceneCleaner CleanTool;//好啦其實就是橡皮擦ㄏㄏ
    BucketPainter BucketTool;//水桶工具
    ShapePainter ShapeTool;//圖形繪圖器
    BlurryPainter BlurryTool;

    PainterTools Ptool;//使用中的工具代號

    GraphLayer *GLayer;//圖層管理
    std::stack<GraphLayerDisplayerItem*> selectItemList;//以選取的圖層物件

    GraphLayerDisplayer *GDisplayer;//圖層UI顯示

    ValueController *PainterValueController;//工具數值設定器

    void getMouse(QMouseEvent *event);//取得滑鼠座標
    void MousePositionOffset();//滑鼠座標偏移

    double zoomRatio;//縮放倍率

    void setToolCursor(PainterTools tool);//設定目前工具鼠標圖示

    void setCloseModeIcon(QWidget* obj);//設定非致能物件icon
    void setOpenModeIcon(QWidget* obj);//設定致能物件icon

protected:
    void mousePressEvent(QMouseEvent *event);//滑鼠按下
    void mouseReleaseEvent(QMouseEvent *event);//滑鼠放開
    void mouseMoveEvent(QMouseEvent *event);//滑鼠移動
    void wheelEvent(QWheelEvent *event);//滑鼠滾輪滾動

    void keyPressEvent(QKeyEvent* event);//鍵盤按下
    void keyReleaseEvent(QKeyEvent* event);//鍵盤放開

    bool eventFilter(QObject *obj, QEvent *event);//事件濾除器


private slots:

    //----圖層功能操作----//
    void addGraphLayer(QImage img=QImage(1000,800,QImage::Format_ARGB32),QPoint pos=QPoint(0,0));//新增圖層
    void mergeGraphLayer();//合併圖層
    void hideGraphLayer();//隱藏圖層
    void deleteGraphLayer();//刪除圖層
    void copyGraphLayer();//複製圖層
    //----圖層功能操作----//

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

    void on_GraphLayerDisplayerItemClicked();//小圖層顯示物件按下

    void autoScrollDown(int min,int max);

};
#endif // PAINTER_H
