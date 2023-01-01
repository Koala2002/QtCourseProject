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

class ValueController : public QObject
{
    Q_OBJECT
public:
    enum PageCode{PenPage,EraserPage,BucketPage,BlurryPage,DragPage,ShapePage};
    enum ToolCode{PenValue,EraserValue,BlurryValue,BucketValue};
    explicit ValueController(QStackedWidget *RegionWidget = nullptr);

    QPen getPen();//回傳畫筆
    QPainter::CompositionMode getPenMode();//回傳畫筆上色方式

    QColor getColor();//回傳目前使用顏色
    int getBlurryWeight();//回傳模糊權重
    void setColor(QColor rgba);
    void loadTool(ToolCode code);//讀取使用工具資料
    void setPage(PageCode code);//設定工具頁面

private:
    QStackedWidget *widget;

    QPen DrawPen;//畫筆
    QColor ColorNow;//現在畫筆的顏色
    QPainter::CompositionMode PenMode;//畫筆上色模式
    QSlider *penSizeControl;//畫筆大小控制項
    QSlider *penTransParentControl;//畫筆透明度控制項
    QComboBox *penModeChoser;//畫筆上色模式選擇器
    QGroupBox *PenBox;//畫筆數值設定區
    QLabel *PenSizeName1;//尺寸顯示物件
    QLabel *PenSizeName2;//不透明度顯示物件
    QLabel *PenModeName;//上色模式顯示物件
    int penSize;//畫筆大小

    QGroupBox *EraserBox;//畫筆數值設定區
    int eraserSize;//橡皮擦大小
    QSlider *eraserSizeControl;//橡皮擦大小控制項
    QLabel *EraserSizeName1;//橡皮擦大小顯示物件

    QGroupBox *BlurryBox;//畫筆數值設定區
    int blurrySize;//模糊工具大小
    int blurryWeight;//模糊工具權重
    QSlider *blurrySizeControl;//模糊區域大小控制項
    QSlider *blurryWeightControl;//模糊深度控制項
    QLabel *BlurrySizeName;//模護範圍顯示物件
    QLabel *BlurryWeightName;//模糊權重顯示物件

    QGroupBox *DragBox;//拖曳工具數值設定區，雖然沒有數值可以設定就是了

    QGroupBox *ShapeBox;//圖形工具數值設定區
    int shapeSize;//圖形邊寬


    QGroupBox *BucketBox;//水桶數值設定區
    QSlider *bucketTransParentControl;//水桶透明度控制項
    QLabel *BucketTransParentName;//水桶顏色透明度顯示物件

    int transParentValue;//目前透明度

    void ControllerInit();//數值設定器初始化
    void ControllerGroupBoxInit();//數值設定容器初始化
    void SliderUISetting();//slider UI設定
    void SliderConnectInit();//數值更改slider信號槽連結

private slots:
    void valueSet(int value);
    void PenModeChange(int mode);

signals:

};

#endif // VALUECONTROLLER_H
