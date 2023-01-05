#ifndef VALUECONTROLLER_H
#define VALUECONTROLLER_H

#include <QObject>
#include <QStackedWidget>
#include <QSlider>
#include <QHBoxLayout>
#include <QDebug>
#include <QGroupBox>
#include <QLabel>
#include <QPen>
#include <QPainter>
#include <QComboBox>
#include <math.h>
#include <QLineEdit>
#include <QListView>
#include <QStandardItemModel>
#include <shapepainter.h>

class ValueController : public QObject
{
    Q_OBJECT
public:
    enum PageCode{PenPage,EraserPage,BucketPage,BlurryPage,DragPage,ShapePage};
    enum ToolCode{PenValue,EraserValue,BlurryValue,BucketValue,ShapeValue,None};
    explicit ValueController(QStackedWidget *RegionWidget = nullptr);

    QPen getPen();//回傳畫筆

    QColor getColor(ToolCode code);//回傳目前使用顏色
    int getBlurryWeight();//回傳模糊權重
    int getShapeWidth();
    int getBucketColorToleranceValue();
    void setColor(QColor rgba);
    void loadTool(ToolCode code);//讀取使用工具資料
    void setPage(PageCode code);//設定工具頁面

    ShapePainter::ShapeTheme ShapeNow();//回傳圖形工具目前形狀
    ShapePainter::ShapeMode ShapeLimit();//回傳圖形工具目前形狀
private:
    QStackedWidget *widget;

    //----畫筆數值設定----//
    QPen DrawPen;//畫筆
    QColor ColorNow;//現在畫筆的顏色
    QPainter::CompositionMode PenMode;//畫筆上色模式
    QSlider *penSizeControl;//畫筆大小控制項
    QSlider *penTransParentControl;//畫筆透明度控制項
    QGroupBox *PenBox;//畫筆數值設定區
    QLabel *PenSizeName1;//尺寸顯示物件
    QLabel *PenSizeName2;//不透明度顯示物件
    int penSize;//畫筆大小
    int penTransParentValue;//目前透明度
    //----畫筆數值設定----//


    //----橡皮擦數值設定----//
    QGroupBox *EraserBox;//畫筆數值設定區
    int eraserSize;//橡皮擦大小
    QSlider *eraserSizeControl;//橡皮擦大小控制項
    QLabel *EraserSizeName1;//橡皮擦大小顯示物件
    //----橡皮擦數值設定----//


    //----模糊工具數值設定----//
    QGroupBox *BlurryBox;//畫筆數值設定區
    int blurrySize;//模糊工具大小
    int blurryWeight;//模糊工具權重
    QSlider *blurrySizeControl;//模糊區域大小控制項
    QSlider *blurryWeightControl;//模糊深度控制項
    QLabel *BlurrySizeName;//模護範圍顯示物件
    QLabel *BlurryWeightName;//模糊權重顯示物件
    //----模糊工具數值設定----//


    QGroupBox *DragBox;//拖曳工具數值設定區，雖然沒有數值可以設定就是了


    //----圖形工具數值設定----//
    QGroupBox *ShapeBox;//圖形工具數值設定區
    QComboBox *ShapeChooser;//圖形選擇器
    QLabel *ShapeName;//形狀使用顯示物件
    QComboBox *ShapeLimitChooser;//圖形繪圖限制選擇器
    QLabel *ShapeLimitName;//圖形繪圖限制顯示物件

    int shapeWidth;//圖形邊寬
    int shapeTransParentValue;//圖形工具透明值

    ShapePainter::ShapeTheme shape;//使用中的圖形
    ShapePainter::ShapeMode shapeLimit;//使用的圖形限制

    QLabel *ShapeWidthName;//邊寬顯示物件
    QLabel *ShapeTransParentName;//不透明度顯示物件
    QSlider *shapeWidthControl;//矩形邊寬控制項
    QSlider *shapeTransParentControl;//矩形透明度控制項
    //----圖形工具數值設定----//


    //----水桶數值設定----//
    QGroupBox *BucketBox;//水桶數值設定區
    QLabel *BucketColorToleranceName;//水桶容差顯示物件
    QSlider *bucketColorToleranceControl;//水桶容差控制項
    QLabel *BucketTransParentName;//水桶顏色透明度顯示物件
    QSlider *bucketTransParentControl;//水桶透明度控制項

    int bucketTransParentValue;//目前水桶透明度
    int bucketColorToleranceValue;//目前水桶容差

    void ControllerInit();//數值設定器初始化
    void ControllerGroupBoxInit();//數值設定容器初始化
    void UISetting();//各種控制項UI設定
    void SliderConnectInit();//數值更改slider信號槽連結
    //----水桶數值設定----//

private slots:
    void valueSet(int value);
    void shapeChange(int shapeMode);
    void shapeLimitChange(int shapeLimit);
signals:

};

#endif // VALUECONTROLLER_H
